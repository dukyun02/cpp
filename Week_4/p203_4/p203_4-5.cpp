#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 그림을 나타내는 아스키 아트 (4x4 그림 퍼즐을 위한  아스키 아트)
const string asciiArt[] = {
    " ^_^ ",  // A
    " (o_o) ", // B
    " (o_o) ", // C
    " (o_o) ", // D
    " (^_^) ",  // E
    " (^^^) ",  // F
    " (^_^) ",  // G
    " (o_o) ", // H
    " (._.) ",  // I
    " (o_o) ",  // J
    " (^_^) ",  // K
    " (o_o) ",  // L
    " (__) ",   // M
    " (o_o) ",  // N
    " (^_^) ",  // O
    " (._.) "   // P
};

// 퍼즐 맵 출력 함수 (문자 퍼즐)
void printPuzzle(const vector<vector<string>>& puzzle) {
    for (size_t i = 0; i < puzzle.size(); ++i) {
        for (size_t j = 0; j < puzzle[i].size(); ++j) {
            if (puzzle[i][j] == "0") { // 빈 칸을 나타낼 경우
                cout << "     " << " "; // 빈 칸은 공백으로 표시
            } else {
                cout << puzzle[i][j] << " "; // 각 퍼즐 조각 출력
            }
        }
        cout << endl;
    }
}

// 퍼즐 맵 초기화 함수 (문자 배열로 초기화)
vector<vector<string>> initializePuzzle(int size) {
    vector<vector<string>> puzzle(size, vector<string>(size));

    // 예시로 문자 배열을 4x4에 배치
    int index = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (index < 16) {
                puzzle[i][j] = asciiArt[index++];
            } else {
                puzzle[i][j] = "0"; // 마지막 칸은 빈 칸
            }
        }
    }
    return puzzle;
}

// 퍼즐을 섞는 함수
void shufflePuzzle(vector<vector<string>>& puzzle) {
    int size = puzzle.size();
    for (int i = 0; i < 100; ++i) {
        int x = 0, y = 0;
        // 빈 칸 위치 찾기
        for (int r = 0; r < size; ++r) {
            for (int c = 0; c < size; ++c) {
                if (puzzle[r][c] == "0") {
                    x = r;
                    y = c;
                    break;
                }
            }
        }

        // 빈 칸 주변으로 이동
        int direction = rand() % 4;
        if (direction == 0 && x > 0) swap(puzzle[x][y], puzzle[x-1][y]); // 위
        else if (direction == 1 && x < size - 1) swap(puzzle[x][y], puzzle[x+1][y]); // 아래
        else if (direction == 2 && y > 0) swap(puzzle[x][y], puzzle[x][y-1]); // 왼쪽
        else if (direction == 3 && y < size - 1) swap(puzzle[x][y], puzzle[x][y+1]); // 오른쪽
    }
}

// 이동 함수 (빈 칸 위치와 이동 방향에 따라 퍼즐을 움직이는 함수)
bool movePuzzle(vector<vector<string>>& puzzle, string direction, int& x, int& y) {
    int size = puzzle.size();
    if (direction == "up" && x > 0) {
        swap(puzzle[x][y], puzzle[x-1][y]);
        x--;
        return true;
    } else if (direction == "down" && x < size - 1) {
        swap(puzzle[x][y], puzzle[x+1][y]);
        x++;
        return true;
    } else if (direction == "left" && y > 0) {
        swap(puzzle[x][y], puzzle[x][y-1]);
        y--;
        return true;
    } else if (direction == "right" && y < size - 1) {
        swap(puzzle[x][y], puzzle[x][y+1]);
        y++;
        return true;
    }
    return false; // 유효하지 않은 방향
}

// 메인 함수
int main() {
    int size = 4; // 4x4 퍼즐
    vector<vector<string>> puzzle = initializePuzzle(size); // 퍼즐 초기화
    int x = size - 1, y = size - 1; // 빈 칸 위치 (초기 값은 맨 마지막 칸)
    
    cout << "섞인 퍼즐 상태:" << endl;
    printPuzzle(puzzle);

    string direction;
    while (true) {
        cout << "\n움직일 방향을 입력하세요 (up, down, left, right, exit): ";
        cin >> direction;

        if (direction == "exit") {
            break; // 게임 종료
        }

        if (movePuzzle(puzzle, direction, x, y)) {
            cout << "현재 퍼즐 상태:" << endl;
            printPuzzle(puzzle);
        } else {
            cout << "잘못된 방향입니다." << endl;
        }
    }

    return 0;
}