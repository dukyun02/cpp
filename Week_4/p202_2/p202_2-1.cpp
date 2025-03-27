#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void randomMap(int map[5][5]) {
    // 난수 생성을 위한 시드 설정
    srand(time(NULL));

    // 5×5 배열을 순회하며 0 또는 1을 랜덤하게 채움
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            map[i][j] = rand() % 2;  // 0 또는 1을 랜덤하게 생성
        }
    }
}

// 테스트용 메인 함수
int main() {
    int map[5][5];

    // randomMap 함수 호출하여 2차원 배열 채우기
    randomMap(map);

    // 결과 출력
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d ", map[i][j]);
        }
        printf("\n");  // 줄바꿈
    }

    return 0;
}