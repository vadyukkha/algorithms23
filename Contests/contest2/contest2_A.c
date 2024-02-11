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

void linearSearch(int32_t arr[], size_t size, int32_t target) {
    int32_t *result = (int32_t*)calloc(size, sizeof(int32_t));
    size_t k = 0;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] == target) {
            result[k++] = i;
        }
    }
    if (k != 0) {
        printf("Target is found at: ");
        printArray(result, k);
    } else {
        printf("No targets");
    }
    free(result);
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
    
    linearSearch(arr, n, target);
    return 0;
}