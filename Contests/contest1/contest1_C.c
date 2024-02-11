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

void merge1(int64_t arr[], int64_t left, int64_t mid, int64_t right) {
    int64_t leftRange = mid - left;
    int64_t rightRange = right - mid + 1;

    int64_t *LeftSide = (int64_t*)malloc(sizeof(int64_t)*leftRange);
    int64_t *RightSide = (int64_t*)malloc(sizeof(int64_t)*rightRange);

    for (size_t i = 0; i < leftRange; i++) LeftSide[i] = arr[left + i];
    for (size_t j = 0; j < rightRange; j++) RightSide[j] = arr[mid + j];

    printf("\nLeft part: ");
    for (size_t i = 0; i < leftRange; i++) {
        printf("%lld ", LeftSide[i]);
    }
    printf("\nRight part: ");
    for (size_t j = 0; j < rightRange; j++) {
        printf("%lld ", RightSide[j]);
    }

    size_t i = 0, j = 0, k = left;

    while (i < leftRange && j < rightRange) {
        if (LeftSide[i] <= RightSide[j]) arr[k++] = LeftSide[i++];
        else arr[k++] = RightSide[j++];
    }
    
    while (currNumIsHigh(leftRange, i)) arr[k++] = LeftSide[i++];
    while (currNumIsHigh(rightRange, j)) arr[k++] = RightSide[j++];

    printf("\nMerged parts: ");
    for (size_t i = left; i <= right; i++) {
        printf("%lld ", arr[i]);
    }
    printf("\n");

    free(LeftSide);
    free(RightSide);
}

void mergeSort(int64_t arr[], int64_t left, int64_t right) {
    if (left != right) {
        int64_t ost = (right - left)%2==0 ? (right-left)/2 : (right-left)/2+1; 
        int64_t mid = left + ost;
        mergeSort(arr, left, mid-1);
        mergeSort(arr, mid, right);
        merge1(arr, left, mid, right);
    }
}

int main() {
    size_t n;
    scanf("%lu", &n);
    int64_t *arr = (int64_t*)malloc(sizeof(int64_t)*n);
    fillArray(arr, n);
    printf("Initial array: \n");
    printArray(arr, n);
    printf("\n");
    mergeSort(arr, 0, n-1);
    return 0;
}