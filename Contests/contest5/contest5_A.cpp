#include <iostream>
#include <vector>

template <typename T>
class PriorityQueue {
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
        while (heapSize > 0 && heap[heapSize] > heap[parent(heapSize)]) {
            std::swap(heap[heapSize], heap[parent(heapSize)]);
            heapSize = parent(heapSize);
        }
    }

    void siftDown(int64_t i) {
        int64_t minIndex = i;
        int64_t left = leftChild(i);
        int64_t right = rightChild(i);

        if (left < heap.size() && heap[left] > heap[minIndex]) {
            minIndex = left;
        }

        if (right < heap.size() && heap[right] > heap[minIndex]) {
            minIndex = right;
        }

        if (i != minIndex) {
            std::swap(heap[i], heap[minIndex]);
            siftDown(minIndex);
        }
    }

public:
    // PriorityQueue(const std::vector<T>& array) {
    //     heap = array;
    //     for (int64_t i = heap.size() / 2 - 1; i >= 0; --i) {
    //         siftDown(i);
    //     }
    // }

    void insert(T value) {
        heap.push_back(value);
        siftUp(heap.size() - 1);
    }

    T extractMax() {
        T min = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        siftDown(0);

        return min;
    }

    void changePriority(T i, int64_t p) {
        if (p <= heap[i]) return;
        heap[i] = p;
        shiftUp(i);
    }
};

int main() {
    PriorityQueue<int64_t> PQ;
    int64_t n, val;
    std::string oper;
    std::cin >> n;
    for (size_t i = 0; i < n; i++) {
        std::cin >> oper;
        if (oper == "Insert") {
            std::cin >> val;
            PQ.insert(val);
        } else if (oper == "ExtractMax") {
            std::cout << PQ.extractMax() << std::endl;
        }
    }
    return 0;
}