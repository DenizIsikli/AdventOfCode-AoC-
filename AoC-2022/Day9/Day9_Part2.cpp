#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <vector>

bool isOutOfProximity (const std::pair<int, int> &tail, const std::pair<int, int> &head) {
    return (std::abs(head.first - tail.first) > 1 || std::abs(head.second - tail.second) > 1);
}

void moveTail(std::pair<int, int> &tail, const std::pair<int, int> &head) {
    if (head.first != tail.first) {
        tail.first += (head.first > tail.first) ? 1 : -1;
    }
    if (head.second != tail.second) {
        tail.second += (head.second > tail.second) ? 1 : -1;
    }
}

int main() {
    std::ifstream file("Input9.txt");
    std::string line;

    std::map<char, std::pair<int, int>> directions = {
        {'R', {0, 1}},
        {'L', {0, -1}},
        {'U', {-1, 0}},
        {'D', {1, 0}}
    };

    std::vector<std::pair<int, int>> knots(10, std::make_pair(0, 0));

    std::set<std::pair<int, int>> visited;
    for (const auto &knot : knots) {
        visited.insert(knot);
    }

    while (std::getline(file, line)) {
        char direction;
        int steps;

        std::istringstream iss(line);
        iss >> direction >> steps;

        for (int step = 0; step < steps; step++) {
            knots[0].first += directions[direction].first;
            knots[0].second += directions[direction].second;

            for (int k = 1; k < knots.size(); ++k) {
                if (isOutOfProximity(knots[k], knots[k - 1])) {
                    moveTail(knots[k], knots[k - 1]);
                }
            }
            
            visited.insert(knots.back());
        }
    }

    std::cout << visited.size() << std::endl;
}

