#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <numeric>
#include <array>

int main() {
    std::ifstream file("Input10.txt");
    std::string line;

    std::vector<std::string> input;
    std::vector<int> cycles;
    int X = 1;

    while (std::getline(file, line)) {
        input.push_back(line);
    }

    const std::array<int, 6> poss{20, 60, 100, 140, 180, 220};

    for (const auto &line : input) {
        std::istringstream iss(line);
        std::string command;
        int value;

        if (line == "noop") {
            cycles.push_back(X);
            continue;
        }
        iss >> command >> value;
        if (command == "addx") {
            cycles.push_back(X);
            cycles.push_back(X);
            X += value;
        }
    }

    auto sum = std::accumulate(poss.cbegin(), poss.cend(), 0, [&cycles](auto &s, const auto &pos) { 
        return s + cycles[pos - 1] * pos; 
    });

    std::cout << "Signal Strength: " << sum << std::endl;
}

