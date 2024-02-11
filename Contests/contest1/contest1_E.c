#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void fillArray(int32_t arr[], size_t size) {
    for (size_t i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
}

void printArray(int32_t arr[], size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
}

size_t partition(int32_t arr[], size_t left, size_t right, size_t size) {
    size_t mid = (left+right)/2;
    int32_t pivot = arr[mid];

    printf("\nPivot index: %lu , pivot element: %d\n", mid, pivot);
    int32_t *buff = (int32_t*)calloc((size), sizeof(int32_t));

    size_t ind = 0;
    size_t indexToReturn = 0;

    for (size_t i = 0; i <= right; i++) {
        if (arr[i] < pivot) buff[ind++] = arr[i];
    }

    for (size_t i = 0; i <= right; i++) {
        if (arr[i] == pivot) {
            buff[ind] = arr[i];
            //printf("ind = %lu - buff[i] = %d\n", ind, buff[ind]);
            indexToReturn = ind;
            ind++;
        }
    }

    //printf("Index to return: %lu\n", indexToReturn);
    for (size_t i = 0; i <= right; i++) {
        if (arr[i] > pivot) buff[ind++] = arr[i];
    }

    //buff[ind++] = pivot;
    for (size_t i = left; i <= right; i++) {
        arr[i] = buff[i];
    }

    printf("Array after partition: ");
    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return indexToReturn;
}

void quickSort(int32_t arr[], size_t left, size_t right, size_t n) {
    if (left < right) {
        size_t mid = partition(arr, left, right, n);
        if (mid > left) quickSort(arr, left, mid-1, n);
        quickSort(arr, mid+1, right, n);
    }
}

int main() {
    size_t n;
    scanf("%lu", &n);
    int32_t *arrToSort = (int32_t*)malloc(n * sizeof(int32_t));
    fillArray(arrToSort, n);

    printf("Initial array: \n");
    printArray(arrToSort, n);
    printf("\n");
    quickSort(arrToSort, 0, n-1, n);

    free(arrToSort);
    return 0;
}