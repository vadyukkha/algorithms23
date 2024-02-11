#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MIN(a, b) ((a) < (b)) ? (a) : (b)

void fillArray(int64_t arr[], int64_t size) {
    for (int64_t i = 0; i < size; i++) {
        scanf("%lld", &arr[i]);
    }
}

void printArray(int64_t arr[], int64_t size) {
    for (int64_t i = 0; i < size; i++) {
        printf("%lld ", arr[i]);
    }
    printf("\n");
}

int64_t binSearch(int64_t arr[], int64_t left, int64_t right, int64_t target) {
    if (left > right) return -1;
    printf("\nSearch history: ");
    int64_t l = left, r = right;
    while (l <= r) {
        int64_t mid = l + (r - l)/2;
        printf("%lld(%lld) ", arr[mid], mid);
        if (arr[mid] == target) return mid;
        else if (arr[mid] > target) r = mid - 1;
        else l = mid + 1;
    }
    return -1;
}

int64_t expSearch(int64_t arr[], int64_t size, int64_t target) {
    if (size == 0) {
        return -1;
    }
    int64_t bound = 1;

    printf("Bounds history: ");
    printf("%lld(%d) ", arr[0], 0);

    if (arr[0] > target) return -1;
    else if (arr[0] == target) return 0;

    while (bound < size && arr[bound] <= target) {
        printf("%lld(%lld) ", arr[bound], bound);
        if (arr[bound] == target) return bound;
        bound *= 2;
    }
    
    if (bound < size) printf("%lld(%lld) ", arr[bound], bound);

    if (arr[bound] != target && bound / 2 != size - 1) {
        int64_t l = bound /2 + 1, r = MIN(bound-1, size-1);
        return binSearch(arr, l, r, target);
    }  
    return -1;
}

int main() {
    int64_t n;
    int64_t target;
    scanf("%lld", &n);
    scanf("%lld", &target);

    int64_t *arr = (int64_t*)malloc(n*sizeof(int64_t));
    fillArray(arr, n);

    printf("Initial array: \n");
    printArray(arr,n);

    printf("Target element: %lld\n", target);
    int64_t foundIndex = expSearch(arr, n, target);
    if (foundIndex != -1) {
        printf("\nTarget is found at: %lld\n", foundIndex);
    } else {
        printf("\nNo targets\n");
    }
    free(arr);
    return 0;
}