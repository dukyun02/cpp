#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 5  // 퍼즐 최대 크기

// 퍼즐을 초기화하는 함수
void initPuzzle(int size, int puzzle[MAX_SIZE][MAX_SIZE]) {
    int numbers[MAX_SIZE * MAX_SIZE];
    int total = size * size;

    // 0부터 (size*size - 1)까지 숫자를 배열에 저장
    for (int i = 0; i < total; i++) {
        numbers[i] = i;
    }

    // 배열을 랜덤하게 섞음
    srand(time(NULL));
    for (int i = total - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }

    // 섞인 숫자를 퍼즐에 배치
    int index = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            puzzle[i][j] = numbers[index++];
        }
    }
}

// 퍼즐을 출력하는 함수
void printPuzzle(int size, int puzzle[MAX_SIZE][MAX_SIZE]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (puzzle[i][j] == 0)
                printf("   ");  // 빈 칸(0) 처리
            else
                printf("%2d ", puzzle[i][j]);
        }
        printf("\n");
    }
}

// 메인 함수
int main() {
    int size;
    int puzzle[MAX_SIZE][MAX_SIZE];

    // 사용자에게 퍼즐 크기 입력받기
    printf("퍼즐 크기를 선택하세요 (3, 4, 5): ");
    scanf("%d", &size);

    // 크기 유효성 검사
    if (size < 3 || size > 5) {
        printf("올바른 크기를 입력하세요! (3, 4, 5만 가능)\n");
        return 1;
    }

    // 퍼즐 초기화 및 출력
    initPuzzle(size, puzzle);
    printf("\n랜덤 퍼즐 생성 완료:\n");
    printPuzzle(size, puzzle);

    return 0;
}