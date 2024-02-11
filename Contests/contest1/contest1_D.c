#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define MAX_SIZE 25

int32_t data[MAX_SIZE][MAX_SIZE][MAX_SIZE];

int64_t LRecursion(int64_t a, int64_t b, int64_t c) {
    if (a <= 0 || b <= 0 || c <= 0) return 1;
    else if (a > 20 || b > 20 || c > 20) return pow(2, 20);
    if (data[a][b][c] != 0) return data[a][b][c];
    if (a < b && b < c) {
        data[a][b][c] = LRecursion(a, b, c - 1)+LRecursion(a, b - 1, c - 1)-LRecursion(a, b - 1, c);
    } else {
        data[a][b][c] = LRecursion(a-1,b,c)+LRecursion(a - 1, b - 1, c)+LRecursion(a - 1, b, c - 1)-LRecursion(a - 1, b - 1, c - 1);
    }
    return data[a][b][c];
}

int main() {
    int64_t a,b,c;
    scanf("%lld %lld %lld", &a, &b, &c);
    printf("%lld\n", LRecursion(a,b,c));
    return 0;
}