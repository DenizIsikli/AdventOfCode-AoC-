#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2>& pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

std::unordered_map<char, std::vector<std::pair<int, int>>> directions {
    {'|', {{-1, 0}, {1, 0}}},
    {'-', {{0, -1}, {0, 1}}},
    {'L', {{-1, 0}, {0, 1}}},
    {'J', {{-1, 0}, {0, -1}}},
    {'7', {{1, 0}, {0, -1}}},
    {'F', {{1, 0}, {0, 1}}},
    {'S', {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}}
};

int traverse(std::pair<int, int> current_pos, std::unordered_map<std::pair<int, int>, char, pair_hash> &nodePositions, 
             std::unordered_map<std::pair<int, int>, int, pair_hash> &distances, int current_distance = 0) {
    static std::unordered_set<std::pair<int, int>, pair_hash> visited;

    if (visited.find(current_pos) != visited.end()) {
        return 0;
    }
    visited.insert(current_pos);

    int max_distance = current_distance;
    distances[current_pos] = current_distance;

    for (auto direction : directions[nodePositions[current_pos]]) {
        std::pair<int, int> new_pos = { current_pos.first + direction.first, current_pos.second + direction.second };
        if (nodePositions.find(new_pos) != nodePositions.end()) {
            max_distance = std::max(max_distance, traverse(new_pos, nodePositions, distances, current_distance + 1));
        }
    }

    return max_distance;
}

int main() {
    std::ifstream file("input.txt");
    std::string line;
    std::vector<std::string> lines;

    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    std::unordered_map<std::pair<int, int>, char, pair_hash> nodePositions;
    std::pair<int, int> current_pos;

    for (int x = 0; x < lines.size(); ++x) {
        for (int y = 0; y < lines[x].size(); ++y) {
            char c = lines[x][y];
            if (c != '.') {
                nodePositions[{x, y}] = c;
                if (c == 'S') {
                    current_pos = {x, y};
                }
            }
        }
    }

    std::unordered_map<std::pair<int, int>, int, pair_hash> distances;
    int furthest_node = traverse(current_pos, nodePositions, distances);
    std::cout << "The furthest node is " << furthest_node << " nodes away." << std::endl;

    return 0;
}
