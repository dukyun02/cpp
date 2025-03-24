#include <iostream>

int reverse(int num) {
    int revNum = 0;
    while (num > 0) {
        revNum = revNum * 10 + num % 10; 
        num /= 10; 
    }
    return revNum;
}

int main() {
    int number;
    std::cout << "12345: ";
    std::cin >> number;

    int reversed = reverse(number);
    std::cout << "54321: " << reversed << std::endl;

    return 0;
}