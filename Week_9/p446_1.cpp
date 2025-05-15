#include <iostream>
using namespace std;

// 주어진 Point 클래스
class Point {
protected: // (4번 문제: 이걸 private로 바꾸면 자식이 접근 불가함)
    int x, y;

public:
    Point(int xx, int yy) : x(xx), y(yy) {}

    virtual void draw() {
        cout << x << " " << y << " 에 점을 그려라.\n";
    }
};

// (1), (2), (3)번: Point를 상속받은 Rectangle 클래스 정의
class Rectangle : public Point {
private:
    int width, height;

public:
    // 생성자에서 멤버 초기화 리스트로 초기화
    Rectangle(int x, int y, int w, int h) : Point(x, y), width(w), height(h) {}

    // draw() 함수 재정의
    void draw() override {
        cout << x << " " << y << " 에서 가로 " << width << " 세로 " << height << "인 사각형을 그려라.\n";
    }
};

// 메인 함수 (테스트용)
int main() {
    Point p(2, 3);
    p.draw();

    Rectangle r(10, 10, 200, 100);
    r.draw();

    return 0;
}

