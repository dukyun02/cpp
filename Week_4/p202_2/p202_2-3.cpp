#include <stdio.h>

void checkMap(int map[5][5]) {
    int i, j;
    int rowCheck, colCheck;
    int mainDiagonal = 1, antiDiagonal = 1;

    // 가로(행) 및 세로(열) 검사
    for (i = 0; i < 5; i++) {
        rowCheck = 1;  // 현재 행이 모두 1인지 확인
        colCheck = 1;  // 현재 열이 모두 1인지 확인

        for (j = 0; j < 5; j++) {
            if (map[i][j] != 1) rowCheck = 0;  // 하나라도 1이 아니면 실패
            if (map[j][i] != 1) colCheck = 0;  // 하나라도 1이 아니면 실패
        }

        if (rowCheck) printf("Row %d is all 1s\n", i);
        if (colCheck) printf("Column %d is all 1s\n", i);
    }

    // 메인 대각선 검사 (↘ 방향: map[0][0], map[1][1], ..., map[4][4])
    for (i = 0; i < 5; i++) {
        if (map[i][i] != 1) mainDiagonal = 0;
    }
    if (mainDiagonal) printf("Main diagonal is all 1s\n");

    // 반대 대각선 검사 (↙ 방향: map[0][4], map[1][3], ..., map[4][0])
    for (i = 0; i < 5; i++) {
        if (map[i][4 - i] != 1) antiDiagonal = 0;
    }
    if (antiDiagonal) printf("Anti diagonal is all 1s\n");
}

// 테스트용 메인 함수
int main() {
    int map[5][5] = {
        {1, 1, 1, 1, 1},  // 모든 원소가 1 → 행 체크에서 발견
        {0, 1, 0, 1, 0},
        {1, 1, 1, 1, 1},  // 모든 원소가 1 → 행 체크에서 발견
        {1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1}
    };

    checkMap(map);  // 검사 수행

    return 0;
}

