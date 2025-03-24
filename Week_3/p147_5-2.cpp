#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PLAYERS 10  // 최대 플레이어 수 제한

// N-연발 권총 탄창 설정
int cylinder[100];  // 충분한 크기의 배열 (N 크기에 맞게 설정됨)

// 랜덤하게 탄창을 채우는 함수
void loadGun(int n, int bullets) {
    for (int i = 0; i < n; i++) {
        cylinder[i] = 0;  // 모든 탄약 슬롯을 빈 상태로 초기화
    }

    // 랜덤한 위치에 탄환 배치
    for (int i = 0; i < bullets; i++) {
        int pos;
        do {
            pos = rand() % n;
        } while (cylinder[pos] == 1);  // 중복 방지
        cylinder[pos] = 1;
    }
}

// 러시안 룰렛 게임 실행 함수
void playGame(int players, int n) {
    int currentPlayer = rand() % players;  // 랜덤한 플레이어부터 시작
    int nextPlayer = (currentPlayer + 1) % players;  // 다음 플레이어
    int position = 0;  // 탄창에서 현재 발사할 위치

    printf("\n게임을 시작합니다! 플레이어 %d부터 시작합니다.\n", currentPlayer + 1);

    while (position < n) {  // 모든 총알이 발사될 때까지 진행
        printf("\n플레이어 %d와 플레이어 %d가 동시에 방아쇠를 당깁니다...\n", currentPlayer + 1, nextPlayer + 1);
        getchar();  // 사용자 입력(Enter) 대기

        int hit1 = cylinder[position];  // 첫 번째 플레이어 총알 여부
        int hit2 = (position + 1 < n) ? cylinder[position + 1] : 0;  // 두 번째 플레이어 총알 여부

        if (hit1 && hit2) {
            printf("두 명 모두 맞았습니다! 플레이어 %d와 플레이어 %d 탈락!\n", currentPlayer + 1, nextPlayer + 1);
            return;  // 게임 종료
        } else if (hit1) {
            printf(" 플레이어 %d가 탈락했습니다!\n", currentPlayer + 1);
            return;  // 게임 종료
        } else if (hit2) {
            printf("플레이어 %d가 탈락했습니다!\n", nextPlayer + 1);
            return;  // 게임 종료
        } else {
            printf(" 헛방! 두 플레이어 모두 살아남았습니다.\n");
        }

        // 다음 두 명의 플레이어 선택
        currentPlayer = (nextPlayer + 1) % players;
        nextPlayer = (currentPlayer + 1) % players;
        position += 2;  // 한 턴에 두 발씩 진행
    }

    printf("\n모든 총알이 발사되었습니다. 모두 살아남았습니다!\n");
}

int main() {
    srand(time(NULL));  // 랜덤 시드 설정

    int n, bullets, players;

    // 사용자 입력 받기
    printf("러시안 룰렛 게임을 시작합니다!\n");
    printf("사용할 N-연발 권총의 크기를 입력하세요: ");
    scanf("%d", &n);

    printf("플레이어 수를 입력하세요 (최소 2명): ");
    scanf("%d", &players);
    if (players < 2 || players > MAX_PLAYERS) {
        printf("잘못된 인원 수입니다! 최소 2명 이상, 최대 %d명까지 가능합니다.\n", MAX_PLAYERS);
        return 1;
    }

    printf("탄환 개수를 입력하세요 (1 ~ %d): ", n - 1);
    scanf("%d", &bullets);
    if (bullets < 1 || bullets >= n) {
        printf("탄환 개수는 1개 이상 %d개 이하로 설정해야 합니다.\n", n - 1);
        return 1;
    }

    // 탄창 설정
    loadGun(n, bullets);

    // 게임 실행
    playGame(players, n);

    return 0;
}