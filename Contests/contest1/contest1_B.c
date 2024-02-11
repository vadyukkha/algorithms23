#include <stdio.h>
#include <stdint.h>

void binCorrect(int64_t n, int64_t prev, int64_t flag) {
    if (n > 0) {
        int64_t curr = n % 2;
        if (curr != prev || flag) {
            binCorrect(n/2, curr, 0);
            printf("%lld", curr);
        }
        else binCorrect(n/2, curr, 1);
    }
}

void binReverse(int64_t n, int64_t prev, int64_t flag) {
    if (n > 0) {
        int64_t curr = n % 2;
        if (curr != prev || flag) {
            printf("%lld", curr);
            binReverse(n/2, curr, 0);
        }
        else binReverse(n/2, curr, 1);
    }
}

void mRecursion(uint64_t n) {
    binCorrect(n, -1, 1);
    printf("\n");
    binReverse(n, -1, 1);
    printf("\n");
}

int main() {
    uint64_t number;
    scanf("%lld", &number);
    mRecursion(number);
    return 0;
}