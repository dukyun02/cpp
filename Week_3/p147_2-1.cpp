#include <stdio.h>

int reverse(int num) {
    int rev = 0;
    while (num > 0) {
        rev = rev * 10 + (num % 10);
        num /= 10;
    }
    return rev;
}

int main() {
    int num, reversedNum;

    printf("12345: ");
    scanf("%d", &num);

    reversedNum = reverse(num);

    printf("54321: %d\n", reversedNum);

    return 0;
}
