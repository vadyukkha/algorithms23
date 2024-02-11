#include <iostream>
#include <vector>
#include <algorithm>

class Pair {
public:
    int64_t key;
    int64_t value;

    Pair(const int64_t& key, const int64_t& value) : key(key), value(value) {}
};

template <typename T>
class BinaryMinHeap {
private:
    std::vector<T> heap;
    std::vector<Pair> result;

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

    void siftDownContest(int64_t i) {
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
            Pair pair(i, minIndex);
            result.push_back(pair);
            siftDownContest(minIndex);
        }
    }

public:
    // BinaryMinHeap(std::vector<T>& array) {
    //     heap = array;
    //     for (int64_t i = heap.size() / 2 - 1; i >= 0; --i) {
    //         siftDown(i);
    //     }
    // }

    void HeapifyContest(const std::vector<T>& array) {
        heap = array;
        for (int64_t i = heap.size() / 2 - 1; i >= 0; --i) {
            siftDownContest(i);
        }
        std::cout << result.size() << std::endl;
        if (result.empty()) return;
        for (const Pair &pair : result) {
            std::cout << pair.key << " " << pair.value << std::endl;
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
};

int main() {
    int64_t n, temp;
    std::cin >> n;
    std::vector<int64_t> arrayToHeap;
    for (size_t i = 0; i < n; i++) {
        std::cin >> temp;
        arrayToHeap.push_back(temp);
    }
    
    BinaryMinHeap<int64_t> minHeap;
    minHeap.HeapifyContest(arrayToHeap);
    return 0;
}