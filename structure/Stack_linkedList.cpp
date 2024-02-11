#include <iostream>
#include <stdint.h>

class LinkedListNode {
public:
    int64_t value;
    LinkedListNode* next;

    LinkedListNode(int64_t val) : value(val), next(nullptr) {}
};

template <typename T>
class Stack {
private:
    LinkedListNode* head;

public:
    Stack() : head(nullptr) {}

    bool isEmpty() {
        return head == nullptr;
    }

    void push(int64_t value) {
        LinkedListNode* newHead = new LinkedListNode(value);
        newHead->next = head;
        head = newHead;
    }

    T top() {
        return head->value;
    }

    T pop() {
        if (!isEmpty()) {
            T value = head->value;
            LinkedListNode* newHead = head->next;
            delete head;
            head = newHead;
            return value;
        }

        return 0;
    }

    ~Stack() {
        while (head) {
            LinkedListNode* current = head;
            head = head->next;
            free(current);
        }
    }
};

int main() {
    Stack<int64_t> stack;

    int64_t val1 = 10;
    int64_t val2 = 20;
    int64_t val3 = 30;

    stack.push(val1);
    stack.push(val2);
    stack.push(val3);

    std::cout << "Top element: " << stack.top() << std::endl;

    while (!stack.isEmpty()) {
        std::cout << "Popped element: " << stack.pop() << std::endl;
    }

    return 0;
}