#include <iostream>
#include <string>
#include <stdint.h>
#include <vector>

template <typename Type>
class Stack {
private:
    std::vector<Type> items;
    int64_t top;

public:
    Stack() : top(-1) {}

    void push(const Type& value) {
        items.push_back(value);
        top++;
    }

    Type pop() {
        Type poppedValue = items[top];
        items.pop_back();
        top--;
        return poppedValue;
    }

    Type peek() {
        return items[top];
    }

    bool isEmpty() {
        return (top == -1);
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

    std::cout << "Top element: " << stack.peek() << std::endl;

    while (!stack.isEmpty()) {
        std::cout << "Popped element: " << stack.pop() << std::endl;
    }

    return 0;
}