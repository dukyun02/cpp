#include <iostream>
#include <cstring>
using namespace std;

class Sample {
    char* name;                // 문자열 포인터
    static int count;          // 객체 수를 저장하는 정적 변수

public:
    // 기본 생성자
    Sample() {
        name = nullptr;
        count++;
    }

    // 문자열 매개변수 생성자
    Sample(const char* name) {
        if (name) {
            this->name = new char[strlen(name) + 1];
            strcpy(this->name, name);
        } else {
            this->name = nullptr;
        }
        count++;
    }

    // 복사 생성자 (깊은 복사)
    Sample(const Sample& other) {
        if (other.name) {
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
        } else {
            name = nullptr;
        }
        count++;
    }

    // 소멸자
    ~Sample() {
        if (name != nullptr) {
            delete[] name;
        }
        count--;
    }

    // 정적 함수: 객체 수 출력
    static void printCount() {
        cout << "현재 Sample 객체 수: " << count << endl;
    }

    // 디버깅용 이름 출력
    void printName() const {
        cout << "name: " << (name ? name : "null") << endl;
    }
};

// 정적 변수 초기화
int Sample::count = 0;

int main() {
    Sample::printCount();  // 0

    Sample a("sample");
    a.printName();
    Sample::printCount();  // 1

    Sample b(a);           // 복사 생성자
    b.printName();
    Sample::printCount();  // 2

    return 0;              // 명시적 종료
}

