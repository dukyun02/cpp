#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ROW 40
#define MAX_COL 80

static int MineMapMask[MAX_ROW][MAX_COL];   // 유저가 보는 화면
static int MineMapLabel[MAX_ROW][MAX_COL];  // 실제 지뢰 위치 및 숫자

int rowSize, colSize;

void initMap(int mineCount) {
    srand(time(NULL));
    // 지뢰 초기화
    for (int i = 0; i < rowSize; ++i)
        for (int j = 0; j < colSize; ++j)
            MineMapLabel[i][j] = 0;

    // 지뢰 배치
    for (int m = 0; m < mineCount; ) {
        int r = rand() % rowSize;
        int c = rand() % colSize;
        if (MineMapLabel[r][c] == -1) continue;
        MineMapLabel[r][c] = -1;
        m++;
        // 주변 숫자 증가
        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                int nr = r + dr, nc = c + dc;
                if (nr >= 0 && nr < rowSize && nc >= 0 && nc < colSize && MineMapLabel[nr][nc] != -1)
                    MineMapLabel[nr][nc]++;
            }
        }
    }

    // 마스크 초기화
    for (int i = 0; i < rowSize; ++i)
        for (int j = 0; j < colSize; ++j)
            MineMapMask[i][j] = 0;
}

void printMap() {
    printf("   ");
    for (int j = 0; j < colSize; ++j)
        printf("%2d ", j);
    printf("\n");

    for (int i = 0; i < rowSize; ++i) {
        printf("%2d ", i);
        for (int j = 0; j < colSize; ++j) {
            if (MineMapMask[i][j] == 0) printf(" . ");
            else if (MineMapMask[i][j] == 1) {
                if (MineMapLabel[i][j] == -1) printf(" * ");
                else printf(" %d ", MineMapLabel[i][j]);
            }
            else if (MineMapMask[i][j] == 2) printf(" F ");
        }
        printf("\n");
    }
}

void dig(int r, int c) {
    if (r < 0 || r >= rowSize || c < 0 || c >= colSize || MineMapMask[r][c] != 0)
        return;

    MineMapMask[r][c] = 1;
    if (MineMapLabel[r][c] == 0) {
        for (int dr = -1; dr <= 1; ++dr)
            for (int dc = -1; dc <= 1; ++dc)
                dig(r + dr, c + dc);
    }
}

void toggleFlag(int r, int c) {
    if (MineMapMask[r][c] == 0)
        MineMapMask[r][c] = 2;
    else if (MineMapMask[r][c] == 2)
        MineMapMask[r][c] = 0;
}

int main() {
    int mineCount;
    printf("지뢰 맵의 크기를 입력하세요 (열 행): ");
    scanf("%d %d", &colSize, &rowSize);
    if (colSize > MAX_COL || rowSize > MAX_ROW) {
        printf("크기 초과! 최대: %d x %d\n", MAX_COL, MAX_ROW);
        return 1;
    }

    printf("지뢰의 개수를 입력하세요: ");
    scanf("%d", &mineCount);

    initMap(mineCount);
    char input[10];
    int x, y;

    while (1) {
        printMap();
        printf("입력 --> ");
        scanf("%s", input);

        if (input[0] == 'p') {
            scanf("%d %d", &x, &y);
            toggleFlag(y, x);
        } else {
            x = atoi(input);
            scanf("%d", &y);
            if (MineMapLabel[y][x] == -1) {
                printf("지뢰를 밟았습니다! 게임 종료!\n");
                MineMapMask[y][x] = 1;
                printMap();
                break;
            }
            dig(y, x);
        }
    }

    return 0;
}