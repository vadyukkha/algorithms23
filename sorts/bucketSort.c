#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define currNumIsHigh(a, b) ((a) > (b)) ? (1) : (0)
#define MAX(x, y) ((x) > (y)) ? (x) : (y)
#define MIN(x, y) ((x) < (y)) ? (x) : (y)

void fillArray(uint32_t arr[], size_t size) {
    for (size_t i = 0; i < size; i++) {
        scanf("%u", &arr[i]);
    }
}

void printArray(uint32_t arr[], size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("%u ", arr[i]);
    }
}

void swap(uint32_t *a, uint32_t *b) {
    uint32_t temp = *a;
    *a = *b;
    *b = temp;
}

void selectionSort(uint32_t arr[], size_t sizeArr) {
    for (size_t i = 0; i < sizeArr; i++) {
        uint32_t mnNum = arr[i];
        size_t mnIndex = i;
        for (size_t j = i + 1; j < sizeArr; j++) {
            mnNum = (currNumIsHigh(mnNum, arr[i])) ? arr[j] : mnNum;
            mnIndex = (currNumIsHigh(mnNum, arr[j])) ? j : mnIndex;
        }
        swap(&arr[i], &arr[mnIndex]);
    }
}

void insertionSort(uint32_t arr[], size_t sizeArr) {
    size_t j;
    for (size_t i = 1; i < sizeArr; i++) {
        uint32_t supElement = arr[i];
        j = i - 1;
        while (j >= 0 && currNumIsHigh(arr[j], supElement)) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = supElement;
    }
}

void bucketSort(uint32_t arr[], size_t sizeArr, uint32_t start, uint32_t end, size_t n_KOROBOK)  {
    uint32_t **korobki = (uint32_t**)malloc(n_KOROBOK * sizeof(uint32_t*));
    size_t *sizeKorobok = (size_t*)calloc(n_KOROBOK, sizeof(size_t));
    uint32_t rangeKorobki = (start-end)/n_KOROBOK + 1;

    for (size_t i = 0; i < n_KOROBOK; i++) {
        korobki[i] = (uint32_t*)malloc(sizeArr * sizeof(uint32_t));
    }

    for (size_t i = 0; i < sizeArr; i++) {
        size_t indexKorobki = (arr[i] - start)/rangeKorobki;
        korobki[indexKorobki][sizeKorobok[indexKorobki]] = arr[i];
        sizeKorobok[indexKorobki]++;
    }

    size_t index = 0;
    for (size_t i = 0; i < n_KOROBOK; i++) {
        insertionSort(korobki[i], sizeKorobok[i]);
        for (size_t j = 0; j < sizeKorobok[i]; j++) {
            arr[index + j] = korobki[i][j];
        }
        index += sizeKorobok[i];
        free(korobki[i]);
    }

    free(korobki);
    free(sizeKorobok);
}

int main() {
    size_t n;
    scanf("%lu", &n);
    uint32_t *arrayToSort = (uint32_t*)malloc(n * sizeof(uint32_t));
    fillArray(arrayToSort, n);

    uint32_t maxItem = arrayToSort[0], minItem = arrayToSort[0];
    for (size_t i = 0; i < n; i++) {
        maxItem = MAX(maxItem, arrayToSort[i]);
        minItem = MIN(minItem, arrayToSort[i]);
    }

    bucketSort(arrayToSort, n, minItem, maxItem, 2*n);

    printArray(arrayToSort, n);

    free(arrayToSort);
    return 0;
}