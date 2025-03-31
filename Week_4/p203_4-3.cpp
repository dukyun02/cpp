#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 4
#define SAVE_FILE "puzzle_save.txt"

typedef struct {
    int x, y;  // 빈칸 위치
} Position;

int puzzle[SIZE][SIZE];  // 퍼즐 배열
Position emptyPos;       // 빈칸 위치
int moveCount = 0;       // 이동 횟수
time_t startTime;        // 게임 시작 시간

// 퍼즐 초기화 함수
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
    printf("\n퍼즐 상태 (이동 횟수: %d):\n", moveCount);
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

// 퍼즐 저장 함수
void saveGame() {
    FILE *file = fopen(SAVE_FILE, "w");
    if (!file) {
        printf("게임을 저장하는데 실패했습니다!\n");
        return;
    }

    fprintf(file, "%d %d\n", moveCount, (int)(time(NULL) - startTime)); // 이동 횟수, 경과 시간 저장
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fprintf(file, "%d ", puzzle[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("게임이 저장되었습니다!\n");
}

// 저장된 퍼즐 불러오기 함수
void loadGame() {
    FILE *file = fopen(SAVE_FILE, "r");
    if (!file) {
        printf("저장된 게임이 없습니다!\n");
        return;
    }

    int elapsedTime;
    fscanf(file, "%d %d", &moveCount, &elapsedTime);
    startTime = time(NULL) - elapsedTime;  // 기존 경과 시간 유지

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fscanf(file, "%d", &puzzle[i][j]);
            if (puzzle[i][j] == 0) {
                emptyPos.x = i;
                emptyPos.y = j;
            }
        }
    }

    fclose(file);
    printf("게임이 불러와졌습니다!\n");
}

// 이동 처리 함수
void moveTile(char direction) {
    int dx = 0, dy = 0;

    if (direction == 'W' || direction == 'w') dx = -1;
    if (direction == 'S' || direction == 's') dx = 1;
    if (direction == 'A' || direction == 'a') dy = -1;
    if (direction == 'D' || direction == 'd') dy = 1;

    int newX = emptyPos.x + dx;
    int newY = emptyPos.y + dy;

    if (newX >= 0 && newX < SIZE && newY >= 0 && newY < SIZE) {
        puzzle[emptyPos.x][emptyPos.y] = puzzle[newX][newY];
        puzzle[newX][newY] = 0;
        emptyPos.x = newX;
        emptyPos.y = newY;
        moveCount++;
    }
}

// 게임 실행 함수
void playGame() {
    char input;
    startTime = time(NULL);

    while (1) {
        printPuzzle();
        printf("\n이동할 방향 입력 (WASD, S: 저장, L: 불러오기, Q: 종료): ");
        scanf(" %c", &input);

        if (input == 'Q' || input == 'q') {
            printf("\n게임 종료!\n");
            break;
        } else if (input == 'S' || input == 's') {
            saveGame();
        } else if (input == 'L' || input == 'l') {
            loadGame();
        } else {
            moveTile(input);
        }
    }
}

// 메인 함수
int main() {
    char choice;
    printf("새 게임을 시작하려면 'N', 저장된 게임을 불러오려면 'L'을 입력하세요: ");
    scanf(" %c", &choice);

    if (choice == 'L' || choice == 'l') {
        loadGame();
    } else {
        initPuzzle();
    }

    playGame();
    return 0;
}