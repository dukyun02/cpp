#include <iostream>
#include "MyTime.h"
using namespace std;

int main() {
    MyTime t1, t2, t3;

    t1.convert(3661);  // 1시간 1분 1초
    t1.print();        // 01:01:01

    t2.convert(59);    // 59초
    t2.print();        // 00:00:59

    t3.add(t1, t2);    // t3 = t1 + t2
    t3.print();        // 01:02:00

    t3.reset();
    t3.print();        // 00:00:00

    t3.read();         // 사용자 입력
    t3.print();        // 입력한 시간 출력

    return 0;
}

