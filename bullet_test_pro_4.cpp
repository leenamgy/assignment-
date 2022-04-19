#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <conio.h> // console io
#include <cstring> // string.h
#include <cstdlib> // stdlib.h
#include <string> // c++ string class
#include <Windows.h>

//진행방향 변수
const int directionToLeft = 0;
const int directionToRight = 1;

//구조체 선언
struct Screen;
struct Player;
struct Enemy;
struct Bullet;
struct Bullets;

//화면 구조체
struct Screen {
    int      size;//화면에 출력할 canvas 사이즈
    char* canvas;//화면에 출력될 캔버스

    // constructor (생성자 함수) 메모리공간상에 적재되는 순간 호출되는
    Screen(unsigned int size)
    {
        if (size == 0) size = 100;//size=0일떄 100으로 설정
        this->size = size + 10;//몬스터 생성 초기 위치에서 총알 맞을걸 대비해 size + 10으로 설정
        canvas = new char[this->size];//캔버스 동적할당 size만큼
    }

    //캔버스 초기화
    void clear()
    {
        memset(canvas, ' ', size);//canvas 전체를 ' '공백 처리
    }

    //canvas의 pos위치에 face를 저장(문자열)
    void draw(int pos, const char* face)
    {
        strncpy(&(canvas[pos]), face, strlen(face));
    }
    //canvas의 pos위치에 face를 저장(단일문자)
    void draw(int pos, char face)
    {
        if (pos < 0 || pos > size) return;
        canvas[pos] = face;
    }
    //canvas맨 끝에 \0문자 삽입 후 실제 출력
    void render()
    {
        canvas[size] = '\0';  // render screen
        printf("%s\r", canvas);
    }
    //아래 정의문에서 설명
    bool isInRange(Bullet* bullet);

    // destructor (소멸자 함수) 메모리공간상에서 없어지는 순간 호출되는 함수
    ~Screen()
    {
        delete[] canvas;//canvas 동적할당 해제
        canvas = nullptr;//널값으로 초기화
        size = 0;//사이즈 = 0 초기화
    }
};

//플레이어 구조체
struct Player {
    char   face[20];//캐릭터 형태
    int      pos;//현재위치
    int      nRemaining;//잔여 시간
    int      hp;//체력

    //플레이어 생성자
    Player(const char* face, int pos, int hp)
    {
        strcpy(this->face, face);
        this->pos = pos;
        this->nRemaining = 0;
        this->hp = hp;
    }

    //아래 설명
    void fire(Bullets* bullets, Enemy* enemy);

    //플레이어 움직이는 함수
    void move(int direction)
    {
        (direction == directionToLeft) ? --pos : ++pos;
    }

    //플레이어 화면에 그리는 함수
    void draw(Screen* screen)
    {
        screen->draw(pos + 5, face);
    }

    //플레이어 정보 업데이트 함수
    void update(const char* face, int enemyPos)
    {
        //플레이어 위치가 적위치와 겹쳐지는 경우
        if (pos + 15 - enemyPos >= 0 && pos + 15 - (enemyPos + 5) <= 5 || pos + 10 - enemyPos >= 0 && pos + 10 - (enemyPos + 5) <= 5) {
            onHit();//상해를 입음
            //플레이어는 피해를 입었을 때 왼쪽에 정보가 나오게 해야하므로 
            //실제 pos위치와 캐릭터 출력 위치가 차이가 있음
            //실제위치 보다 앞쪽에 캐릭터가 출력되고
            //앞쪽에 출력된 캐릭터랑 적이 만나서 데미지를 입게되는 방식
        }
        if (nRemaining == 0) return;
        --nRemaining;
        if (nRemaining == 0) strcpy(this->face, face);
    }
    //플레이어가 피해를 입었을 때 함수
    void onHit()
    {
        char temp[10];//현재의 hp정보를 임시 저장할 문자변수
        hp -= 1;//hp값 감소 (위의 nRemaining과 동일하게 처리하기 위해 -1씩 감소되게 함)
        _itoa(hp, temp, 10);//hp값 문자열 변환

        //출력 순서에 맞게 HP: hp값 얼굴형태로 str함수 활용해 face 완성
        strcpy(face, "HP:");
        strcat(face, temp);
        strcat(face, " (T_T)");
        nRemaining = 10;
    }
    //적을 맞췄을때의 함수
    void onEnemyHit()
    {
        strcpy(face, "      \\(^_^)/");
        nRemaining = 30;
    }

    //현재 위치 반환 함수
    int  getPos()
    {
        return pos;
    }

    //현재 hp값 반환 함수
    int getHp()
    {
        return hp;
    }

    //현재 얼굴형태 반환 함수
    const char* getFace()
    {
        return face;
    }

    //현재 생사 정보 반환함수
    bool isAlive()
    {
        return hp > 0 ? true : false;
    }
};

//적 구조체
struct Enemy {
    char   face[20];//적 얼굴
    int      pos;//적 위치
    int      nRemaining;//잔여 시간
    int     nMovementInterval;//??이거는 안쓰는 변수인듯 해요
    float   fPos;//이동 속도 제어를 위한 값
    int     hp;//체력 정보


    //생성자
    Enemy(const char* face, int pos, int hp)
    {
        strcpy(this->face, face);
        this->pos = pos;
        nRemaining = 0;
        fPos = pos;
        this->hp = hp;
    }

    //적 이동
    void move(int direction)
    {
        direction == directionToLeft ? --pos : ++pos;
    }

    //적 화면에 그리는 함수
    void draw(Screen* screen)
    {
        screen->draw(pos, face);
    }

    //적 정보 업데이트 함수
    void update(const char* face, int playerPos)
    {
        int movement = playerPos + 12 > pos ? 1 : -1;//플레이어보다 앞에있을때는 1, 뒤에있을때는 -1
        fPos += movement * 0.1f;//이동
        pos = fPos;

        if (nRemaining == 0) return;
        --nRemaining;
        if (nRemaining == 0) strcpy(this->face, face);
    }

    //아래 설명
    bool isHit(Bullet* bullet);

    //적이 맞았을때
    void onHit()
    {
        //위의 플레이어가 맞았을때(onHit)함수와 동일
        char temp[10];
        hp -= 5;
        _itoa(hp, temp, 10);
        strcpy(face, "(T_T) HP:");
        strcat(face, temp);
        nRemaining = 10;
    }
    //현재 위치 반환함수
    int  getPos()
    {
        return pos;
    }
    //현재 체력 반환함수
    int getHp()
    {
        return hp;
    }
    //현재 생존상태 반환함수
    bool isAlive()
    {
        return hp > 0 ? true : false;
    }
};

//총알 구조체
struct Bullet {
    int   isReady;//쏠수 있는 준비상태 = 0, 발사한 사용상태(날아가는중) = 1, 발사되고 적이 맞은 상태 = 2
    int      pos;//총알 위치
    int      direction;//총알 방향

    //생성자
    Bullet()
    {
        isReady = 0;
        pos = 0;
        direction = directionToLeft;
    }

    //발사 함수
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

    //총알 움직이는 함수
    void move()
    {
        (direction == directionToLeft) ? --pos : ++pos;
    }

    //총알 캔버스에 그리는 함수
    void draw(Screen* screen)
    {
        if (isReady == 0 || isReady == 2) return;
        screen->draw(pos, '-');
    }

    //준비상태로 바꿔주는 함수
    void reuse()
    {
        isReady = 0;
    }

    //총알 정보 업데이트 함수
    void update(Player* player, Enemy* enemy, Screen* screen)
    {
        //총알이 발사된게 아니면 return
        if (isReady == 0 || isReady == 2) return;

        //총알이 발사되서 움직이는 상태를 갱신
        move();
        if (enemy->isHit(this))
        { // 적이 총알을 맞았을 때
            enemy->onHit();
            player->onEnemyHit();
            isReady = 2;
        }
    }

    //총알 위치 반환함수
    int  getPos() // function definition
    {
        return pos;
    }
    //총알 방향 반환함수
    int  getDirection()
    {
        return direction;
    }

    //총알이 사용가능한 상태인지 반환하는 함수
    int isAvailable() { return isReady; }
};

//탄창 구조체
struct Bullets {
    int      nBullets;//총알들 개수
    Bullet* bullets;//탄창 포인터
    int delay = 110;//재장전 딜레이

    //생성자
    Bullets(unsigned int nBullets)
    {
        if (nBullets == 0) nBullets = 80;
        this->nBullets = nBullets;
        bullets = new Bullet[nBullets];
    }

    //캔버스에 총알들 그리는 함수
    void draw(Screen* screen)
    {
        for (int i = 0; i < nBullets; i++)
        {
            Bullet* bullet = &bullets[i];
            bullet->draw(screen);
        }
    }

    //탄창 정보로 총알 정보 업데이트 함수
    void update(Player* player, Enemy* enemy, Screen* screen)
    {
        //각 총알 별로 업데이트
        for (int i = 0; i < nBullets; i++)
        {
            Bullet* bullet = &bullets[i];
            bullet->update(player, enemy, screen);
        }
        //모든 총알을 사용한 경우 재장전
        if (useAll()) {
            delay--;//재장전 딜레이를 감소시켜
            if (delay == 0) {//재장전 딜레이가 0이면
                reload();//재장전시키고
                delay = 110;//딜레이 초기화
            }
        }
    }

    //사용하지 않은 총알 반환함수
    Bullet* find_unused_bullet()
    {
        for (int i = 0; i < nBullets; i++)
        {
            Bullet* bullet = &bullets[i];
            if (bullet->isAvailable() == 0) return bullet;
        }
        return nullptr;
    }
    //총알을 모두 사용했는지 확인하는 함수
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

    //재장전 함수
    void reload() {
        for (int i = 0; i < nBullets; i++)
        {
            bullets[i].reuse();
        }
    }
    //소멸자
    ~Bullets()
    {
        delete[] bullets;
        bullets = nullptr;
        nBullets = 0;
    }
};

// forward declaration 전방위 선언
// function prototype declaration 함수 원형 선언

//총알이 화면 범위 내에 있는지 확인하는 함수
bool Screen::isInRange(Bullet* bullet)
{
    int bullet_pos = bullet->getPos();
    return bullet_pos >= 0 && bullet_pos < size;
}

//플레이어가 총을 쏘는 함수
void Player::fire(Bullets* bullets, Enemy* enemy)
{
    Bullet* bullet = bullets->find_unused_bullet();
    if (bullet == nullptr) return;
    bullet->setFire(this, enemy);
}

//적이 총알에 맞는 함수
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

    //각 변수 초기화
    Screen  screen(100);
    Player* player = new Player("      (-_-)", 0, 50);
    Enemy* enemy = new Enemy("(`_#)", 80, 50);
    Bullets bullets(5);

    // game loop

    bool isLooping = true;
    while (isLooping) {
        screen.clear();//화면을 지운뒤


        if (!player->isAlive())//플레이어가 살아있지 않으면
            break;//반복문 종료 후 게임 종료
        //플레이어 정보 업데이트 후 캔버스에 그리기
        player->update("      (-_-)", enemy->getPos());
        player->draw(&screen);

        if (!enemy->isAlive())//적이 살아있지 않으면
            break;//반복문 종료 후 게임 종료
        else {
            //적 정보 업데이트 후 캔버스에 그리기
            enemy->update("(`_#)", player->getPos());
            enemy->draw(&screen);
        }

        //총 정보 업데이트 후 캔버스에 그리기
        bullets.update(player, enemy, &screen);
        bullets.draw(&screen);

        screen.render();//실제 캔버스 출력
        Sleep(100);//자연스러운 출력을 위한 딜레이

        //사용자 키입력 처리
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