#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <unordered_map>
#include <limits>
#include <cstdint>
#include <queue>
#include <utility>
#include <sstream>

typedef std::pair<long double, std::string> ldsPair;

template <typename T>
class Node {
 public:
    T value_;
    Node* prev_;
    Node* next_;
    size_t size_;

    Node(const T& value) : value_(value), prev_(nullptr), next_(nullptr), size_(0) {}
};

template <typename T>
class LinkedList {
 public:
    LinkedList() : head_(nullptr), tail_(nullptr) {}

    void pushBack(const T& value) {
        Node<T>* newNode = new Node<T>(value);
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
            Node<T>* temp = head_;
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

    Node<T>* getHead() const {
        return head_;
    }

    void printList() const {
        Node<T>* current = head_;
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
        Node<T>* current = head_;
        Node<T>* nextNode = nullptr;

        while (current) {
            nextNode = current->next_;
            delete current;
            current = nextNode;
        }
    }

 private:
    Node<T>* head_;
    Node<T>* tail_;
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

class City {
 public:
    std::string city_;
    int64_t posX_, posY_;
    std::vector<std::string> neighbours_;

    // City() : city_(nullptr), posX_(-1), posY_(-1), neighbours_(1, nullptr) {}

    City(const std::string& city, const int64_t& X, const int64_t& Y) : 
        city_(city), posX_(X), posY_(Y) {}

    void addNeighbours(const std::string& neighbour) {
        neighbours_.push_back(neighbour);
    }

    friend std::ostream& operator<<(std::ostream& os, const City& city) {
        os << "City: " << city.city_ << "\n";
        os << "X: " << city.posX_ << "\n";
        os << "Y: " << city.posY_ << "\n";
        os << "Neighbours: ";
        for (size_t i = 0; i < city.neighbours_.size(); i++) {
            os << city.neighbours_[i] << " ";
        }
        os << "\n";
        return os;
    }
};

class Cities {
 public:
    Cities(const size_t& size) : num_cities_(size) {cities_.reserve(size);}

    void read() {
        std::string buff;
        for (size_t i = 0; i < num_cities_; i++) {
            std::string buff, city;
            int64_t X,Y;
            std::getline(std::cin >> std::ws, buff);
            std::istringstream iss(buff);

            iss >> city >> X >> Y;
            cities_.push_back(new City(city, X, Y));

            std::string neighbour;
            while (iss >> neighbour) {
                cities_.back()->addNeighbours(neighbour);
            }
        }
    }
    
    void printCity() {
        std::cout << "\nOUTPUT: " << std::endl;
        for (size_t i = 0; i < num_cities_; i++) {
            std::cout << *cities_[i] << std::endl;
        }
    }
   
    void findShortestPathDijkstra(const std::string& startCity, const std::string& endCity) const {
        std::priority_queue<ldsPair, std::vector<ldsPair>, std::greater<ldsPair>> pq;
        std::unordered_map<std::string, long double> distance;
        std::unordered_map<std::string, std::string> parent;

        if (findCity(startCity) == nullptr || findCity(endCity) == nullptr) {
            std::cout << "Path: \nNo way" << std::endl;
            return;
        }

        for (const City* city : cities_) {
            distance[city->city_] = std::numeric_limits<long double>::infinity();
            parent[city->city_] = "";
        }

        pq.push(std::make_pair(0.0, startCity));
        distance[startCity] = 0.0;

        while(!pq.empty()) {
            std::string current = pq.top().second;
            pq.pop();

            if (current == endCity) {
                break;
            }
            
            City* currentCity = findCity(current);
            for (const std::string& neighbour : currentCity->neighbours_) {
                long double dist = calculateDistance(current, neighbour);
                
                if (distance[neighbour] > distance[current] + dist) {
                    distance[neighbour] = distance[current] + dist;
                    pq.push(std::make_pair(distance[neighbour], neighbour));
                    parent[neighbour] = current;
                }
            }
        }

        if (distance[endCity] == std::numeric_limits<long double>::infinity()) {
            std::cout << "Path: \nNo way" << std::endl;
            return;
        }        

        Stack<std::string> path;
        uint64_t path_order = 1;
        std::string current = endCity;
        while (current != startCity) {
            path.push(current);
            path_order++;
            current = parent[current];
        }
        path.push(startCity);

        std::cout << "Path is not greater than " << static_cast<int64_t>(ceil(distance[endCity])) << std::endl;
        std::cout << "Path:" << std::endl;
        while (!path.isEmpty()) {
            std::cout << path.peek() << " ";
            path.pop();
        }
        std::cout << std::endl;
    } 

 private:
    size_t num_cities_;
    std::vector<City*> cities_;

    City* findCity(const std::string& cityName) const {
        for (const auto& city : cities_) {
            if (city->city_ == cityName) {
                return city;
            }
        }
        return nullptr;
    }

    long double calculateDistance(const std::string& city1, const std::string& city2) const {
        City* c1 = findCity(city1);
        City* c2 = findCity(city2);

        if (c1 == nullptr || c2 == nullptr) {
            return std::numeric_limits<long double>::infinity();
        }

        return std::sqrt((c2->posX_ - c1->posX_)*(c2->posX_ - c1->posX_) + (c2->posY_ - c1->posY_)*(c2->posY_ - c1->posY_));
    }
};

int main() {
    size_t numbers_cities;
    std::cin >> numbers_cities;
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (numbers_cities == 0) {
        std::cout << "Path: \nNo way" << std::endl;
        return EXIT_SUCCESS;
    }
    
    Cities cities(numbers_cities);
    cities.read();

    // cities.printCity();

    std::string startCity, endCity;
    std::cin >> startCity >> endCity;

    cities.findShortestPathDijkstra(startCity, endCity);

    return EXIT_SUCCESS;
}
