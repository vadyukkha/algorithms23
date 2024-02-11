#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define currNumIsHigh(a, b) ((a) > (b)) ? (1) : (0)

void fillArray(int64_t arr[], size_t size) {
    for (size_t i = 0; i < size; i++) {
        scanf("%lld", &arr[i]);
    }
}

void printArray(int64_t arr[], size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("%lld ", arr[i]);
    }
}

void merge(int64_t arr[], int64_t left, int64_t mid, int64_t right) {
    int64_t leftRange = mid - left + 1;
    int64_t rightRange = right - mid;

    int64_t *leftHalf = (int64_t*)malloc(leftRange * sizeof(int64_t));
    int64_t *rightHalf = (int64_t*)malloc(rightRange * sizeof(int64_t));

    for (size_t i = 0; i < leftRange; i++) leftHalf[i] = arr[left + i];
    for (size_t j = 0; j < rightRange; j++) rightHalf[j] = arr[mid + 1 + j];

    size_t i = 0;
    size_t j = 0;
    size_t k = left;

    while (i < leftRange && j < rightRange) {
        if (leftHalf[i] <= rightHalf[j]) {
            arr[k++] = leftHalf[i++];
        } else {
            arr[k++] = rightHalf[j++];
        }
    }

    while (currNumIsHigh(leftRange, i)) {
        arr[k++] = leftHalf[i++];
    }

    while (currNumIsHigh(rightRange, j)) {
        arr[k++] = rightHalf[j++];
    }

    free(leftHalf);
    free(rightHalf);
}

void mergeSort(int64_t arr[], int64_t left, int64_t right) {
    if (left < right) {
        int64_t mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid+1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    size_t n;
    scanf("%lu", &n);

    int64_t *arrToSort = (int64_t*)malloc(n * sizeof(int64_t));

    fillArray(arrToSort, n);

    mergeSort(arrToSort, 0, n - 1);

    printArray(arrToSort, n);

    free(arrToSort);

    return 0;
}
