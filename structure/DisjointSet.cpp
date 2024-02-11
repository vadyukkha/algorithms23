#include <iostream>
#include <vector>

class DisjointSet {
private:
	std::vector<int64_t> rank, parent; 
    int64_t n;
public:
	DisjointSet(int64_t n) {
		this->n = n;
		makeSet();
	}

	void makeSet() {
		for (int64_t i = 0; i < n; i++) {
            parent.push_back(i);
            rank.push_back(0);
		}
	}

	int64_t find(int64_t x) {
        if (x != parent[x]) {
			parent[x] = find(parent[x]);
		}
        return x;
	}

	void Union(int64_t x, int64_t y) {
		int64_t xRoot = find(x);
		int64_t yRoot = find(y);

		if (xRoot == yRoot) {
			return;
        }

		if (rank[xRoot] < rank[yRoot]) {
			parent[xRoot] = yRoot;
		}
		else if (rank[xRoot] > rank[yRoot]) {
			parent[yRoot] = xRoot;
		}
		else {
			parent[yRoot] = xRoot;
			rank[xRoot]++;
		}
	}
};

int main() {
    int64_t n = 5;

    DisjointSet disjointSet(n);
    disjointSet.makeSet();

    int64_t x = 3, y = 5;
    
    int64_t root = disjointSet.find(x);
    std::cout << "Root: "<< root << std::endl;

    disjointSet.Union(x, y);
    return 0;
}