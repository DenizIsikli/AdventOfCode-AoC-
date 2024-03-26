#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <array>

int main() {
    std::ifstream file("Input10.txt");
    std::string line;

    std::vector<std::string> input;
    std::vector<int> cycles;
    int X = 1;
    int pos = 0;

    const int crtWidth = 40;
    const int crtHeight = 6;
    std::array<char, crtWidth * crtHeight> crtScreen;
    std::fill_n(crtScreen.begin(), crtWidth * crtHeight, '.');

    while (std::getline(file, line)) {
        input.push_back(line);
    }

    auto tick = [&crtScreen, &pos, &X, crtWidth] {
        if (X - 1 <= (pos % crtWidth) && (pos % crtWidth) <= X + 1) {
            crtScreen[pos] = '#';
        }
        pos++;
    };

    for (const auto &line : input) {
        std::istringstream iss(line);
        std::string command;
        int value;

        if (line == "noop") {
            tick();
            continue;
        }
        iss >> command >> value;
        if (command == "addx") {
            tick();
            tick();
            X += value;
        }
    }

    for (size_t i = 0; i < crtHeight; ++i) {
        for (size_t j = 0; j < crtWidth; ++j) {
            std::cout << crtScreen[i * crtWidth + j];
        }
        std::cout << std::endl;
    }
}

