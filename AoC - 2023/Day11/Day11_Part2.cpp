#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>
#include <thread>
#include <mutex>

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
    
    std::vector<std::string> expanded;
    for (int i = 0; i < rows; ++i) {
        for (int k = 0; k < 1000000; ++k) {
            std::string expandedRow;
            for (int j = 0; j < cols; ++j) {
                expandedRow += lines[i][j];
                if (emptyCol[j]) expandedRow += '.';
            }
            expanded.push_back(expandedRow);
        }
        
    }

    for (int k = 0; k < 1000000; ++k) { // Expand columns
        std::string emptyColString(cols, '.');
        for (int i = 0; i < rows; ++i) {
            expanded.push_back(emptyColString);
        }
    }

    return expanded;
}

int manhattanDistance(const std::pair<int, int> &a, const std::pair<int, int> &b) {
    return std::abs(a.first - b.first) + std::abs(a.second - b.second);
}

void computeDistances(const std::unordered_map<int, std::pair<int, int>>& galaxyCoords, int start, int end, int &partialTotal) {
    int partialSum = 0;
    auto it = galaxyCoords.begin();
    std::advance(it, start);

    for (int i = start; i < end; ++i) {
        auto it2 = it;
        for (int j = i + 1; j < galaxyCoords.size(); ++j) {
            ++it2;
            partialSum += manhattanDistance(it->second, it2->second);
        }
        ++it;
    }
    partialTotal = partialSum;
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

    int numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    std::vector<int> partialSums(numThreads);
    int totalPathLength = 0;

    for (int i = 0; i < numThreads; ++i) {
        int start = (i * galaxyCoords.size()) / numThreads;
        int end = ((i + 1) * galaxyCoords.size()) / numThreads;
        threads.emplace_back([&, start, end, i]() {
            computeDistances(galaxyCoords, start, end, std::ref(partialSums[i]));
        });
    }

    for (int i = 0; i < numThreads; ++i) {
        threads[i].join();
        totalPathLength += partialSums[i];
    }

    std::cout << totalPathLength << std::endl;
}
