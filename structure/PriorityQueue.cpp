#include <iostream>
#include <vector>

template <typename T>
class PriorityQueue {
private:
    std::vector<T> queue;

    int64_t parent(int64_t i) { 
        return (i - 1) / 2; 
    }

    int64_t leftChild(int64_t i) { 
        return 2 * i + 1;
    }

    int64_t rightChild(int64_t i) { 
        return 2 * i + 2; 
    }

    void siftUp(int64_t queueSize) {
        while (queueSize > 0 && queue[queueSize] < queue[parent(queueSize)]) {
            std::swap(queue[queueSize], queue[parent(queueSize)]);
            queueSize = parent(queueSize);
        }
    }

    void siftDown(int64_t i) {
        int64_t minIndex = i;
        int64_t left = leftChild(i);
        int64_t right = rightChild(i);

        if (left < queue.size() && queue[left] < queue[minIndex]) {
            minIndex = left;
        }

        if (right < queue.size() && queue[right] < queue[minIndex]) {
            minIndex = right;
        }

        if (i != minIndex) {
            std::swap(queue[i], queue[minIndex]);
            siftDown(minIndex);
        }
    }

public:
    PriorityQueue(const std::vector<T>& array) {
        queue = array;
        for (int64_t i = queue.size() / 2 - 1; i >= 0; --i) {
            siftDown(i);
        }
    }

    void insert(T value) {
        queue.push_back(value);
        siftUp(queue.size() - 1);
    }

    T extractMin() {
        T min = queue[0];
        queue[0] = queue.back();
        queue.pop_back();
        siftDown(0);

        return min;
    }

    T getMin() {
        return queue[0];
    }

    bool isEmpty() {
        return queue.empty();
    }

    void increaseKey(T i, int64_t p) {
        if (p <= queue[i]) return;
        queue[i] = p;
        siftUp(i);
    }
};


int main() {
    std::vector<int64_t> elements = {5, 2, 8, 1, 6};
    PriorityQueue<int64_t> priorityQueue(elements);

    std::cout << "Min element: " << priorityQueue.getMin() << std::endl;

    priorityQueue.insert(3);

    std::cout << "Min element after insertion: " << priorityQueue.getMin() << std::endl;

    int64_t extractedMin = priorityQueue.extractMin();
    std::cout << "Extracted min element: " << extractedMin << std::endl;

    priorityQueue.increaseKey(2, 10);

    std::cout << "Min element after key increase: " << priorityQueue.getMin() << std::endl;

    return 0;
}