#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <conio.h> // console io
#include <cstring> // string.h
#include <cstdlib> // stdlib.h
#include <string> // c++ string class
#include <time.h>
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

    // constructor (생성자 함수) 메모리공간상에 적재되는 순간 호출되는
    Screen(unsigned int size)
    {
        if (size == 0) size = 100;
        this->size = size + 10;
        canvas = new char[size + 10];
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
        if (pos < 0 || pos > size) return;
        canvas[pos] = face;
    }
    void render()
    {
        canvas[size - 1] = '\0';  // render screen
        printf("%s\r", canvas);
    }
    bool isInRange(Bullet* bullet);

    // destructor (소멸자 함수) 메모리공간상에서 없어지는 순간 호출되는 함수
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
    int      hp;

    Player(const char* face, int pos, int hp)
    {
        strcpy(this->face, face);
        this->pos = pos;
        this->nRemaining = 0;
        this->hp = hp;
    }
    void fire(Bullets* bullets, Enemy* enemy);
    void move(int direction)
    {
        (direction == directionToLeft) ? --pos : ++pos;
    }
    void draw(Screen* screen)
    {
        screen->draw(pos + 5, face);
    }
    void update(const char* face, int enemyPos)
    {
        if (pos + 15 - enemyPos >= 0 && pos + 15 - (enemyPos + 5) <= 5 || pos + 10 - enemyPos >= 0 && pos + 10 - (enemyPos + 5) <= 5) {
            onHit();
        }
        if (nRemaining == 0) return;
        --nRemaining;
        if (nRemaining == 0) strcpy(this->face, face);
    }
    void onHit()
    {
        char temp[10];
        hp -= 1;
        _itoa(hp, temp, 10);
        strcpy(face, "HP:");
        strcat(face, temp);
        strcat(face, " (T_T)");
        nRemaining = 10;
    }
    void onEnemyHit()
    {
        strcpy(face, "      \\(^_^)/");
        nRemaining = 30;
    }
    int  getPos()
    {
        return pos;
    }
    int getHp()
    {
        return hp;
    }
    const char* getFace()
    {
        return face;
    }
    bool isAlive()
    {
        return hp > 0 ? true : false;
    }
};
struct Enemy {
    char   face[20];
    int      pos;
    int      nRemaining;
    int     nMovementInterval;
    float   fPos;
    int     hp;

    Enemy(const char* face, int pos, int hp)
    {
        strcpy(this->face, face);
        this->pos = pos;
        nRemaining = 0;
        fPos = pos;
        this->hp = hp;
    }
    void move(int direction)
    {
        direction == directionToLeft ? --pos : ++pos;
    }
    void draw(Screen* screen)
    {
        screen->draw(pos, face);
    }
    void update(const char* face, int playerPos)
    {
        //int movement = rand() % 3 - 1;
        int movement = playerPos + 12 > pos ? 1 : -1;
        fPos += movement * 0.1f;
        pos = fPos;

        if (nRemaining == 0) return;
        --nRemaining;
        if (nRemaining == 0) strcpy(this->face, face);
    }
    bool isHit(Bullet* bullet);
    void onHit()
    {
        char temp[10];
        hp -= 5;
        _itoa(hp, temp, 10);
        strcpy(face, "(T_T) HP:");
        strcat(face, temp);
        nRemaining = 10;
    }
    int  getPos()
    {
        return pos;
    }
    int getHp()
    {
        return hp;
    }

    bool isAlive()
    {
        return hp > 0 ? true : false;
    }
};
struct Bullet {
    int   isReady;//ready = 0, use(fire) = 1, use(hit) = 2
    int      pos;
    int      direction;

    Bullet()
    {
        isReady = 0;
        pos = 0;
        direction = directionToLeft;
    }
    void setFire(Player* player, Enemy* enemy)
    {
        isReady = 1; // inUse

        // direction 설정
        int enemy_pos = enemy->getPos();
        int player_pos = player->getPos() + 5;
        const char* player_face = player->getFace();

        direction = directionToLeft;
        if (player_pos < enemy_pos) direction = directionToRight;

        // bullet position 설정
        pos = player_pos;
        if (direction == directionToRight) pos += (strlen(player_face) - 1);
    }
    void move()
    {
        (direction == directionToLeft) ? --pos : ++pos;
    }
    void draw(Screen* screen)
    {
        if (isReady == 0 || isReady == 2) return;
        screen->draw(pos, '-');
    }
    void reuse()
    {
        isReady = 0;
    }
    void update(Player* player, Enemy* enemy, Screen* screen)
    {
        if (isReady == 0 || isReady == 2) return;

        move();
        if (enemy->isHit(this))
        { // 적이 총알을 맞았을 때
            enemy->onHit();
            player->onEnemyHit();
            isReady = 2;
        }
    }
    int  getPos() // function definition
    {
        return pos;
    }
    int  getDirection()
    {
        return direction;
    }

    int isAvailable() { return isReady; }
};
struct Bullets {
    int      nBullets; // 80
    Bullet* bullets;
    int delay = 110;

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
        if (useAll()) {
            delay--;
            if (delay == 0) {
                reload();
                delay = 110;
            }
        }
    }
    Bullet* find_unused_bullet()
    {
        for (int i = 0; i < nBullets; i++)
        {
            Bullet* bullet = &bullets[i];
            if (bullet->isAvailable() == 0) return bullet;
        }
        return nullptr;
    }
    bool useAll()
    {
        int i = 0;
        for (i = 0; i < nBullets; i++)
        {
            Bullet* bullet = &bullets[i];
            if (bullet->isAvailable() == 0) return false;
        }
        if (i == nBullets)
            return true;
    }
    void reload() {
        for (int i = 0; i < nBullets; i++)
        {
            bullets[i].reuse();
        }
    }
    ~Bullets()
    {
        delete[] bullets;
        bullets = nullptr;
        nBullets = 0;
    }
};

// forward declaration 전방위 선언
// function prototype declaration 함수 원형 선언
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

Enemy* createEnemy(Player* p) {//적을 생성하는 함수
    int randPos = rand() % 60 + p->pos;//플레이어 위치를 기준으로 앞으로 오게
    Enemy* enemy = new Enemy("(`_#)", randPos, 5);//적 객체 생성
    return enemy;
}

int main()
{
    srand(time(NULL));//rand함수 초기화
    int major;
    int minor;
    int enemySize;

    Screen  screen(100);
    Player* player = new Player("      (-_-)", 0, 10);
    //Enemy* enemy = new Enemy("(`_#)", 80, 5);
    Enemy* enemies[10];//10개의 enemies포인터 변수

    for (int i = 0; i < 10; i++)//초기화
        enemies[i] = NULL;


    enemies[++enemySize] = createEnemy(player);//적을 생성하는 함수

    Bullets bullets(5);
    // game loop

    bool isLooping = true;
    while (isLooping) {
        screen.clear();

        if (!player->isAlive())
            break;

        for (int i = 0; i <= 10; i++) {//플레이어의 위치를 갱신
            if (enemies[i] != NULL)
                player->update("      (-_-)", enemies[i]->getPos());
        }
        player->draw(&screen);

        if (enemySize == 0)
            break;
        for (int i = 0; i <= 10; i++) {//적들의 위치 갱신
            if (enemies[i] != NULL) {
                enemies[i]->update("(`_#)", player->getPos());
                enemies[i]->draw(&screen);
            }
        }

        for (int i = 0; i < 10; i++) {//총알 위치 갱신
            if (enemies[i] != NULL) {
                bullets.update(player, enemies[i], &screen);
            }
        }

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
            player->fire(&bullets, enemy);
            break;
        case 224: // arrow key, function key pressed
            minor = _getch();
            switch (minor) {
            case 75: // left
                player->move(directionToLeft); //             
                break;
            case 77: // right
                player->move(directionToRight);
                break;
            case 72: // up
                enemy->move(directionToLeft);
                break;
            case 80: // down
                enemy->move(directionToRight);
                break;
            }
            break;
        }
    }
    printf("\nGame Over\n");

    delete player;
    delete enemy;

    return 0;
}