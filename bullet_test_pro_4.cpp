#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <conio.h> // console io
#include <cstring> // string.h
#include <cstdlib> // stdlib.h
#include <string> // c++ string class
#include <Windows.h>

//������� ����
const int directionToLeft = 0;
const int directionToRight = 1;

//����ü ����
struct Screen;
struct Player;
struct Enemy;
struct Bullet;
struct Bullets;

//ȭ�� ����ü
struct Screen {
    int      size;//ȭ�鿡 ����� canvas ������
    char* canvas;//ȭ�鿡 ��µ� ĵ����

    // constructor (������ �Լ�) �޸𸮰����� ����Ǵ� ���� ȣ��Ǵ�
    Screen(unsigned int size)
    {
        if (size == 0) size = 100;//size=0�ϋ� 100���� ����
        this->size = size + 10;//���� ���� �ʱ� ��ġ���� �Ѿ� ������ ����� size + 10���� ����
        canvas = new char[this->size];//ĵ���� �����Ҵ� size��ŭ
    }

    //ĵ���� �ʱ�ȭ
    void clear()
    {
        memset(canvas, ' ', size);//canvas ��ü�� ' '���� ó��
    }

    //canvas�� pos��ġ�� face�� ����(���ڿ�)
    void draw(int pos, const char* face)
    {
        strncpy(&(canvas[pos]), face, strlen(face));
    }
    //canvas�� pos��ġ�� face�� ����(���Ϲ���)
    void draw(int pos, char face)
    {
        if (pos < 0 || pos > size) return;
        canvas[pos] = face;
    }
    //canvas�� ���� \0���� ���� �� ���� ���
    void render()
    {
        canvas[size] = '\0';  // render screen
        printf("%s\r", canvas);
    }
    //�Ʒ� ���ǹ����� ����
    bool isInRange(Bullet* bullet);

    // destructor (�Ҹ��� �Լ�) �޸𸮰����󿡼� �������� ���� ȣ��Ǵ� �Լ�
    ~Screen()
    {
        delete[] canvas;//canvas �����Ҵ� ����
        canvas = nullptr;//�ΰ����� �ʱ�ȭ
        size = 0;//������ = 0 �ʱ�ȭ
    }
};

//�÷��̾� ����ü
struct Player {
    char   face[20];//ĳ���� ����
    int      pos;//������ġ
    int      nRemaining;//�ܿ� �ð�
    int      hp;//ü��

    //�÷��̾� ������
    Player(const char* face, int pos, int hp)
    {
        strcpy(this->face, face);
        this->pos = pos;
        this->nRemaining = 0;
        this->hp = hp;
    }

    //�Ʒ� ����
    void fire(Bullets* bullets, Enemy* enemy);

    //�÷��̾� �����̴� �Լ�
    void move(int direction)
    {
        (direction == directionToLeft) ? --pos : ++pos;
    }

    //�÷��̾� ȭ�鿡 �׸��� �Լ�
    void draw(Screen* screen)
    {
        screen->draw(pos + 5, face);
    }

    //�÷��̾� ���� ������Ʈ �Լ�
    void update(const char* face, int enemyPos)
    {
        //�÷��̾� ��ġ�� ����ġ�� �������� ���
        if (pos + 15 - enemyPos >= 0 && pos + 15 - (enemyPos + 5) <= 5 || pos + 10 - enemyPos >= 0 && pos + 10 - (enemyPos + 5) <= 5) {
            onHit();//���ظ� ����
            //�÷��̾�� ���ظ� �Ծ��� �� ���ʿ� ������ ������ �ؾ��ϹǷ� 
            //���� pos��ġ�� ĳ���� ��� ��ġ�� ���̰� ����
            //������ġ ���� ���ʿ� ĳ���Ͱ� ��µǰ�
            //���ʿ� ��µ� ĳ���Ͷ� ���� ������ �������� �԰ԵǴ� ���
        }
        if (nRemaining == 0) return;
        --nRemaining;
        if (nRemaining == 0) strcpy(this->face, face);
    }
    //�÷��̾ ���ظ� �Ծ��� �� �Լ�
    void onHit()
    {
        char temp[10];//������ hp������ �ӽ� ������ ���ں���
        hp -= 1;//hp�� ���� (���� nRemaining�� �����ϰ� ó���ϱ� ���� -1�� ���ҵǰ� ��)
        _itoa(hp, temp, 10);//hp�� ���ڿ� ��ȯ

        //��� ������ �°� HP: hp�� �����·� str�Լ� Ȱ���� face �ϼ�
        strcpy(face, "HP:");
        strcat(face, temp);
        strcat(face, " (T_T)");
        nRemaining = 10;
    }
    //���� ���������� �Լ�
    void onEnemyHit()
    {
        strcpy(face, "      \\(^_^)/");
        nRemaining = 30;
    }

    //���� ��ġ ��ȯ �Լ�
    int  getPos()
    {
        return pos;
    }

    //���� hp�� ��ȯ �Լ�
    int getHp()
    {
        return hp;
    }

    //���� ������ ��ȯ �Լ�
    const char* getFace()
    {
        return face;
    }

    //���� ���� ���� ��ȯ�Լ�
    bool isAlive()
    {
        return hp > 0 ? true : false;
    }
};

//�� ����ü
struct Enemy {
    char   face[20];//�� ��
    int      pos;//�� ��ġ
    int      nRemaining;//�ܿ� �ð�
    int     nMovementInterval;//??�̰Ŵ� �Ⱦ��� �����ε� �ؿ�
    float   fPos;//�̵� �ӵ� ��� ���� ��
    int     hp;//ü�� ����


    //������
    Enemy(const char* face, int pos, int hp)
    {
        strcpy(this->face, face);
        this->pos = pos;
        nRemaining = 0;
        fPos = pos;
        this->hp = hp;
    }

    //�� �̵�
    void move(int direction)
    {
        direction == directionToLeft ? --pos : ++pos;
    }

    //�� ȭ�鿡 �׸��� �Լ�
    void draw(Screen* screen)
    {
        screen->draw(pos, face);
    }

    //�� ���� ������Ʈ �Լ�
    void update(const char* face, int playerPos)
    {
        int movement = playerPos + 12 > pos ? 1 : -1;//�÷��̾�� �տ��������� 1, �ڿ��������� -1
        fPos += movement * 0.1f;//�̵�
        pos = fPos;

        if (nRemaining == 0) return;
        --nRemaining;
        if (nRemaining == 0) strcpy(this->face, face);
    }

    //�Ʒ� ����
    bool isHit(Bullet* bullet);

    //���� �¾�����
    void onHit()
    {
        //���� �÷��̾ �¾�����(onHit)�Լ��� ����
        char temp[10];
        hp -= 5;
        _itoa(hp, temp, 10);
        strcpy(face, "(T_T) HP:");
        strcat(face, temp);
        nRemaining = 10;
    }
    //���� ��ġ ��ȯ�Լ�
    int  getPos()
    {
        return pos;
    }
    //���� ü�� ��ȯ�Լ�
    int getHp()
    {
        return hp;
    }
    //���� �������� ��ȯ�Լ�
    bool isAlive()
    {
        return hp > 0 ? true : false;
    }
};

//�Ѿ� ����ü
struct Bullet {
    int   isReady;//��� �ִ� �غ���� = 0, �߻��� ������(���ư�����) = 1, �߻�ǰ� ���� ���� ���� = 2
    int      pos;//�Ѿ� ��ġ
    int      direction;//�Ѿ� ����

    //������
    Bullet()
    {
        isReady = 0;
        pos = 0;
        direction = directionToLeft;
    }

    //�߻� �Լ�
    void setFire(Player* player, Enemy* enemy)
    {
        isReady = 1; // inUse

        // direction ����
        int enemy_pos = enemy->getPos();
        int player_pos = player->getPos() + 5;
        const char* player_face = player->getFace();

        direction = directionToLeft;
        if (player_pos < enemy_pos) direction = directionToRight;

        // bullet position ����
        pos = player_pos;
        if (direction == directionToRight) pos += (strlen(player_face) - 1);
    }

    //�Ѿ� �����̴� �Լ�
    void move()
    {
        (direction == directionToLeft) ? --pos : ++pos;
    }

    //�Ѿ� ĵ������ �׸��� �Լ�
    void draw(Screen* screen)
    {
        if (isReady == 0 || isReady == 2) return;
        screen->draw(pos, '-');
    }

    //�غ���·� �ٲ��ִ� �Լ�
    void reuse()
    {
        isReady = 0;
    }

    //�Ѿ� ���� ������Ʈ �Լ�
    void update(Player* player, Enemy* enemy, Screen* screen)
    {
        //�Ѿ��� �߻�Ȱ� �ƴϸ� return
        if (isReady == 0 || isReady == 2) return;

        //�Ѿ��� �߻�Ǽ� �����̴� ���¸� ����
        move();
        if (enemy->isHit(this))
        { // ���� �Ѿ��� �¾��� ��
            enemy->onHit();
            player->onEnemyHit();
            isReady = 2;
        }
    }

    //�Ѿ� ��ġ ��ȯ�Լ�
    int  getPos() // function definition
    {
        return pos;
    }
    //�Ѿ� ���� ��ȯ�Լ�
    int  getDirection()
    {
        return direction;
    }

    //�Ѿ��� ��밡���� �������� ��ȯ�ϴ� �Լ�
    int isAvailable() { return isReady; }
};

//źâ ����ü
struct Bullets {
    int      nBullets;//�Ѿ˵� ����
    Bullet* bullets;//źâ ������
    int delay = 110;//������ ������

    //������
    Bullets(unsigned int nBullets)
    {
        if (nBullets == 0) nBullets = 80;
        this->nBullets = nBullets;
        bullets = new Bullet[nBullets];
    }

    //ĵ������ �Ѿ˵� �׸��� �Լ�
    void draw(Screen* screen)
    {
        for (int i = 0; i < nBullets; i++)
        {
            Bullet* bullet = &bullets[i];
            bullet->draw(screen);
        }
    }

    //źâ ������ �Ѿ� ���� ������Ʈ �Լ�
    void update(Player* player, Enemy* enemy, Screen* screen)
    {
        //�� �Ѿ� ���� ������Ʈ
        for (int i = 0; i < nBullets; i++)
        {
            Bullet* bullet = &bullets[i];
            bullet->update(player, enemy, screen);
        }
        //��� �Ѿ��� ����� ��� ������
        if (useAll()) {
            delay--;//������ �����̸� ���ҽ���
            if (delay == 0) {//������ �����̰� 0�̸�
                reload();//��������Ű��
                delay = 110;//������ �ʱ�ȭ
            }
        }
    }

    //������� ���� �Ѿ� ��ȯ�Լ�
    Bullet* find_unused_bullet()
    {
        for (int i = 0; i < nBullets; i++)
        {
            Bullet* bullet = &bullets[i];
            if (bullet->isAvailable() == 0) return bullet;
        }
        return nullptr;
    }
    //�Ѿ��� ��� ����ߴ��� Ȯ���ϴ� �Լ�
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

    //������ �Լ�
    void reload() {
        for (int i = 0; i < nBullets; i++)
        {
            bullets[i].reuse();
        }
    }
    //�Ҹ���
    ~Bullets()
    {
        delete[] bullets;
        bullets = nullptr;
        nBullets = 0;
    }
};

// forward declaration ������ ����
// function prototype declaration �Լ� ���� ����

//�Ѿ��� ȭ�� ���� ���� �ִ��� Ȯ���ϴ� �Լ�
bool Screen::isInRange(Bullet* bullet)
{
    int bullet_pos = bullet->getPos();
    return bullet_pos >= 0 && bullet_pos < size;
}

//�÷��̾ ���� ��� �Լ�
void Player::fire(Bullets* bullets, Enemy* enemy)
{
    Bullet* bullet = bullets->find_unused_bullet();
    if (bullet == nullptr) return;
    bullet->setFire(this, enemy);
}

//���� �Ѿ˿� �´� �Լ�
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

    //�� ���� �ʱ�ȭ
    Screen  screen(100);
    Player* player = new Player("      (-_-)", 0, 50);
    Enemy* enemy = new Enemy("(`_#)", 80, 50);
    Bullets bullets(5);

    // game loop

    bool isLooping = true;
    while (isLooping) {
        screen.clear();//ȭ���� �����


        if (!player->isAlive())//�÷��̾ ������� ������
            break;//�ݺ��� ���� �� ���� ����
        //�÷��̾� ���� ������Ʈ �� ĵ������ �׸���
        player->update("      (-_-)", enemy->getPos());
        player->draw(&screen);

        if (!enemy->isAlive())//���� ������� ������
            break;//�ݺ��� ���� �� ���� ����
        else {
            //�� ���� ������Ʈ �� ĵ������ �׸���
            enemy->update("(`_#)", player->getPos());
            enemy->draw(&screen);
        }

        //�� ���� ������Ʈ �� ĵ������ �׸���
        bullets.update(player, enemy, &screen);
        bullets.draw(&screen);

        screen.render();//���� ĵ���� ���
        Sleep(100);//�ڿ������� ����� ���� ������

        //����� Ű�Է� ó��
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