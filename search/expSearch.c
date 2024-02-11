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

int64_t exponentialSearch(int64_t arr[], int64_t size, int64_t target) {
    if (arr[0] == target)
        return 0;

    int64_t i = 1;
    while (i < size && arr[i] <= target) {
        i *= 2;
    }
    return binarySearch(arr, i / 2, (i < size) ? i : size - 1, target);
}

int main() {
    int64_t arr[] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 72, 91};
    int64_t size = sizeof(arr) / sizeof(arr[0]);
    int64_t target = 23;

    int64_t result = exponentialSearch(arr, size, target);

    if (result != -1)
        printf("Element %lld found at index %lld\n", target, result);
    else
        printf("Element %lld not found in the array\n", target);

    return 0;
}
