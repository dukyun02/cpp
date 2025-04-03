#include <stdio.h>
#include <stdlib.h>

MyTime* addTimeDynamic(MyTime* t1, MyTime* t2) {
    MyTime* result = (MyTime*)malloc(sizeof(MyTime));
    if (result == NULL) {
        printf("메모리 할당 실패\n");
        return NULL;
    }

    result->hours = t1->hours + t2->hours;
    result->minutes = t1->minutes + t2->minutes;
    result->seconds = t1->seconds + t2->seconds;

    if (result->seconds >= 60) {
        result->seconds -= 60;
        result->minutes++;
    }
    if (result->minutes >= 60) {
        result->minutes -= 60;
        result->hours++;
    }

    return result;
}

int main() {
    MyTime t1 = {2, 45, 50};
    MyTime t2 = {1, 20, 30};

    MyTime* result = addTimeDynamic(&t1, &t2);
    if (result != NULL) {
        printf("Result: %d:%d:%d\n", result->hours, result->minutes, result->seconds);
        free(result);  // 메모리 해제
    }

    return 0;
}

