#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <vector>

void printArray(std::vector<int64_t> v) {
    for (size_t i = 0; i < v.size(); i++) {
        printf("%lld ", v[i]);
    }
    printf("\n");
}

bool checkPrime(uint8_t arr[], int64_t left, int64_t right) {
    for (int64_t i = left; i <= right; i++) {
        if (!arr[i]) return true;
    }
    return false;
}

void sieveOfEratosthenes(int64_t left, int64_t right) {
    uint8_t* sieve = (uint8_t*)calloc(right+1, sizeof(uint8_t));
    sieve[0] = 0, sieve[1] = 1;
    int64_t it = 0;
    for (int64_t i = 2; i*i <= right; i++) {
        if (!sieve[i]) {
            std::vector<int64_t> v;
            for (int64_t j = i * i; j <= right; j += i) {
                if (j >= left && !sieve[j]) {
                    v.push_back(j);
                }
                sieve[j] = 1;
            }
            ++it;
            if (!v.empty()) {
                printf("Iteration : %lld\n", it);
                printArray(v);
            }
        }
    }
    printf("Primes :\n");
    if (checkPrime(sieve, left, right)) {
        for (int64_t i = left; i <= right; i++) {
            if (!sieve[i]) printf("%lld ", i);
        }
    } else {
        printf("No primes");
    }
}

int main(){
    int64_t a,b;
    scanf("%lld %lld", &a, &b);
    printf("Start and finish: %lld %lld\n", a,b);
    sieveOfEratosthenes(a,b);
    return 0;
}