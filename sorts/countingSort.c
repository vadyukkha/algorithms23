#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX(x, y) ((x) > (y)) ? (x) : (y)

void fillArray(uint32_t arr[], size_t size) {
    for (size_t i = 0; i < size; i++) {
        scanf("%u", &arr[i]);
    }
}

void printArray(uint32_t arr[], size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("%u ", arr[i]);
    }
}

void countingSort(uint32_t arr[], size_t sizeArr) {
    uint32_t maxNum = 0;

    for (size_t i = 0; i < sizeArr; i++) {
        maxNum = MAX(maxNum, arr[i]);
    }

    uint32_t *countsOfNum = (uint32_t*)calloc((maxNum+1), sizeof(uint32_t));

    for (size_t i = 0; i < sizeArr; i++) {
        countsOfNum[ arr[i] ]++;
    }

    uint32_t *arrForResult = (uint32_t*)malloc(sizeArr * sizeof(uint32_t));

    size_t Index = 0;

    for (size_t i = 0; i <= maxNum; i++) {
        while (countsOfNum[i] > 0) {
            arrForResult[Index++] = i;
            countsOfNum[i]--;
        }
    }

    printArray(arrForResult, sizeArr);

    free(arrForResult);
    free(countsOfNum);   
}

int main() {
    size_t n;
    scanf("%lu", &n);
    uint32_t *arrayToSort = (uint32_t*)malloc(n * sizeof(uint32_t));
    fillArray(arrayToSort, n);

    countingSort(arrayToSort, n);

    free(arrayToSort);
    return 0;
}