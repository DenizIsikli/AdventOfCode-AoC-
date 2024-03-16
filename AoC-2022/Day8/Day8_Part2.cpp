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

   std::vector<std::vector<int>> scores(grid.size(), std::vector<int>(grid[0].size(), 1));

   const std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

   auto inBounds = [&](int row, int col) -> bool {
       return row >= 0 && row < grid.size() && col >= 0 && col < grid[0].size();
   };

   for (int row = 0; row < grid.size(); row++) {
       for (int col = 0; col < grid[0].size(); col++) {
           for (const auto &[dRow, dCol] : directions) {
               int score = 0;
               int nextRow = row + dRow, nextCol = col + dCol;
               while(inBounds(nextRow, nextCol) && grid[row][col] > grid[nextRow][nextCol]) {
                   score++;
                   nextRow += dRow;
                   nextCol += dCol;
               }
               if (inBounds(nextRow, nextCol)) score++;
               scores[row][col] *= score;
           }
       }
   }

   int highestScore = 0;
   for (const auto &row : scores) {
       for (const auto ele : row) {
           highestScore = std::max(highestScore, ele);
       }
   }

   std::cout << highestScore << std::endl;
}

