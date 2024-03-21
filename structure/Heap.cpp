#include <iostream>
#include <vector>

template <typename T>
class BinaryMinHeap {
private:
    std::vector<T> heap;

    int64_t parent(int64_t i) { 
        return (i - 1) / 2; 
    }
    int64_t leftChild(int64_t i) { 
        return 2 * i + 1;
    }
    int64_t rightChild(int64_t i) { 
        return 2 * i + 2; 
    }

    void siftUp(int64_t heapSize) {
        while (heapSize > 0 && heap[heapSize] < heap[parent(heapSize)]) {
            std::swap(heap[heapSize], heap[parent(heapSize)]);
            heapSize = parent(heapSize);
        }
    }

    void siftDown(int64_t i) {
        int64_t minIndex = i;
        int64_t left = leftChild(i);
        int64_t right = rightChild(i);

        if (left < heap.size() && heap[left] < heap[minIndex]) {
            minIndex = left;
        }

        if (right < heap.size() && heap[right] < heap[minIndex]) {
            minIndex = right;
        }

        if (i != minIndex) {
            std::swap(heap[i], heap[minIndex]);
            siftDown(minIndex);
        }
    }

public:
    BinaryMinHeap(std::vector<T>& array) {
        heap = array;
        for (int64_t i = heap.size() / 2 - 1; i >= 0; --i) {
            siftDown(i);
        }
    }

    void insert(T value) {
        heap.push_back(value);
        siftUp(heap.size() - 1);
    }

    T extractMin() {
        T min = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        siftDown(0);

        return min;
    }

    T getMin() {
        return heap[0];
    }

    bool isEmpty() {
        return heap.empty();
    }

    void heapSort() {
        for (int64_t i = heap.size() - 1; i > 0; --i) {
            std::swap(heap[0], heap[i]);
            siftDown(0);
        }
    }
};

int main() {
    int64_t n, temp;
    std::cin >> n;
    std::vector<int64_t> arrayToHeap;
    for (size_t i = 0; i < n; i++) {
        std::cin >> temp;
        arrayToHeap.push_back(temp);
    }
    
    BinaryMinHeap<int64_t> minHeap(arrayToHeap);

    std::cout << "Min element: " << minHeap.getMin() << std::endl;

    std::sort_heap(arrayToHeap.begin(), arrayToHeap.end());

    std::cout << "Sorted elements: ";
    while (!minHeap.isEmpty()) {
        std::cout << minHeap.extractMin() << " ";
    }

    return 0;
}
