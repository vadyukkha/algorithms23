#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define currNumIsHigh(a, b) ((a) > (b)) ? (1) : (0)

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

void swap(uint32_t *a, uint32_t *b) {
    uint32_t temp = *a;
    *a = *b;
    *b = temp;
}

void selectionSort(uint32_t arr[], size_t sizeArr) {
    for (size_t i = 0; i < sizeArr; i++) {
        uint32_t mnNum = arr[i];
        size_t mnIndex = i;
        for (size_t j = i + 1; j < sizeArr; j++) {
            if (currNumIsHigh(mnNum, arr[j])) {
                mnNum = arr[j];
                mnIndex = j;
            }
        }
        swap(&arr[i], &arr[mnIndex]);
    }
}

int main() {
    size_t n;
    scanf("%lu", &n);
    uint32_t *arrayToSort = (uint32_t*)malloc(n * sizeof(uint32_t));
    fillArray(arrayToSort, n);

    selectionSort(arrayToSort, n);

    printArray(arrayToSort, n);

    free(arrayToSort);
    return 0;
}