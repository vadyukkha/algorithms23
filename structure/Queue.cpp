#include <iostream>
#include <stdint.h>

class LinkedListNode {
public:
    int64_t value;
    LinkedListNode* next;
    LinkedListNode* prev;

    // Constructor
    LinkedListNode(int64_t val) : value(val), next(nullptr), prev(nullptr) {}
};

class Queue {
private:
    LinkedListNode* head;
    LinkedListNode* tail;

public:
    Queue() : head(nullptr), tail(nullptr) {}

    void enqueue(int64_t value) {
        LinkedListNode* newNode = new LinkedListNode(value);

        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
        }
    }

    int64_t dequeue() {
        int64_t value = 0;

        if (!isEmpty()) {
            value = tail->value;
            LinkedListNode* newTail = tail->prev;

            delete tail;
            tail = newTail;

            if (tail == nullptr) {
                head = nullptr;
            }
        }
        return value;
    }

    bool isEmpty() {
        return head == nullptr;
    }

    ~Queue() {
        while (head) {
            LinkedListNode* current = head;
            head = head->next;
            delete current;
        }
    }
};

int main() {
    Queue queue;

    int64_t val_1 = 1;
    int64_t val_2 = 22;
    int64_t val_3 = 333;
    int64_t val_4 = 4444;

    int64_t out_val;

    queue.enqueue(val_1);
    std::cout << "enqueue " << val_1 << std::endl;
    queue.enqueue(val_2);
    std::cout << "enqueue " << val_2 << std::endl;

    out_val = queue.dequeue();
    std::cout << "dequeue " << out_val << std::endl;

    queue.enqueue(val_3);
    std::cout << "enqueue " << val_3 << std::endl;
    queue.enqueue(val_4);
    std::cout << "enqueue " << val_4 << std::endl;

    out_val = queue.dequeue();
    std::cout << "dequeue " << out_val << std::endl;
    out_val = queue.dequeue();
    std::cout << "dequeue " << out_val << std::endl;
    out_val = queue.dequeue();
    std::cout << "dequeue " << out_val << std::endl;

    return 0;
}
