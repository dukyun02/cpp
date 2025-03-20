#include <iostream>
using namespace std;

int main() {
    int n;

    cout << "1000 미만의 정수를 입력하세요: ";
    cin >> n;

    if (n >= 1000 || n <= 0) {
        cout << "입력값이 1000 미만이 아니거나 잘못된 입력입니다." << endl;
        return 1; 
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i; j >= 1; j--) {
            if (j == 1 && i >= 10) {
                continue;  
            }
            cout << j;
        }
        for (int j = 2; j <= i; j++) {
            if (j == 1 && i >= 10) {
                continue;  
            }
            cout << j;
        }
        cout << endl;  
    }

    return 0;
}
