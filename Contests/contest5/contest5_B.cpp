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

class Processor {
public:
    int64_t id;
    int64_t end;

    Processor(int64_t id, int64_t end) : id(id), end(end) {}

    bool operator<(const Processor& other) const {
        if (end == other.end) return id < other.id;
        return (end < other.end);
    }
};

class Solution {
private:
    int64_t countCores;
    PriorityQueue<Processor> queue;

public:
    Solution(int64_t countCores) : countCores(countCores), queue(std::vector<Processor>()) {
        std::vector<Processor> processors;
        for (int64_t i = 0; i < countCores; ++i) {
            processors.push_back(Processor(i, 0));
        }
        queue = PriorityQueue<Processor>(processors);
    }

    void scheduleTasks(const std::vector<int64_t>& taskTimes) {
        for (size_t i = 0; i < taskTimes.size(); ++i) {
            Processor curr = queue.extractMin();
            std::cout << curr.id << " " << curr.end << std::endl;
            queue.insert(Processor(curr.id, curr.end + taskTimes[i]));
        }
    }
};

int main() {
    int64_t countCores, countTasks;
    std::cin >> countCores >> countTasks;

    std::vector<int64_t> taskTimes(countTasks);
    for (size_t i = 0; i < countTasks; ++i) {
        std::cin >> taskTimes[i];
    }

    Solution scheduler(countCores);
    scheduler.scheduleTasks(taskTimes);

    return 0;
}