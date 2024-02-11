#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TRUE 1

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

void swap2(uint32_t *a, uint32_t *b) {
    size_t buff = *a;
    *a = *b;
    *b = buff;
}

size_t partitionHoar(uint32_t arr[], size_t left, size_t right) {
    uint32_t mid = arr[(left+right)/2];
    size_t i = left, j = right;
    while (TRUE) {
        while (arr[i] < mid) ++i;
        while (arr[j] > mid) --j;
        if (i >= j) return j;
        swap2(&arr[i++], &arr[j--]);
    }
}

size_t partitionLomuto(uint32_t arr[], size_t left, size_t right) {
    size_t mid = (left+right)/2;
    uint32_t pivot = arr[mid];

    size_t index = left - 1;
    for (size_t j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            index++;
            if (index != j) swap2(&arr[j], &arr[index]);
        }
    }

    swap2(&arr[index+1], &arr[right]);
    return (index+1);
}

void quickSort(uint32_t arr[], size_t left, size_t right, size_t n) {
    if (left < right) {
        size_t mid = partitionLomuto(arr,left, right);
        quickSort(arr, left, mid, n);
        quickSort(arr, mid+1, right,n);
    }
}

int main() {
    size_t n;
    scanf("%lu", &n);
    uint32_t *arrToSort = (uint32_t*)malloc(n * sizeof(uint32_t));
    fillArray(arrToSort, n);

    quickSort(arrToSort, 0, n-1, n);

    printArray(arrToSort, n);

    free(arrToSort);
    return 0;
}