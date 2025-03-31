#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

// 게임 정보를 저장할 구조체
struct Game {
    char name[50];  // 게임 이름 (최대 50자)
    int score;      // 점수

    // 게임 정보 출력 함수
    void print() const {
        cout << "게임 이름: " << name << ", 점수: " << score << endl;
    }
};

// 이진 파일에 저장하는 함수
void saveRankingToFile(const vector<Game>& ranking) {
    ofstream outFile("ranking.dat", ios::binary); // 이진 모드로 파일 열기

    if (!outFile) {
        cout << "파일 열기 실패!" << endl;
        return;
    }

    int size = ranking.size();
    outFile.write(reinterpret_cast<char*>(&size), sizeof(size)); // 랭킹의 크기 먼저 저장

    // 게임 정보 하나씩 저장
    for (const auto& game : ranking) {
        outFile.write(reinterpret_cast<const char*>(&game), sizeof(game));
    }

    outFile.close();
    cout << "랭킹이 파일에 저장되었습니다." << endl;
}

// 이진 파일에서 랭킹을 읽어오는 함수
vector<Game> loadRankingFromFile() {
    ifstream inFile("ranking.dat", ios::binary); // 이진 모드로 파일 열기

    vector<Game> ranking;

    if (!inFile) {
        cout << "파일 열기 실패 또는 파일이 존재하지 않습니다." << endl;
        return ranking;
    }

    int size;
    inFile.read(reinterpret_cast<char*>(&size), sizeof(size)); // 랭킹 크기 읽기

    ranking.resize(size);  // 랭킹 크기만큼 벡터 크기 조정

    // 게임 정보 하나씩 읽어오기
    for (int i = 0; i < size; ++i) {
        inFile.read(reinterpret_cast<char*>(&ranking[i]), sizeof(Game));
    }

    inFile.close();
    return ranking;
}

// 랭킹을 점수 기준으로 내림차순 정렬하는 함수
void sortRanking(vector<Game>& ranking) {
    sort(ranking.begin(), ranking.end(), [](const Game& a, const Game& b) {
        return a.score > b.score; // 내림차순으로 점수 비교
    });
}

// 상위 10개의 랭킹을 출력하는 함수
void printRanking(const vector<Game>& ranking) {
    int rankCount = min(10, (int)ranking.size());
    for (int i = 0; i < rankCount; ++i) {
        cout << "랭킹 " << (i + 1) << ": ";
        ranking[i].print();
    }
}

// 랭킹에 새로운 게임 추가 함수
void addGameToRanking(vector<Game>& ranking, const Game& newGame) {
    // 새로운 게임 추가
    ranking.push_back(newGame);

    // 랭킹을 점수 기준으로 내림차순 정렬
    sortRanking(ranking);

    // 상위 10개만 남기기
    if (ranking.size() > 10) {
        ranking.resize(10);
    }
}

int main() {
    vector<Game> ranking = loadRankingFromFile(); // 파일에서 랭킹 로드

    while (true) {
        cout << "\n1. 새로운 게임 기록 추가\n2. 랭킹 보기\n3. 종료\n";
        int choice;
        cout << "선택: ";
        cin >> choice;

        if (choice == 1) {
            Game newGame;
            cout << "게임 이름을 입력하세요: ";
            cin.ignore();  // 버퍼 비우기
            cin.getline(newGame.name, 50);  // 게임 이름 입력 받기
            cout << "점수를 입력하세요: ";
            cin >> newGame.score;

            addGameToRanking(ranking, newGame); // 랭킹에 게임 추가
            saveRankingToFile(ranking);  // 파일에 저장
        } else if (choice == 2) {
            cout << "\n현재 랭킹:" << endl;
            printRanking(ranking);  // 랭킹 출력
        } else if (choice == 3) {
            break;  // 종료
        } else {
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }
    }

    return 0;
}