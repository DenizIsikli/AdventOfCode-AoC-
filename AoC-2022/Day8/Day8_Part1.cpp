#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
    std::ifstream file("Input8.txt");
    std::string line;

    std::vector<std::vector<int>> grid;

    while (std::getline(file, line)) {
        std::vector<int> row;
        for (char ch : line) {
            if (std::isdigit(ch)) {
                row.push_back(ch - '0');
            }
        }
        grid.push_back(row);
    }

    int n = grid.size();
    int visible = 0;

    auto isVisibleInDirection = [&](int row, int col, int dRow, int dCol) {
        int height = grid[row][col];
        row += dRow;
        col += dCol;
        while (row >= 0 && row < n && col >= 0 && col < n) {
            if (grid[row][col] >= height) return false;
            row += dRow;
            col += dCol;
        }
        return true;
    };

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == 0 || i == n - 1 || j == 0 || j == n - 1) {
                visible++;
            } else {
                if (isVisibleInDirection(i, j, 0, -1) ||
                    isVisibleInDirection(i, j, 0, 1) ||
                    isVisibleInDirection(i, j, -1, 0) ||
                    isVisibleInDirection(i, j, 1, 0)) {
                    visible++;
                }
            }
        }
    }

    std::cout << visible << std::endl;
}

