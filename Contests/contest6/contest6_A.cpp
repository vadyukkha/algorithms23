#include <iostream>
#include <vector>

class Pair {
public:
    size_t posX_, posY_;

    Pair(const size_t &X, const size_t &Y) : posX_(X), posY_(Y) {}
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

class Chessboard {
public:
    Chessboard(const size_t &size_, const size_t &x, const size_t &y) :
            size_(size_), start(x, y), graph_(size_ * size_, LinkedList<size_t>()) {}

    void createGraph() {
        std::vector<int16_t> moveX = {-1, 1, -2, 2, -2, 2, -1, 1};
        std::vector<int16_t> moveY = {-2, -2, -1, -1, 1, 1, 2, 2};

        for (size_t row = 0; row < size_; row++) {
            for (size_t col = 0; col < size_; col++) {

                size_t from = row * size_ + col;
                for (size_t i = 0; i < 8; i++) {
                    int32_t newX = col + moveX[i];
                    int32_t newY = row + moveY[i];
                    if (isValidMove(newX, newY)) {
                        size_t to = newY * size_ + newX;
                        graph_[from].pushBack(to);
                    }
                }
            }
        }
    }

    void printGraph() {
        std::cout << "Graph: " << std::endl;
        for (size_t i = 0; i < size_ * size_; i++) {
            std::cout << i << " - ";
            Node<size_t> *curr = graph_[i].getHead();
            std::cout << curr << std::endl;
        }
    }

    void isHamiltonianPath() {
        std::vector<bool> visited(size_ * size_, false);
        std::vector<std::vector<size_t>> path(size_, std::vector<size_t>(size_, -1));
        size_t path_value = 0;
            
        std::cout << "Hamiltonian path:" << std::endl;
        if(DFS(start.posX_, start.posY_, visited, path, path_value)) {
            for (size_t i = 0; i < size_; i++) {
                for (size_t j = 0; j < size_; j++) {
                    std::cout << path[i][j] << " ";
                }
                std::cout << std::endl;
            }
        } else {
            std::cout << "No way" << std::endl;
        }
    }

private:
    size_t size_;
    Pair start;
    std::vector<LinkedList<size_t> > graph_;

    bool isValidMove(const size_t &x, const size_t &y) const {
        return (x >= 0 && x < size_ && y >= 0 && y < size_);
    }

    bool DFS(const size_t &row, const size_t &col, std::vector<bool> &visited, std::vector<std::vector<size_t>>&path, size_t &path_value) {
        size_t vertex = row * size_ + col;
        visited[vertex] = true;
        path[row][col] = path_value++;

        if (path_value == size_*size_) return true;

        // search
        Node<size_t> *currentNode = graph_[vertex].getHead();
        while (currentNode) {
            size_t nextNode = currentNode->value_;

            if (!visited[nextNode]) {
                size_t newX = nextNode / size_;
                size_t newY = nextNode % size_;
                if (DFS(newX, newY, visited, path, path_value)) {
                    return true;
                }
            }
            currentNode = currentNode->next_;
        }

        // back from recursion
        visited[vertex] = false;
        path[row][col] = -1;
        path_value--;
        return false;
    }
};

int main() {
    size_t table_size, x_start, y_start;
    std::cin >> table_size >> x_start >> y_start;

    Chessboard board(table_size, x_start, y_start);

    board.createGraph();
    
    board.printGraph();
    
    board.isHamiltonianPath();

    return EXIT_SUCCESS;
}
