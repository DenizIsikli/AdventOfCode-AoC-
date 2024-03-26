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
    int cycle = 0;

    const int crtWidth = 40;
    std::vector<std::string> crtScreen(6, std::string(crtWidth, '.'));

    while (std::getline(file, line)) {
        input.push_back(line);
    }

    for (const auto& commandLine : input) {
        std::istringstream iss(commandLine);
        std::string command;
        int value = 0;

        // Check if the line is a 'noop' or an 'addx' command
        if (commandLine == "noop") {
            // If 'noop', increase cycle by 1
            cycle++;
        } else {
            iss >> command >> value;
            if (command == "addx") {
                // Before changing X, check if the current cycle draws the sprite
                if (X >= 0 && X < crtWidth) {
                    crtScreen[cycle / crtWidth][X] = '#';
                }
                // Change X according to the value
                X += value;
                // Wrap X around if it goes beyond the screen width
                X = (X + crtWidth) % crtWidth;
                // After changing X, increase cycle by 1
                cycle++;
                // Check if the new value of X results in drawing the sprite
                if (X >= 0 && X < crtWidth) {
                    crtScreen[cycle / crtWidth][X] = '#';
                }
            }
        }

        // Wrap the cycle if it exceeds the screen height
        if (cycle / crtWidth >= crtScreen.size()) {
            std::cerr << "CRT screen overflow. Increase the number of rows in crtScreen." << std::endl;
            break;
        }
    }

    // Output the CRT screen
    for (const auto& row : crtScreen) {
        std::cout << row << std::endl;
    }
}

