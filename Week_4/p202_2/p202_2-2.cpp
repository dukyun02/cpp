#include <stdio.h>

void printMap(int map[5][5]) {
    // 배열을 보기 좋게 출력
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d ", map[i][j]);  // 한 줄에 한 행씩 출력
        }
        printf("\n");  // 줄바꿈
    }
}

// 테스트용 메인 함수
int main() {
    // 샘플 맵 (randomMap을 실행한 후 사용하면 더 좋음)
    int map[5][5] = {
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0},
        {1, 1, 0, 0, 1},
        {0, 0, 1, 1, 0},
        {1, 0, 1, 0, 1}
    };

    // printMap 함수 호출
    printMap(map);

    return 0;
}