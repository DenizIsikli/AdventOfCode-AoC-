#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

std::unordered_map<char, std::vector<std::pair<int, int>>> directions = {
    {'|', {{-1, 0}, {1, 0}}},
    {'-', {{0, 1}, {0, -1}}},
    {'L', {{0, 1}, {-1, 0}}},
    {'J', {{0, -1}, {-1, 0}}},
    {'7', {{1, 0}, {0, -1}}},
    {'F', {{1, 0}, {0, 1}}},
    {'S', {{-1, 0}, {1, 0}, {0, 1}, {0, -1}}},
    {'.', {}}
};

int main() {
    std::ifstream file("Input.txt");
    std::string line;
    std::unordered_map<int, char> maze;
    int start = 0;
    int row = 0;
    int max_width = 0;
    int key;

    while (std::getline(file, line)) {
        max_width = line.length();

        for (int col = 0; col < line.length(); ++col) {
            key++;
            maze[key] = line[col];
            if (line[col] == 'S') {
                start = key;
            }
        }
        ++row;
    }

    std::unordered_map<int, std::unordered_set<int>> graph;
    for (const auto &m : maze) {
        int pos = m.first;
        char c = m.second;
        int row = pos / max_width;
        int col = pos % max_width;
        for (auto &dir: directions[c]) {
            int neighbor = (row + dir.first) * max_width + (col + dir.second);
            if (maze.find(neighbor) != maze.end()) {
                graph[pos].insert(neighbor);
            }
        }
    }

    std::unordered_set<int> seen = {start};
    std::unordered_set<int> todo = graph[start];

    while (!todo.empty()) {
        int node = *todo.begin();
        seen.insert(node);
        todo.erase(node);
        for (const auto &n : graph[node]) {
            if (seen.find(n) == seen.end()) {
                todo.insert(n);
            }
        }
    }

    std::cout << seen.size() / 2 << std::endl;
    return 0;
}
