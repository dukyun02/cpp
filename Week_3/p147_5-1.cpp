#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PLAYERS 10  // 최대 플레이어 수 제한

// N-연발 권총 설정
int cylinder[100];  // 충분히 큰 배열 (N 크기에 맞게 설정됨)

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
    int position = 0;  // 탄창에서 현재 발사할 위치

    printf("\n게임을 시작합니다! 플레이어 %d부터 시작합니다.\n", currentPlayer + 1);

    while (position < n) {  // 탄창 끝까지 반복
        printf("\n플레이어 %d가 방아쇠를 당깁니다...\n", currentPlayer + 1);
        getchar();  // 사용자 입력(Enter) 대기

        if (cylinder[position] == 1) {
            printf("총알 발사! 플레이어 %d가 탈락했습니다!\n", currentPlayer + 1);
            return;  // 게임 종료
        } else {
            printf("헛방! 플레이어 %d는 살아남았습니다.\n", currentPlayer + 1);
        }

        // 다음 플레이어로 이동
        currentPlayer = (currentPlayer + 1) % players;
        position++;
    }

    printf("\n🎉 모든 총알이 발사되었습니다. 모두 살아남았습니다!\n");
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