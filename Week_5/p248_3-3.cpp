#include <stdio.h>

void addTimeArray(MyTime times[], int index1, int index2, int resultIndex) {
    times[resultIndex].hours = times[index1].hours + times[index2].hours;
    times[resultIndex].minutes = times[index1].minutes + times[index2].minutes;
    times[resultIndex].seconds = times[index1].seconds + times[index2].seconds;

    if (times[resultIndex].seconds >= 60) {
        times[resultIndex].seconds -= 60;
        times[resultIndex].minutes++;
    }
    if (times[resultIndex].minutes >= 60) {
        times[resultIndex].minutes -= 60;
        times[resultIndex].hours++;
    }
}

int main() {
    MyTime times[3] = {
        {2, 45, 50},
        {1, 20, 30},
        {0, 0, 0} // 결과 저장용
    };

    addTimeArray(times, 0, 1, 2);
    printf("Result: %d:%d:%d\n", times[2].hours, times[2].minutes, times[2].seconds);
   
    return 0;
}

