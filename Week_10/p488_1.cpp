#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
using namespace std;

const int ROW = 10;
const int COL = 20;
const int MAX = 10;

class World {
public:
    char data[ROW][COL];

    void init() {
        for (int i = 0; i < ROW; i++)
            for (int j = 0; j < COL; j++)
                data[i][j] = ' ';
        for (int i = 0; i < ROW; i++) {
            data[i][0] = '#';
            data[i][COL - 1] = '#';
        }
        for (int j = 0; j < COL; j++) {
            data[0][j] = '#';
            data[ROW - 1][j] = '#';
        }
    }

    void show() {
        system("cls");
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++)
                cout << data[i][j];
            cout << endl;
        }
    }
};

class Monster {
protected:
    char shape;

public:
    Monster(int x, int y, char s = 'M') : shape(s) {}
    virtual void move(char map[ROW][COL], int& x, int& y) {
        int dx = rand() % 3 - 1;
        int dy = rand() % 3 - 1;

        int newX = x + dx, newY = y + dy;
        if (map[newX][newY] != '#') {
            x = newX;
            y = newY;
        }
    }
    char getShape() const { return shape; }
};

class Human : public Monster {
public:
    Human(int x, int y, char s = 'H') : Monster(x, y, s) {}

    void moveHuman(char map[ROW][COL], int& x, int& y) {
        char ch = _getch();
        if (ch == 224) ch = _getch();

        int dx = 0, dy = 0;
        switch (ch) {
            case 72: dx = -1; break; // ↑
            case 80: dx = 1;  break; // ↓
            case 75: dy = -1; break; // ←
            case 77: dy = 1;  break; // →
            default: return;
        }

        int newX = x + dx, newY = y + dy;
        if (map[newX][newY] != '#') {
            x = newX;
            y = newY;
        }
    }
};

class MonsterWorld {
    Monster* pMon[MAX];
    int monX[MAX], monY[MAX];
    int monCount;
    World world;

public:
    MonsterWorld() : monCount(0) {}

    void play() {
        srand((unsigned)time(0));
        world.init();

        // 몬스터 3마리 생성
        for (int i = 0; i < 3; i++) {
            monX[monCount] = rand() % (ROW - 2) + 1;
            monY[monCount] = rand() % (COL - 2) + 1;
            pMon[monCount++] = new Monster(monX[monCount], monY[monCount], 'M');
        }

        // 사람 생성 (마지막 인덱스)
        monX[monCount] = ROW / 2;
        monY[monCount] = COL / 2;
        pMon[monCount++] = new Human(monX[monCount], monY[monCount], 'H');

        while (true) {
            world.init();

            // 이동 후 맵에 표시
            for (int i = 0; i < monCount; i++)
                world.data[monX[i]][monY[i]] = pMon[i]->getShape();

            world.show();

            // 몬스터 이동
            for (int i = 0; i < monCount - 1; i++)
                pMon[i]->move(world.data, monX[i], monY[i]);

            // 충돌 검사 (몬스터 vs 사람)
            for (int i = 0; i < monCount - 1; i++) {
                if (monX[i] == monX[monCount - 1] && monY[i] == monY[monCount - 1]) {
                    cout << "\n몬스터에게 잡혔습니다! 게임 오버!" << endl;
                    return;
                }
            }

            // 사람 조작
            ((Human*)pMon[monCount - 1])->moveHuman(world.data, monX[monCount - 1], monY[monCount - 1]);
        }
    }

    ~MonsterWorld() {
        for (int i = 0; i < monCount; i++)
            delete pMon[i];
    }
};

int main() {
    MonsterWorld mw;
    mw.play();
    return 0;
}

