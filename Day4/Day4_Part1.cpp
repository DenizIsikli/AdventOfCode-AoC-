#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

int main () {
    std::ifstream file("Input.txt");
    int total_sum = 0;    

    if (!file.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line.substr(line.find(':') + 2));
        std::string leftLine, rightLine;
        std::getline(iss, leftLine, '|');
        std::getline(iss, rightLine);

        std::vector<std::string> winningNumbers;
        std::vector<std::string> scratchNumbers;

        std::stringstream ss(leftLine), ss2(rightLine);
        std::string number;

        while (ss >> number) {
            winningNumbers.push_back(number);
        }

        while (ss2 >> number) {
            scratchNumbers.push_back(number);
        }

        int card_score = 0;
        for (const std::string &winNum : winningNumbers) {
            if (std::find(scratchNumbers.begin(), scratchNumbers.end(), winNum) != scratchNumbers.end()) {
                card_score++;
            }
        }

        if (card_score > 0) {
            // << (card_score - 1) is a bitwise left shift operation: 2^(card_score - 1)
            total_sum += 1 << (card_score - 1);
        }
    }
    
    std::cout << "Total: " << total_sum << std::endl;
    return 0;
}
