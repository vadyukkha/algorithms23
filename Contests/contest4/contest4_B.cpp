#include <iostream>
#include <vector>
#include <climits>
#include <sstream>

template <typename T, typename T2>
class Node {
public:
    T key;
    T2 value;
    bool state;

    // Constructor
    Node(const T& key, T2 value) : key(key), value(value), state(true) {}
};

template <typename T, typename T2>
class HashMap {
private:
    std::vector<Node<T, T2>*> arr;

    // Hash function for contesst
    int64_t hashContest(const std::string& key, int64_t p, int64_t q) const {
        //read more https://www.geeksforgeeks.org/string-hashing-using-polynomial-rolling-hash-function/
        int64_t hashToReturn = 0;
        int64_t p_Exp = 1;
        for (size_t i = 0; i < key.length(); i++) {
            hashToReturn = (hashToReturn + p_Exp * (key[i] - 'a' + 1)) % q;
            p_Exp = (p_Exp * p) % q;
        }
        return hashToReturn % q;
    }

    // Find an empty index for the given key
    size_t findEmptyIndexContest(const T& key, int64_t p, int64_t q) const {
        size_t h1 = hashContest(key, p, q);
        size_t i = 0;

        while (arr[h1] != nullptr && i < q) {
            if (!arr[h1]->state) {
                return h1;
            }
            h1 = (h1 + 1) % q;
            ++i;
        }

        return h1;
    }

public:
    // Constructor, set defualt values
    HashMap() { arr.resize(1000, nullptr); }

    // Function for the contest
    void putContest(const T& key, T2 value, int64_t p, int64_t q) {
        size_t index = hashContest(key, p, q);

        if (arr[index] == nullptr) { // existence check
            arr[index] = new Node<T, T2>(key, value); // save the key and the value by creating the node
            std::cout << "key=" << key << " hash=" << hashContest(key, p, q) << " operation=PUT result=inserted value=" << value << std::endl;
        } else if (!arr[index]->state) { // check deleted node
            arr[index] = new Node<T, T2>(key, value); // save the key and the value by creating the node
            std::cout << "key=" << key << " hash=" << hashContest(key, p, q) << " operation=PUT result=inserted value=" << value << std::endl;
        } else {
            size_t collisionIndex = findEmptyIndexContest(key, p, q); //get first empty index
            if (collisionIndex == hashContest(key, p, q)) { //check collision
                std::cout << "key=" << key << " hash=" << hashContest(key, p, q) << " operation=PUT result=overflow" << std::endl;
            } else {
                arr[collisionIndex] = new Node<T, T2>(key, value);
                std::cout << "key=" << key << " hash=" << hashContest(key, p, q) << " operation=PUT result=collision linear_probing=" << collisionIndex << " value=" << value << std::endl;
            }
        }
    }

    // Function for the contest
    void delContest(const T& key, int64_t p, int64_t q) {
        size_t h1 = hashContest(key, p, q);
        size_t i = 0;

        while (arr[h1] != nullptr && i < q) {
            if (arr[h1]->key == key && arr[h1]->state && h1 == hashContest(key, p, q)) { //found the key in the node associated the hash
                delete arr[h1];
                arr[h1]->state = false;
                std::cout << "key=" << key << " hash=" << hashContest(key, p, q) << " operation=DEL result=removed" << std::endl;
                return;
            } else if (arr[h1]->key == key && arr[h1]->state) { //found the key in the another node
                delete arr[h1];
                arr[h1]->state = false;
                std::cout << "key=" << key << " hash=" << hashContest(key, p, q) << " operation=DEL result=collision linear_probing=" << h1 << " value=removed" << std::endl;
                return;
            }

            h1 = (h1 + 1) % q;
            ++i;
        }
        if(h1 == hashContest(key, p, q)) { //check collision
            std::cout << "key=" << key << " hash=" << hashContest(key, p, q) << " operation=DEL result=no_key" << std::endl;
        } else {
            std::cout << "key=" << key << " hash=" << hashContest(key, p, q) << " operation=DEL result=collision linear_probing=" << h1 << " value=no_key" << std::endl;
        }
    }

    // Function for the contest
    void getContest(const T& key, int64_t p, int64_t q) {
        size_t h1 = hashContest(key, p, q);
        size_t i = 0;

        while (arr[h1] != nullptr && i < q) {
            if (arr[h1]->key == key && arr[h1]->state && h1 == hashContest(key, p, q)) { //found the key in the node associated the hash
                std::cout << "key=" << key << " hash=" << hashContest(key, p, q) << " operation=GET result=found value=" << arr[h1]->value << std::endl;
                return;
            } else if (arr[h1]->key == key && arr[h1]->state) { //found the key in the another node
                std::cout << "key=" << key << " hash=" << hashContest(key, p, q) << " operation=GET result=collision linear_probing=" << h1 << " value=" << arr[h1]->value << std::endl;
                return;
            }
            h1 = (h1 + 1) % q;
            ++i;
        }
        if (h1 == hashContest(key, p, q)) { //cheeck collision
            std::cout << "key=" << key << " hash=" << hashContest(key, p, q) << " operation=GET result=no_key" << std::endl;
        } else {
            std::cout << "key=" << key << " hash=" << hashContest(key, p, q) << " operation=GET result=collision linear_probing=" << h1 << " value=no_key" << std::endl;
        }
    }


    // Destructor to free memory when the hash table is destroyed (unstable)
    ~HashMap() {
        for (Node<T, T2>* node : arr) {
            if (node != nullptr) {
                if (node->state) {
                    delete node;
                }
            }
        }
    }
};

// Class for some solution 
class Solution {
public:
    void AnswerForContest2() {
        HashMap<std::string, int64_t> myMap;
        std::string buff;
        std::getline(std::cin, buff);

        std::istringstream iss(buff);
        int64_t q, p, n;
        iss >> q >> p >> n;

        for (size_t i = 0; i < n; i++) {
            std::getline(std::cin, buff);
            std::istringstream iss_line(buff);
            std::string op, s;
            int64_t value;
            iss_line >> op >> s;

            if (op == "PUT") {
                iss_line >> value;
                myMap.putContest(s, value, p, q);
            } else if (op == "GET") {
                myMap.getContest(s, p, q);
            } else {
                myMap.delContest(s, p, q);
            }
        }
    }
};

int main() {
    Solution solve;
    solve.AnswerForContest2();
    return 0;
}