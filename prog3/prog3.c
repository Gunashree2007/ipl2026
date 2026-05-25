#include <stdio.h>

void printBits(int n) {
    int totalBits = sizeof(int) * 8;
    for (int i = totalBits - 1; i >= 0; i--) {
        int bit = (n >> i) & 1;
        printf("%d", bit);
        if (i % 8 == 0) printf(" ");
    }
    printf("\n");
}

int countOneBits(int n) {
    int count = 0;
    while (n != 0) {
        n = n & (n - 1);
        count++;
    }
    return count;
}

int main() {
    int positiveNum = 12;
    int negativeNum = -12;

    printf("For Positive Number (%d):\n", positiveNum);
    printf("Bits:  ");
    printBits(positiveNum);
    printf("1-Bits count: %d\n\n", countOneBits(positiveNum));

    printf("For Negative Number (%d):\n", negativeNum);
    printf("Bits:  ");
    printBits(negativeNum);
    printf("1-Bits count: %d\n", countOneBits(negativeNum));

    return 0;
}
