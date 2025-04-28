#include <iostream>
#include <algorithm> // std::max 사용
using namespace std;

class Monster {
private:
    int x, y;               // 몬스터의 위치
    int nEnergy;            // 몬스터 에너지

    // 상수 정의
    static const int INIT_ENERGY = 100;   // 에너지 초기값: 100
    static const int ENERGY_GAIN = 8;     // 아이템 먹으면 +8
    static const int ENERGY_LOSS = 1;     // 아이템 못 먹으면 -1

public:
    // 생성자: (0,0) 위치, 에너지는 INIT_ENERGY(100)으로 초기화
    Monster() : x(0), y(0), nEnergy(INIT_ENERGY) {}

    // 아이템을 먹었을 때 or 못 먹었을 때 처리
    void eat(bool gotItem) {
        if (gotItem) {
            nEnergy += ENERGY_GAIN;
        } else {
            nEnergy = max(0, nEnergy - ENERGY_LOSS); // 에너지는 최소 0
        }
    }

    // 몬스터 상태 출력
    void print() const {
        cout << "몬스터 상태 출력:" << endl;
        cout << "  위치 : (" << x << ", " << y << ")" << endl;
        cout << "  에너지 레벨 : " << nEnergy << endl;
    }

    // 몬스터 이동 (필요하면 사용)
    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }

    // 현재 에너지 읽기
    int getEnergy() const {
        return nEnergy;
    }
};