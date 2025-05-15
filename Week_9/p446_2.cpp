#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class Monster {
protected:
    string name, icon;
    int x, y, nItem;

public:
    Monster(string n = "", string i = "?", int px = 0, int py = 0)
        : name(n), icon(i), x(px), y(py), nItem(0) {}

    virtual ~Monster() {}

    virtual void move(int** map, int maxx, int maxy) = 0;

    void print() {
        cout << name << "(" << icon << ") 위치: (" << x << "," << y << ")\n";
    }

    int getX() { return x; }
    int getY() { return y; }

    void draw(int** map) {
        map[y][x] = 1;
    }
};

// 몬스터 1: 좀비 (Zombi)
class Zombie : public Monster {
public:
    Zombie(string n = "허접좀비", string i = "$", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}

    ~Zombie() { cout << "Zombie 소멸\n"; }

    void move(int** map, int maxx, int maxy) override {
        int dx[] = { -1, 1, 0, 0 };
        int dy[] = { 0, 0, -1, 1 };
        int dir = rand() % 4;
        x += dx[dir];
        y += dy[dir];

        // 범위 체크
        if (x < 0) x = 0;
        if (x >= maxx) x = maxx - 1;
        if (y < 0) y = 0;
        if (y >= maxy) y = maxy - 1;
    }
};

// 몬스터 2: 뱀파이어 (Vampire)
class Vampire : public Monster {
public:
    Vampire(string n = "뱀파이어백작", string i = "@", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}

    void move(int** map, int maxx, int maxy) override {
        int dir = rand() % 4;
        if (dir == 0) x--;
        else if (dir == 1) x++;
        else if (dir == 2) y--;
        else y++;

        if (x < 0) x = 0;
        if (x >= maxx) x = maxx - 1;
        if (y < 0) y = 0;
        if (y >= maxy) y = maxy - 1;
    }
};

// 몬스터 3: 강시 (Jiangshi)
class Jiangshi : public Monster {
    bool bHori;

public:
    Jiangshi(string n = "대륙강시", string i = "=", int x = 0, int y = 0, bool bH = true)
        : Monster(n, i, x, y), bHori(bH) {}

    void move(int** map, int maxx, int maxy) override {
        int dir = rand() % 2;
        int jump = rand() % 2 + 1;

        if (bHori) x += (dir == 0 ? -jump : jump);
        else y += (dir == 0 ? -jump : jump);

        if (x < 0) x = 0;
        if (x >= maxx) x = maxx - 1;
        if (y < 0) y = 0;
        if (y >= maxy) y = maxy - 1;
    }
};

// 몬스터 4: 처녀귀신 (KGhost)
class KGhost : public Monster {
public:
    KGhost(string n = "어쩌다귀신", string i = "&", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}

    void move(int** map, int maxx, int maxy) override {
        x = rand() % maxx;
        y = rand() % maxy;
    }
};

// MonsterWorld 클래스
class MonsterWorld {
    int width, height;
    vector<Monster*> pMon;

public:
    MonsterWorld(int w, int h) : width(w), height(h) {}

    ~MonsterWorld() {
        for (auto m : pMon) delete m;
    }

    void add(Monster* m) {
        pMon.push_back(m);
    }

    int** Data() {
        int** map = new int*[height];
        for (int i = 0; i < height; i++) {
            map[i] = new int[width]{};
        }

        for (auto m : pMon)
            m->draw(map);

        return map;
    }

    void FreeMap(int** map) {
        for (int i = 0; i < height; i++)
            delete[] map[i];
        delete[] map;
    }

    void showMap(int** map) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                cout << (map[i][j] ? "*" : ".");
            }
            cout << '\n';
        }
    }

    void play(int delay, int times) {
        for (int t = 0; t < times; t++) {
            int** map = Data();

            cout << "[ " << t + 1 << " ]\n";
            showMap(map);

            for (auto m : pMon)
                m->move(map, width, height);

            FreeMap(map);
        }
    }
};

// 메인 함수
int main() {
    srand((unsigned int)time(NULL));
    int w = 16, h = 8;

    MonsterWorld game(w, h);

    game.add(new Zombie("허접좀비", "$", rand() % w, rand() % h));
    game.add(new Vampire("뱀파이어백작", "@", rand() % w, rand() % h));
    game.add(new KGhost("어쩌다귀신", "&", rand() % w, rand() % h));
    game.add(new Jiangshi("못여서강시", "=", rand() % w, rand() % h, true));
    game.add(new Jiangshi("못여서강시", "=", rand() % w, rand() % h, false));

    game.play(500, 10);

    cout << "----- 게임 종료 -----\n";
    return 0;
}

