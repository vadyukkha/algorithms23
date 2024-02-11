#include <iostream>
#include <stdint.h>

class ListNode {
public:
    int64_t value;
    ListNode* next;

    // Constructor
    ListNode(int64_t val) : value(val), next(nullptr) {}
};

class LinkedList {
private:
    ListNode* head;

    ListNode* getTailNode() {
        ListNode* tail = head;
        while (tail && tail->next) {
            tail = tail->next;
        }
        return tail;
    }

    ListNode* getNodeByValue(int64_t value) {
        ListNode* current = head;
        while (current && current->value != value) {
            current = current->next;
        }
        return current;
    }

    ListNode* getPreviousNodeByValue(int64_t value) {
        ListNode* current = head;
        while (current && current->next && current->next->value != value) {
            current = current->next;
        }
        return current;
    }

public:
    // Constructor
    LinkedList() : head(nullptr) {}

    void insertHead(int64_t value) {
        ListNode* newNode = new ListNode(value);
        newNode->next = head;
        head = newNode;
    }

    void insertTail(int64_t value) {
        ListNode* tail = getTailNode();
        if (!tail) {
            head = new ListNode(value);
        } else {
            tail->next = new ListNode(value);
        }
    }

    void insertAfterValue(int64_t valueToInsertAfter, int64_t value) {
        ListNode* nodeToInsertAfter = getNodeByValue(valueToInsertAfter);
        if (nodeToInsertAfter) {
            ListNode* newNode = new ListNode(value);
            newNode->next = nodeToInsertAfter->next;
            nodeToInsertAfter->next = newNode;
        } else {
            insertTail(value);
        }
    }

    void insertBeforeValue(int64_t valueToInsertBefore, int64_t value) {
        ListNode* previousNode = getPreviousNodeByValue(valueToInsertBefore);
        if (previousNode) {
            ListNode* newNode = new ListNode(value);
            newNode->next = previousNode->next;
            previousNode->next = newNode;
        } else {
            insertHead(value);
        }
    }

    void deleteValue(int64_t valueToDelete) {
        ListNode* previousNode = getPreviousNodeByValue(valueToDelete);
        if (previousNode) {
            ListNode* nodeToDelete = previousNode->next;
            previousNode->next = nodeToDelete->next;
            free(nodeToDelete);
        }
    }

    void printList() {
        ListNode* current = head;
        while (current) {
            std::cout << current->value << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    ~LinkedList() {
        while (head) {
            ListNode* current = head;
            head = head->next;
            delete current;
        }
    }
};

int main() {
    LinkedList myList;
    myList.insertHead(3);
    myList.insertTail(5);
    myList.insertAfterValue(3, 7);
    myList.insertBeforeValue(5, 9);
    myList.printList();

    myList.deleteValue(7);
    myList.printList();

    return 0;
}