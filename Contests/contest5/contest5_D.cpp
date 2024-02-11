#include <iostream>
#include <vector>

class Table {
public:
    int64_t linkToRoot;
    int64_t rows;

    Table(int64_t linkToRoot, int64_t rows) : linkToRoot(linkToRoot), rows(rows) {}
};

class Solution {
private:
    std::vector<Table> tables;
    int64_t maxRow;
public:
    Solution(int64_t n) {
        maxRow = 0;
        for (size_t i = 0; i < n; i++) {
            int64_t request;
            std::cin >> request;
            maxRow = std::max(maxRow, request);
            Table buff(i, request);
            tables.push_back(buff);
        };
    }

    int64_t find(int64_t index) {
        if (index != tables[index].linkToRoot) {
            tables[index].linkToRoot = find(tables[index].linkToRoot);
        }
        return tables[index].linkToRoot;
    }

    void Union(int64_t xRoot, int64_t yRoot) {
        tables[xRoot].linkToRoot = yRoot;
        tables[yRoot].rows += tables[xRoot].rows;
        tables[xRoot].rows = 0;
        maxRow = std::max(maxRow, tables[yRoot].rows);
    }

    void dataProcessing(int64_t destination, int64_t source) {
        int64_t realDestination = find(destination);
        int64_t realSource = find(source);

        if (realDestination != realSource) {
            Union(realSource, realDestination);
        }

        std::cout << maxRow << std::endl;
    }
};

int main() {
    int64_t n, m;
    std::cin >> n >> m;
    Solution database(n);
    for (int64_t i = 0; i < m; ++i) {
        int64_t destination, source;
        std::cin >> destination >> source;
        database.dataProcessing(destination-1, source-1);
    }
	return 0;
}