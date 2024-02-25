#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <utility>

typedef std::pair<int64_t, size_t> iiPair; // Integer, Integer - pair
constexpr int64_t __INT64_T_MAX__ = std::numeric_limits<int64_t>::max();

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

template <typename Type>
class Stack {
 public:
    Stack() : top_(-1) {}

    void push(const Type& value) {
        items_.push_back(value);
        top_++;
    }

    Type pop() {
        Type poppedValue = items_[top_];
        items_.pop_back();
        top_--;
        return poppedValue;
    }

    Type peek() {
        return items_[top_];
    }

    bool isEmpty() {
        return (top_ == -1);
    }

 private:
    std::vector<Type> items_;
    int64_t top_;
};

class Graph {
public:
    Graph(const size_t& size) : size_(size) {adjacencyList_.reserve(size);}

    void addEdge(const size_t& vertex1, const size_t& vertex2) {
        adjacencyList_[vertex1].pushBack(vertex2);
    }

    void printGraph() {
        std::cout << "Graph: " << std::endl;
        for (size_t i = 0; i < size_; i++) {
            std::cout << i << " - ";
            Node<size_t>* curr = adjacencyList_[i].getHead();
            std::cout << curr << std::endl;            
        }
    }

    void BFS(const size_t& start) {
        std::vector<bool> visited(size_, false);
        std::vector<int64_t> path(size_, -1);
        size_t path_size = 0;

        LinkedList<size_t> queue;
    
        visited[start] = true;
        queue.pushBack(start);
    
        while (!queue.empty()) {
            size_t node = queue.getValue();
            queue.popFront();
            path[path_size++] = node;
    
            Node<size_t>* currentNode = adjacencyList_[node].getHead();
            while (currentNode) {
                size_t nextNode = currentNode->value_;
                if (!visited[nextNode]) {
                    visited[nextNode] = true;
                    queue.pushBack(nextNode);
                }
                currentNode = currentNode->next_;
            }
        }
        
        for (const auto& node : path) {
            std::cout << node << " ";
        }
        std::cout << std::endl;
    }

    void DFS(const size_t& start) {
        std::vector<bool> visited(size_, false);
        std::vector<size_t> path(size_, -1);
        size_t path_size = 0;
        DFSUtil(start, visited, path, path_size);
        bool all_visited = true; 
        for (const auto& item : visited) {
            if (item == false) {
                all_visited = false;
                break;
            }
        } 
        if (all_visited) {
            for (const auto& node : path) {
                std::cout << node << " ";
            }
            std::cout << std::endl;
        }
    }

    void Dijkstra(const size_t& start, const size_t& end) {
        std::vector<int64_t> distance(size_, __INT64_T_MAX__);
        std::vector<size_t> parent(size_, -1);
        std::priority_queue<iiPair, std::vector<iiPair>, std::greater<iiPair>> pq;
        pq.push(std::make_pair(0, start));
        distance[start] = 0;

        while (!pq.empty()) {
            size_t curr = pq.top().second;
            pq.pop();

            Node<size_t>* currentNode = adjacencyList_[curr].getHead();
            while (currentNode) {
                size_t neighbour = currentNode->value_;
                int64_t weight = 1;

                if (distance[neighbour] > distance[curr] + weight) {
                    distance[neighbour] = distance[curr] + weight;
                    parent[neighbour] = curr;
                    pq.push(std::make_pair(distance[neighbour], neighbour));
                }
                currentNode = currentNode->next_;
            }
        }

        Stack<size_t> path;
        uint64_t path_order = 1;
        size_t current = end;
        while (current != start) {
            path.push(current);
            path_order++;
            current = parent[current];
        }
        path.push(start);

        std::cout << "Distance: " << distance[end] << "\t";
        std::cout << "Path: ";
        while (!path.isEmpty()) {
            std::cout << path.peek() << " ";
            path.pop();
        }
        std::cout << std::endl;
    }

    void BellmanFord(const size_t& start) {
        std::vector<int64_t> distance(size_, __INT64_T_MAX__);
        distance[start] = 0;

        for (size_t i = 0; i < size_ - 1; ++i) {
            for (size_t j = 0; j < size_; ++j) {
                Node<size_t>* current = adjacencyList_[j].getHead();

                while (current) {
                    size_t neighbour = current->value_;
                    int64_t weight = 1;
                    if (distance[j] != __INT64_T_MAX__ && distance[j] + weight < distance[neighbour]) {
                        distance[neighbour] = distance[j] + weight;
                    }
                    current = current->next_;
                }
            }
        }

        // Check for negative cycles
        for (size_t i = 0; i < size_ - 1; ++i) {
            for (size_t j = 0; j < size_; ++j) {
                Node<size_t>* current = adjacencyList_[j].getHead();

                while (current) {
                    size_t neighbour = current->value_;
                    int64_t weight = 1;
                    if (distance[j] != __INT64_T_MAX__ && distance[j] + weight < distance[neighbour]) {
                        std::cout << "Graph contains negative cycle" << std::endl;
                        return;
                    }
                    current = current->next_;
                }
            }
        }

        for (size_t i = 0; i < size_; ++i) {
            std::cout << "Distance from vertex " << start << " to vertex " << i << " is " << distance[i] << std::endl;
        }
    }

    void FloydWarshall() {
        std::vector<std::vector<int64_t>> dist(size_, std::vector<int64_t>(size_, __INT64_T_MAX__));

        // Initialize
        for (size_t i = 0; i < size_; ++i) {
            dist[i][i] = 0;

            Node<size_t>* current = adjacencyList_[i].getHead();
            while (current) {
                size_t neighbour = current->value_;
                int64_t weight = 1;
                dist[i][neighbour] = weight;
                current = current->next_;
            }
        }

        // Update shortest distances using all vertices as intermediates
        for (size_t k = 0; k < size_; ++k) {
            for (size_t i = 0; i < size_; ++i) {
                for (size_t j = 0; j < size_; ++j) {
                    // If vertex k is on the shortest path from i to j, then update the value
                    if (dist[i][k] != __INT64_T_MAX__ && dist[k][j] != __INT64_T_MAX__ && dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        for (size_t i = 0; i < size_; ++i) {
            std::cout << i << " - ";
            for (size_t j = 0; j < size_; ++j) {
                if (dist[i][j] == __INT64_T_MAX__) {
                    std::cout << "INF ";
                } else {
                    std::cout << dist[i][j] << " ";
                }
            }
            std::cout << std::endl;
        }
    }

private:
    size_t size_;
    std::vector<LinkedList<size_t>> adjacencyList_;

    void DFSUtil(size_t start, std::vector<bool>& visited, std::vector<size_t>& path, size_t& path_size) {
        visited[start] = true;
        path[path_size++] = start;

        // search
        Node<size_t>* current = adjacencyList_[start].getHead();
        while (current) {
            if (!visited[current->value_]) {
                DFSUtil(current->value_, visited, path, path_size);
            }
            current = current->next_;
        }
    }
};

int main() {
    // Add edges in Graph
    Graph myGraph(4);
    myGraph.addEdge(0, 1);
    myGraph.addEdge(0, 2);
    myGraph.addEdge(1, 2);
    myGraph.addEdge(2, 0);
    myGraph.addEdge(2, 3);
    myGraph.addEdge(3, 3);

    // Display graph
    myGraph.printGraph();

    // BFS
    std::cout << "\nFollowing is Breadth First Traversal " << "(starting from vertex 2)" << std::endl;
    myGraph.BFS(2);

    // DFS
    std::cout << "\nFollowing is Depth First Traversal (starting from vertex 2)" << std::endl;
    myGraph.DFS(2);

    // Dijkstra's algorithm
    std::cout << "\nDijkstra's algorithm results:" << "\t";
    myGraph.Dijkstra(2, 1);

    // BellmanFord's algorithm
    std::cout << "\nBellmanFord's algorithm results:" << std::endl;
    myGraph.BellmanFord(2);

    // Floyd-Warshall algorithm
    std::cout << "\nFloyd-Warshall algorithm results:" << std::endl;
    myGraph.FloydWarshall();

    return EXIT_SUCCESS;
}
