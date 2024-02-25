#include <iostream>
#include <vector>
#include <limits>

class Pair {
public:
    int64_t index_, cost_;

    Pair(const int64_t &X, const int64_t &Y) : index_(X), cost_(Y) {}

    friend std::ostream& operator<<(std::ostream& os, const Pair& pair) {
        os << "Index: " << pair.index_ << " Costs: " << pair.cost_;
        return os;
    }
};

template<typename T>
class Node {
public:
    T value_;
    Node *prev_;
    Node *next_;
    size_t size_;

    Node(const T &value) : value_(value), prev_(nullptr), next_(nullptr), size_(0) {}

    friend std::ostream& operator<<(std::ostream& os, const Node* node) {
        if (node == nullptr) {
            os << "None";
            return os;
        }

        while (node) {
            os << node->value_ << " ";
            node = node->next_;
        }

        return os;
    }
};

template<typename T>
class LinkedList {
public:
    LinkedList() : head_(nullptr), tail_(nullptr) {}

    void pushBack(const T &value) {
        Node<T> *newNode = new Node<T>(value);
        if (!head_) {
            head_ = tail_ = newNode;
        } else {
            newNode->prev_ = tail_;
            tail_->next_ = newNode;
            tail_ = newNode;
        }
        head_->size_++;
    }

    void popFront() {
        if (head_) {
            head_->size_--;
            Node<T> *temp = head_;
            head_ = head_->next_;
            delete temp;
        }
    }

    T getValue() {
        return head_->value_;
    }

    size_t size() const {
        return head_->size_;
    }

    Node<T> *getHead() const {
        return head_;
    }

    void printList() const {
        Node<T> *current = head_;
        while (current) {
            std::cout << current->value_ << " ";
            current = current->next_;
        }
        std::cout << std::endl;
    }

    bool empty() const {
        return head_ == nullptr;
    }

    LinkedList<T>& operator=(const LinkedList<T> &other) {
        if (this != &other) {
            Node<T> *current = head_;
            Node<T> *nextNode = nullptr;

            while (current) {
                nextNode = current->next_;
                delete current;
                current = nextNode;
            }
            head_ = tail_ = nullptr;

            Node<T> *otherCurrent = other.head_;
            while (otherCurrent) {
                pushBack(otherCurrent->value_);
                otherCurrent = otherCurrent->next_;
            }
        }
        return *this;
    }


    ~LinkedList() {
        Node<T> *current = head_;
        Node<T> *nextNode = nullptr;

        while (current) {
            nextNode = current->next_;
            delete current;
            current = nextNode;
        }
    }

private:
    Node<T> *head_;
    Node<T> *tail_;
};

class Salesman {
 public:
    Salesman(const size_t& size) : size_(size) {
        costs_.reserve(size);
    }

    void create() {
        int64_t cost;
        for (size_t i = 0; i < size_; i++) {
            for (size_t j = 0; j < size_; j++) {
                std::cin >> cost;
                if (cost != 0) {
                    costs_[i].pushBack(Pair(j, cost));
                }
            }
        }
    }

    void print() const {
        for (size_t i = 0; i < size_; i++) {
            std::cout << i << " - ";
            costs_[i].printList();
        }
    }

    void traversal() {
        LinkedList<size_t> pathAnswer;
        int64_t finalCost = std::numeric_limits<int64_t>::max();
        for (size_t i = 0; i < size_; i++) {
            traversalUtil(i, pathAnswer, finalCost);
        }

        if (finalCost == 0 || finalCost == std::numeric_limits<int64_t>::max()) {
            std::cout << "Lost" << std::endl;
        } else {
            std::cout << "Path: " << std::endl;
            pathAnswer.printList();
            std::cout << "Cost: " << finalCost << std::endl;
        }
    }
    
 private:
    size_t size_;
    std::vector<LinkedList<Pair>> costs_;

    void traversalUtil(const size_t& value, LinkedList<size_t>& pathAnswer, int64_t& finalCost) {
        LinkedList<size_t> path;
        std::vector<bool> visited(size_, false);
        size_t currentCity = value;
        int64_t totalCost = 0;

        path.pushBack(currentCity);
        visited[currentCity] = true;

        while (path.size() < size_) {
            int64_t minCost = std::numeric_limits<int64_t>::max();
            int64_t nextCity = -1;

            Node<Pair>* current = costs_[currentCity].getHead();
            while (current) {
                size_t nextNode = current->value_.index_;
                int64_t cost = current->value_.cost_;
                if (!visited[nextNode] && cost < minCost) {
                    minCost = cost;
                    nextCity = nextNode;
                }
                current = current->next_;
            }

            if (nextCity == -1) {break;}

            totalCost += minCost;
            path.pushBack(nextCity);
            visited[nextCity] = true;
            currentCity = nextCity;
        }

        int64_t saveCost = totalCost;
        Node<Pair> *moveback = costs_[currentCity].getHead();
        while (moveback) {
            if (moveback->value_.index_ == value) {
                totalCost += moveback->value_.cost_;
            }
            moveback = moveback->next_;
        }
        if (saveCost == totalCost) {
            return;
        }
        path.pushBack(path.getValue());
        std::cout << "PATH ";
        path.printList();
        if (totalCost < finalCost && path.size() - 1 == size_) {
            finalCost = totalCost;
            pathAnswer = path;
        }
    }
};

int main() {
    int64_t n;
    std::cin >> n;

    Salesman salesman(n);

    salesman.create();

    // salesman.print();
    
    salesman.traversal();

    return EXIT_SUCCESS;
}
