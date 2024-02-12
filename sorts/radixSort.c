#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void radix(uint32_t arr[], size_t size); // O(n)
uint32_t mamax(uint32_t arr[], size_t size);
void fillArray(uint32_t arr[], size_t size);
void printArray(uint32_t arr[], size_t size);

int main(){
    size_t n;
    scanf("%lu", &n);
    uint32_t *arrToSort = (uint32_t*)malloc(n * sizeof(uint32_t));
// Only for positive numbers (!)

    fillArray(arrToSort, n);

    radix(arrToSort, n);

    printArray(arrToSort, n);

    free(arrToSort);
    return 0;
}

void radix(uint32_t arr[], size_t size) {
    uint32_t *res_arr = (uint32_t*)malloc(size * sizeof(uint32_t));
    uint32_t max = mamax(arr, size);

    for (int div = 1; max / div > 0; div *= 10){
        int cases[10] = {0}; 

        for (int i = 0; i < size; i++)
            cases[(arr[i] / div) % 10]++;

        for (int i = 1; i < 10; i++)
            cases[i] += cases[i - 1];

        for (int i = size - 1; i > -1; i--)
            res_arr[--cases[(arr[i] / div) % 10]] = arr[i];
        
        for (int i = 0; i < size; i++)
            arr[i] = res_arr[i];
    }
}

uint32_t mamax(uint32_t arr[], size_t size){
    uint32_t max = arr[0];
    for (int i = 1; i < size; i++){
        if (max < arr[i]) 
            max = arr[i];
    }
    return max;
}

void fillArray(uint32_t arr[], size_t size) {
    for (size_t i = 0; i < size; i++)
        scanf("%u", &arr[i]);
}

void printArray(uint32_t arr[], size_t size) {
    for (size_t i = 0; i < size; i++)
        printf("%u ", arr[i]);
}