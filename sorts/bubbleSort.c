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

void bubbleSort(uint32_t arr[], size_t sizeArr) {
    for (size_t i = 0; i < sizeArr - 1; i++) {
        for (size_t j = 0; j < sizeArr - 1 - i; j++) {
            if (currNumIsHigh(arr[j], arr[j+1])) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

int main() {
    size_t n;
    scanf("%lu", &n);
    uint32_t *arrToSort = (uint32_t*)malloc(n * sizeof(uint32_t));
    fillArray(arrToSort, n);

    bubbleSort(arrToSort, n);

    printArray(arrToSort, n);

    free(arrToSort);
    return 0;
}