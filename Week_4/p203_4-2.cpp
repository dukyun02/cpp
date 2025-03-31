#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 4          // 퍼즐 크기 (4x4)
#define MAX_MOVES 1000  // 최대 이동 기록 저장 개수

typedef struct {
    int x, y;  // 빈칸(0)의 위치
} Position;

typedef struct {
    char move; // 이동한 방향 ('W', 'A', 'S', 'D')
} MoveRecord;

int puzzle[SIZE][SIZE];  // 퍼즐 배열
Position emptyPos;       // 빈칸 위치
MoveRecord moves[MAX_MOVES]; // 이동 기록 저장
int moveCount = 0;       // 이동 횟수

// 초기 퍼즐 설정 함수
void initPuzzle() {
    int numbers[SIZE * SIZE];
    for (int i = 0; i < SIZE * SIZE; i++) {
        numbers[i] = i;
    }

    srand(time(NULL));
    for (int i = SIZE * SIZE - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }

    int index = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            puzzle[i][j] = numbers[index];
            if (numbers[index] == 0) {
                emptyPos.x = i;
                emptyPos.y = j;
            }
            index++;
        }
    }
}

// 퍼즐 출력 함수
void printPuzzle() {
    printf("\n퍼즐 상태:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (puzzle[i][j] == 0)
                printf("   ");
            else
                printf("%2d ", puzzle[i][j]);
        }
        printf("\n");
    }
}

// 이동 처리 함수
void moveTile(char direction) {
    int dx = 0, dy = 0;
   
    if (direction == 'W' || direction == 'w') dx = -1; // 위로 이동
    if (direction == 'S' || direction == 's') dx = 1;  // 아래로 이동
    if (direction == 'A' || direction == 'a') dy = -1; // 왼쪽 이동
    if (direction == 'D' || direction == 'd') dy = 1;  // 오른쪽 이동

    int newX = emptyPos.x + dx;
    int newY = emptyPos.y + dy;

    // 경계 체크
    if (newX >= 0 && newX < SIZE && newY >= 0 && newY < SIZE) {
        // 빈칸과 숫자 교환
        puzzle[emptyPos.x][emptyPos.y] = puzzle[newX][newY];
        puzzle[newX][newY] = 0;
        emptyPos.x = newX;
        emptyPos.y = newY;

        // 이동 기록 저장
        if (moveCount < MAX_MOVES) {
            moves[moveCount].move = direction;
            moveCount++;
        }
    }
}

// 리플레이 기능
void replayMoves() {
    printf("\n[리플레이 시작]\n");
    Position replayPos = emptyPos; // 초기 빈칸 위치

    for (int i = 0; i < moveCount; i++) {
        printf("▶ %c 이동\n", moves[i].move);
    }

    printf("\n[리플레이 종료]\n");
}

// 게임 실행 함수
void playGame() {
    char input;
    printf("\n[퍼즐 게임 시작]\n");
    printPuzzle();

    while (1) {
        printf("\n이동할 방향 입력 (WASD, Q: 종료): ");
        scanf(" %c", &input);

        if (input == 'Q' || input == 'q') {
            printf("\n게임 종료!\n");
            break;
        }

        moveTile(input);
        printPuzzle();
    }

    // 게임 종료 후 리플레이 기능 실행
    replayMoves();
}

// 메인 함수
int main() {
    initPuzzle();
    playGame();
    return 0;
}