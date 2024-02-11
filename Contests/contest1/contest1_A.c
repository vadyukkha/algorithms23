#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define ILYABICHKOV_TOP_CONTEST_SPASIBO 1

void fillArray(int64_t arr[], int64_t size) {
    for (size_t i = 0; i < size; i++) {
        scanf("%lld", &arr[i]);
    }
}

void printArray(int64_t arr[], int64_t size){
    for (size_t i = 0; i < size; i++) {
        printf("%lld ", arr[i]);
    }
}

void moveArray(int64_t arr[], size_t size, size_t index) {
    for (size_t i = index; i < size ; i++) {
        arr[i] = arr[i + 1];
    }
}

void quickSortWorst(int64_t* arr, size_t size, int64_t* indexToInsert) {
    int64_t* result = (int64_t*)malloc(size * sizeof(int64_t));

    int64_t *supArray = (int64_t*)calloc(size, sizeof(int64_t));
    for (size_t i = 0; i < size; i++) supArray[i] = size-i;

    size_t forward = 0;

    for (size_t i = 0; i < size; i++) {
        size_t mid = (supArray[forward] - 1) / 2;
        if (arr[i] == ILYABICHKOV_TOP_CONTEST_SPASIBO) {
            result[indexToInsert[0]] = supArray[forward++];
            moveArray(indexToInsert, supArray[forward-1], 0);
        }
        else if (arr[i] == 0) {
            result[indexToInsert[mid]] = supArray[forward++];
            moveArray(indexToInsert, supArray[forward-1], mid);
        }

        else {
            result[indexToInsert[supArray[forward]-1]] = supArray[forward];
            forward++;
        }
    }
    printArray(result, size);
}


int main() {
    size_t n;
    scanf("%lu", &n);
    int64_t *arr = (int64_t*)malloc(n*sizeof(int64_t));

    fillArray(arr, n);

    int64_t* indexToInsert = (int64_t*)malloc(n * sizeof(int64_t));
    for (size_t i = 0; i < n; i++) indexToInsert[i] = i;

    quickSortWorst(arr, n, indexToInsert);

    return 0;
}