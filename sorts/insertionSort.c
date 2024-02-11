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

void insertionSort(uint32_t arr[], size_t sizeArr) {
    for (size_t i = 1; i < sizeArr; i++) {
        size_t j = i - 1;
        uint32_t supElement = arr[i];
        while (j >= 0 && currNumIsHigh(arr[j], supElement)) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = supElement;
    }
}

int main() {
    size_t n;
    scanf("%lu", &n);

    uint32_t *arrayToSort = (uint32_t*)malloc(n * sizeof(uint32_t));
    
    fillArray(arrayToSort, n);

    insertionSort(arrayToSort, n);

    printArray(arrayToSort, n);

    free(arrayToSort);
    return 0;
}

