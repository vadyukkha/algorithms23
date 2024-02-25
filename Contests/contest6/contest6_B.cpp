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

class Maze {
 private:
    Pair start_, finish_;
    size_t rowSize_, colmSize_;
    std::vector<std::vector<char>> maze_;
    std::vector<LinkedList<size_t>> graph_;

    bool isValid(const size_t& row, const size_t& colm) {
        return (row >= 0 && row < rowSize_ && colm >= 0 && colm < colmSize_ && maze_[row][colm] != '#');
    }

 public:
    Maze(const size_t& rowSize_, const size_t& colmSize_) : rowSize_(rowSize_), colmSize_(colmSize_), 
        start_(-1, -1), finish_(-1, -1), maze_(rowSize_, std::vector<char>(colmSize_, '\0')), graph_(rowSize_*colmSize_, LinkedList<size_t>()) {}

    void readMaze() {
        for (size_t i = 0; i < rowSize_; i++) {
            for (size_t j = 0; j < colmSize_; j++) {
                std::cin >> maze_[i][j];
                if (maze_[i][j] == 'S') {
                    start_ = Pair(j, i);
                } else if (maze_[i][j] == 'F') {
                    finish_ = Pair(j, i);
                }
            }
        }
    }

    void printMaze() {
        std::cout << "Initial labyrinth: " << std::endl;
        for (size_t i = 0; i < rowSize_; i++) {
            for (size_t j = 0; j < colmSize_; j++) {
                std::cout << maze_[i][j];
            }
            std::cout << std::endl;
        }
    }

    void createGraph() {
        std::vector<int32_t> moveX = {0, -1, 1, 0};
        std::vector<int32_t> moveY = {-1, 0, 0, 1};

        for (size_t row = 0; row < rowSize_; row++) {
            for (size_t col = 0; col < colmSize_; col++) {
                if (maze_[row][col] == '#') continue;

                size_t from = row * colmSize_ + col;
                for (size_t i = 0; i < 4; i++) {
                    int32_t newX = col + moveX[i];
                    int32_t newY = row + moveY[i];

                    if (isValid(newY, newX)) {
                        size_t to = newY * colmSize_ + newX;
                        graph_[from].pushBack(to);
                    }
                }
            }
        }
    }

    void printGraph() {
        std::cout << "Graph: " << std::endl;
        for (size_t i = 0; i < rowSize_ * colmSize_; i++) {
            std::cout << i << " - ";
            Node<size_t>* curr = graph_[i].getHead();
            std::cout << curr << std::endl;            
        }
    }

    void BFS() {
        std::cout << "BFS result is: " << std::endl;

        std::vector<int32_t> visited(rowSize_ * colmSize_, -1);

        size_t finish = finish_.posY_ * colmSize_ + finish_.posX_;
        size_t start = start_.posY_ * colmSize_ + start_.posX_;

        LinkedList<Pair> queue;
        queue.pushBack(start_);

        visited[start] = 0;

        while (!queue.empty()) {
            Pair current = queue.getHead()->value_;
            queue.popFront();

            size_t node = current.posY_ * colmSize_ + current.posX_;

            if (node == finish) break;

            Node<size_t>* currentNode = graph_[node].getHead();
            while (currentNode) {
                size_t nextNode = currentNode->value_;
                if (visited[nextNode] == -1) {
                    visited[nextNode] = visited[node] + 1;
                    size_t newY = nextNode % colmSize_;
                    size_t newX = nextNode / colmSize_;
                    Pair next(newY, newX);
                    queue.pushBack(next);
                }
                
                currentNode = currentNode->next_;
            }
        }

        for (size_t i = 0; i < rowSize_; i++) {
            for (size_t j = 0; j < colmSize_; j++) {
                std::cout << visited[i * colmSize_ + j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    size_t rowSize_, colmSize_;
    std::cin >> rowSize_ >> colmSize_;

    Maze maze_(rowSize_, colmSize_);

    maze_.readMaze();

    maze_.printMaze();

    maze_.createGraph();

    maze_.printGraph();

    maze_.BFS();
    return EXIT_SUCCESS;
}
