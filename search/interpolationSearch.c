#include <stdint.h>
#include <stdio.h>

size_t interpolationSearch(int64_t array[], size_t size, int64_t target) {
    if (size == 0) {
        return -1;
    }

    size_t left = 0, right = size - 1, mid;

    while (array[right] != array[left] && target >= array[left] && target <= array[right])
    {
        mid = left + ((target - array[left]) * (right - left) / (array[right] - array[left]));

        if (target == array[mid]) {
            return mid;
        }
        else if (target < array[mid]) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    if (target == array[left]) {
        return left;
    }
    else {
        return -1;
    }
}

int main() {
    int64_t arr[] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 72, 91};
    int64_t size = sizeof(arr) / sizeof(arr[0]);
    int64_t target = 23;

    int64_t result = interpolationSearch(arr, size, target);

    if (result != -1)
        printf("Element %lld found at index %lld\n", target, result);
    else
        printf("Element %lld not found in the array\n", target);

    return 0;
}