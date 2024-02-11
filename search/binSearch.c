#include <stdio.h>
#include <stdint.h>

int64_t binarySearch(int64_t arr[], int64_t left, int64_t right, int64_t target) {
    while (left <= right) {
        int64_t mid = left + (right - left) / 2;

        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }

    return -1;
}

int main() {
    int64_t arr[] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 72, 91};
    int64_t size = sizeof(arr) / sizeof(arr[0]);
    int64_t target = 23;

    int64_t result = binarySearch(arr, 0, size, target);

    if (result != -1)
        printf("Element %lld found at index %lld\n", target, result);
    else
        printf("Element %lld not found in the array\n", target);

    return 0;
}
