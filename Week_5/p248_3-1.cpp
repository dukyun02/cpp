#include <stdio.h>

MyTime globalResult; // 전역 변수 선언

void addTimeGlobal(MyTime t1, MyTime t2) {
    globalResult.hours = t1.hours + t2.hours;
    globalResult.minutes = t1.minutes + t2.minutes;
    globalResult.seconds = t1.seconds + t2.seconds;

    if (globalResult.seconds >= 60) {
        globalResult.seconds -= 60;
        globalResult.minutes++;
    }
    if (globalResult.minutes >= 60) {
        globalResult.minutes -= 60;
        globalResult.hours++;
    }
}

int main() {
    MyTime t1 = {2, 45, 50};
    MyTime t2 = {1, 20, 30};

    addTimeGlobal(t1, t2);
    printf("Result: %d:%d:%d\n", globalResult.hours, globalResult.minutes, globalResult.seconds);
   
    return 0;
}

