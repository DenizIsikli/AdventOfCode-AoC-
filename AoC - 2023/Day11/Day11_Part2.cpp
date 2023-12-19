#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>

std::vector<std::string> expandUniverse(const std::vector<std::string> &lines) {
    int rows = lines.size();
    int cols = lines[0].size();

    std::vector<bool> emptyRow(rows, true), emptyCol(cols, true);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (lines[i][j] == '#') {
                emptyRow[i] = false;
                emptyCol[j] = false;
            }
        }
    }
    
    std::vector<std::string> expandedCols;
    for (const auto &line : lines) {
        std::string expandedLine;
        for (int j = 0; j < cols; ++j) {
            expandedLine += line[j];
            if (emptyCol[j]) {
                expandedLine += std::string(1000000, '.');
            }
        }
        expandedCols.push_back(expandedLine);
    }

    std::vector<std::string> expanded;
    for (int i = 0; i < rows; ++i) {
        expanded.push_back(expandedCols[i]);
        if (emptyRow[i]) {
            for (int k = 0; k < 1000000; ++k) {
                expanded.push_back(std::string(expandedCols[i].size(), '.'));
            }
        }
    }

    return expanded;
}

int manhattanDistance(const std::pair<int, int> &a, const std::pair<int, int> &b) {
    return std::abs(a.first - b.first) + std::abs(a.second - b.second);
}

int main() {
    std::ifstream file("Input.txt");
    std::string line;
    
    std::vector<std::string> lines;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    std::vector<std::string> newLines = expandUniverse(lines);

    std::unordered_map<int, std::pair<int, int>> galaxyCoords;
    int galaxyNumber = 1;
    for (int i = 0; i < newLines.size(); ++i) {
        for (int j = 0; j < newLines[i].size(); ++j) {
            if (newLines[i][j] == '#') {
                galaxyCoords[galaxyNumber++] = std::make_pair(i, j);
            }
        }
    }

    int totalPathLength = 0;
    for (int i = 1; i < galaxyNumber; ++i) {
        for (int j = i + 1; j < galaxyNumber; ++j) {
            totalPathLength += manhattanDistance(galaxyCoords[i], galaxyCoords[j]);
        }
    }

    std::cout << totalPathLength << std::endl;
}
    