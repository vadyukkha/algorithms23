#include <stdio.h> 
#include <math.h>
#include <stdint.h>
#include <iostream>
#include <stdbool.h>

int64_t gcd(int64_t a, int64_t b){
    if (b == 0) {
        return a;
    }
    return gcd(b, a%b);
}

int64_t powerMod(int64_t base, int64_t exp, int64_t mod) {
    int64_t res = 1;
    while (exp > 0) {
        if (exp%2==1) {
            res = (res * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

void ferma(int64_t x){
    printf("Fermat test: ");
    bool flag = true;
    int64_t cond = 0;
    int64_t count = 0;
    for (int64_t a = 1; a < x; a++) {
        if (gcd(a, x) != 1) {
            cond++;
            flag = false;
        }
        else if (powerMod(a, x - 1, x) != 1) {
            cond++;
            flag = false;
        }
        else count++;
    }
    if (flag) {
        printf("True %lld %lld", cond, count);
    } else {
        printf("False %lld %lld", cond, count);
    }
}

void MillerRabinTest(int64_t n) {
    printf("Miller-Rabin test: ");
    bool flag = true;
    int64_t cond = 0;
    int64_t t = n - 1;
    int64_t s = 0;

    while (!(t%2)) {
        t /= 2;
        s++;
    }

    int64_t usl1 = 0, usl2 = 0;

    for (int64_t a = 1; a < n; a++) {  
        int64_t x = powerMod(a, t,n);
        if (x == 1 || x == n - 1) {
            usl1++;
            continue;
        }

        for (int64_t r = 1; r < s; r++) {
            x = powerMod(x,2,n);
            if (x == 1) {
                flag = false;
            }
            if (x == n - 1) {
                usl2++;
                break;
            }
        }

        if (x != n - 1 || x == 1) {
            flag = false;
            cond++;
        }
    }

    if (flag) {
        printf("True %lld %lld %lld\n", cond, usl1/2, usl2+usl1/2);
    } else {
        printf("False %lld %lld %lld\n", cond, usl1/2, usl2+usl1/2);
    }
}

int main(){ 
    int64_t n;
    scanf("%lld", &n);
    MillerRabinTest(n);
    ferma(n);
    return 0; 
}