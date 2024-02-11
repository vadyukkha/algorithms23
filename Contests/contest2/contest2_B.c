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
    printf("\n");
}

size_t binSearch(int32_t arr[], size_t size, int32_t target) {
    printf("Search history: ");
    size_t l = 0, r = size - 1;
    while (l <= r) {
        size_t mid = l + (r - l)/2;
        printf("%d(%lu) ", arr[mid], mid);
        if (arr[mid] == target) return mid;
        else if (arr[mid] > target) r = mid - 1;
        else l = mid + 1;
    }
    return -1;
}

int main() {
    size_t n;
    int32_t target;
    scanf("%lu", &n);
    scanf("%d", &target);

    int32_t *arr = (int32_t*)malloc(n*sizeof(int32_t));
    fillArray(arr, n);

    printf("Initial array: \n");
    printArray(arr,n);

    printf("Target element: %d\n", target);
    size_t foundIndex = binSearch(arr, n, target);
	if (foundIndex != -1) {
        printf("\nTarget is found at: %lu\n", foundIndex);
    } else {
        printf("\nNo targets\n");
    }
    return 0;
}