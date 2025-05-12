#include <iostream>
using namespace std;

class Monster {
private:
    int x, y;           // 위치
    int nEnergy;        // 에너지
    static int count;   // Monster 클래스 전체 수 (정적 변수)

public:
    Monster(int x = 0, int y = 0, int energy = 100) : x(x), y(y), nEnergy(energy) {
        count++;
    }

    ~Monster() {
        count--;
    }

    void move() {
        x += 1;
        y += 1;
        nEnergy -= 10;  // 이동 시 에너지 감소
    }

    void eat() {
        nEnergy += 20;  // 먹기 기능 (선택적 사용 가능)
    }

    int getEnergy() const {
        return nEnergy;
    }

    void print() const {
        cout << "Monster at (" << x << ", " << y << "), Energy: " << nEnergy << endl;
    }

    static void printCount() {
        cout << "현재 Monster 수: " << count << endl;
    }
};

int Monster::count = 0;

class MonsterWorld {
private:
    Monster* pMon[100];     // Monster 포인터 배열
    static int mMon;        // MonsterWorld 전체 수

public:
    MonsterWorld() {
        for (int i = 0; i < 100; ++i)
            pMon[i] = nullptr;
    }

    ~MonsterWorld() {
        for (int i = 0; i < 100; ++i)
            delete pMon[i];
    }

    void createMonster(int index, int x, int y) {
        if (index >= 0 && index < 100 && pMon[index] == nullptr) {
            pMon[index] = new Monster(x, y);
            mMon++;
        }
    }

    void moveMonsters() {
        for (int i = 0; i < 100; ++i) {
            if (pMon[i]) pMon[i]->move();
        }
    }

    void checkStarvation() {
        for (int i = 0; i < 100; ++i) {
            if (pMon[i] && pMon[i]->getEnergy() <= 0) {
                delete pMon[i];
                pMon[i] = nullptr;
                mMon--;
            }
        }
    }

    void printAll() const {
        for (int i = 0; i < 100; ++i) {
            if (pMon[i]) pMon[i]->print();
        }
        cout << "MonsterWorld 총 몬스터 수: " << mMon << endl;
    }

    static void printWorldCount() {
        cout << "MonsterWorld 관리 중인 몬스터 수: " << mMon << endl;
    }
};

int MonsterWorld::mMon = 0;

int main() {
    MonsterWorld world;

    // 몬스터 생성 (3마리)
    world.createMonster(0, 0, 0);
    world.createMonster(1, 5, 5);
    world.createMonster(2, 10, 10);

    // 몬스터 상태 출력 + 이동 반복
    for (int step = 1; step <= 10; ++step) {
        cout << "======== Step " << step << " ========" << endl;
        world.moveMonsters();          // ① 몬스터 이동
        world.checkStarvation();       // ② 에너지 고갈 시 삭제
        world.printAll();              // ③ 위치, 에너지 출력
        Monster::printCount();         // ④ 전체 Monster 수 출력
        MonsterWorld::printWorldCount(); // ⑤ MonsterWorld 내부 카운트 출력
        cout << endl;
    }

    return 0;
}

