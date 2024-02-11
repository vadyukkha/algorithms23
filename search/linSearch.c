#include <stdio.h>
#include <stdint.h>

int64_t linearSearch(int64_t arr[], int64_t size, int64_t target) {
    for (size_t i = 0; i < size; i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

int main() {
    int64_t arr[] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 72, 91};
    int64_t size = sizeof(arr) / sizeof(arr[0]);
    int64_t target = 23;

    int64_t result = linearSearch(arr, size, target);

    if (result != -1)
        printf("Element %lld found at index %lld\n", target, result);
    else
        printf("Element %lld not found in the array\n", target);

    return 0;
}