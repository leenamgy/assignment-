#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <conio.h> // console io
#include <cstring> // string.h
#include <cstdlib> // stdlib.h
#include <string> // c++ string class
#include <Windows.h>

const int directionToLeft = 0;
const int directionToRight = 1;

struct Screen;
struct Player;
struct Enemy;
struct Bullet;
struct Bullets;

struct Screen {
    int      size;
    char* canvas;

    // constructor (������ �Լ�) �޸𸮰����� ����Ǵ� ���� ȣ��Ǵ�
    Screen(unsigned int size)
    {
        if (size == 0) size = 80;
        this->size = size;
        canvas = new char[size + 1];
    }
    void clear()
    {
        memset(canvas, ' ', size);
    }
    void draw(int pos, const char* face)
    {
        strncpy(&(canvas[pos]), face, strlen(face));
    }
    void draw(int pos, char face)
    {
        if (pos < 0 || pos >= size) return;
        canvas[pos] = face;
    }
    void render()
    {
        canvas[size] = '\0';  // render screen
        printf("%s\r", canvas);
    }
    bool isInRange(Bullet* bullet);

    // destructor (�Ҹ��� �Լ�) �޸𸮰����󿡼� �������� ���� ȣ��Ǵ� �Լ�
    ~Screen()
    {
        delete[] canvas;
        canvas = nullptr;
        size = 0;
    }
};
struct Player {
    char   face[20];
    int      pos;
    int      nRemaining;

    Player(const char* face, int pos)
    {
        strcpy(this->face, face);
        this->pos = pos;
        this->nRemaining = 0;
    }
    void fire(Bullets* bullets, Enemy* enemy);
    void move(int direction)
    {
        (direction == directionToLeft) ? --pos : ++pos;
    }
    void draw(Screen* screen)
    {
        screen->draw(pos, face);
    }
    void update(const char* face)
    {
        if (nRemaining == 0) return;
        --nRemaining;
        if (nRemaining == 0) strcpy(this->face, face);
    }
    void onEnemyHit()
    {
        strcpy(face, "\\(^_^)/");
        nRemaining = 30;
    }
    int  getPos()
    {
        return pos;
    }
    const char* getFace()
    {
        return face;
    }
};
struct Enemy {
    char   face[20];
    int      pos;
    int      nRemaining;
    int     nMovementInterval;
    float   fPos;

    Enemy(const char* face, int pos)
    {
        strcpy(this->face, face);
        this->pos = pos;
        nRemaining = 0;
        fPos = pos;
    }
    void move(int direction)
    {
        direction == directionToLeft ? --pos : ++pos;
    }
    void draw(Screen* screen)
    {
        screen->draw(pos, face);
    }
    void update(const char* face)
    {
        int movement = rand() % 3 - 1;
        fPos += movement * 0.3f;
        pos = fPos;

        if (nRemaining == 0) return;
        --nRemaining;
        if (nRemaining == 0) strcpy(this->face, face);
    }
    bool isHit(Bullet* bullet);
    void onHit()
    {
        strcpy(face, "(T_T)");
        nRemaining = 10;
    }
    int  getPos()
    {
        return pos;
    }
};
struct Bullet {
    bool   isReady;
    int      pos;
    int      direction;

    Bullet()
    {
        isReady = true;
        pos = 0;
        direction = directionToLeft;
    }
    void setFire(Player* player, Enemy* enemy)
    {
        isReady = false; // inUse

        // direction ����
        int enemy_pos = enemy->getPos();
        int player_pos = player->getPos();
        const char* player_face = player->getFace();

        direction = directionToLeft;
        if (player_pos < enemy_pos) direction = directionToRight;

        // bullet position ����
        pos = player_pos;
        if (direction == directionToRight) pos += (strlen(player_face) - 1);
    }
    void move()
    {
        (direction == directionToLeft) ? --pos : ++pos;
    }
    void draw(Screen* screen)
    {
        if (isReady == true) return;
        screen->draw(pos, '-');
    }
    void reuse()
    {
        isReady = true;
    }
    void update(Player* player, Enemy* enemy, Screen* screen)
    {
        if (isReady == true) return;

        move();
        if (enemy->isHit(this))
        { // ���� �Ѿ��� �¾��� ��
            enemy->onHit();
            player->onEnemyHit();
            reuse();
        }
        if (!screen->isInRange(this)) reuse();
    }
    int  getPos() // function definition
    {
        return pos;
    }
    int  getDirection()
    {
        return direction;
    }

    bool isAvailable() { return isReady; }
};
struct Bullets {
    int      nBullets; // 80
    Bullet* bullets;

    Bullets(unsigned int nBullets)
    {
        if (nBullets == 0) nBullets = 80;
        this->nBullets = nBullets;
        bullets = new Bullet[nBullets];
    }
    void draw(Screen* screen)
    {
        for (int i = 0; i < nBullets; i++)
        {
            Bullet* bullet = &bullets[i];
            bullet->draw(screen);
        }
    }
    void update(Player* player, Enemy* enemy, Screen* screen)
    {
        for (int i = 0; i < nBullets; i++)
        {
            Bullet* bullet = &bullets[i];
            bullet->update(player, enemy, screen);
        }
    }
    Bullet* find_unused_bullet()
    {
        for (int i = 0; i < nBullets; i++)
        {
            Bullet* bullet = &bullets[i];
            if (bullet->isAvailable() == true) return bullet;
        }
        return nullptr;
    }
    ~Bullets()
    {
        delete[] bullets;
        bullets = nullptr;
        nBullets = 0;
    }
};

// forward declaration ������ ����
// function prototype declaration �Լ� ���� ����
bool Screen::isInRange(Bullet* bullet)
{
    int bullet_pos = bullet->getPos();
    return bullet_pos >= 0 && bullet_pos < size;
}
void Player::fire(Bullets* bullets, Enemy* enemy)
{
    Bullet* bullet = bullets->find_unused_bullet();
    if (bullet == nullptr) return;
    bullet->setFire(this, enemy);
}
bool Enemy::isHit(Bullet* bullet)
{
    int bullet_direction = bullet->getDirection();
    int bullet_pos = bullet->getPos();
    return (
        (bullet_direction == directionToLeft && pos + strlen(face) - 1 == bullet_pos)
        || (bullet_direction == directionToRight && pos == bullet_pos));
}

int main()
{
    int major;
    int minor;

    Screen  screen(80);
    Player   player("(-_-)", 50);
    Enemy   enemy("(`_#)", 10);
    Bullets bullets(80);

    Enemy   enemy2("(*_*)", 30);

    // game loop

    bool isLooping = true;
    while (isLooping) {
        screen.clear();

        player.update("(-_-)");
        enemy.update("(`_#)");
        enemy2.update("(*_*)");
        bullets.update(&player, &enemy2, &screen);

        player.draw(&screen);
        enemy.draw(&screen);
        enemy2.draw(&screen);
        bullets.draw(&screen);

        screen.render();
        Sleep(100);

        if (!_kbhit()) continue;

        major = _getch();
        switch (major) {
        case 'q':
            isLooping = false;
            break;

        case ' ':
            player.fire(&bullets, &enemy2);
            break;
        case 224: // arrow key, function key pressed
            minor = _getch();
            switch (minor) {
            case 75: // left
                player.move(directionToLeft); //             
                break;
            case 77: // right
                player.move(directionToRight);
                break;
            case 72: // up
                enemy.move(directionToLeft);
                break;
            case 80: // down
                enemy.move(directionToRight);
                break;
            }
            break;
        }
    }
    printf("\nGame Over\n");

    return 0;
}