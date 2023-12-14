#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

int main() {
    std::ifstream file("Input.txt");
    std::string line;

    std::vector<std::vector<int>> winningNumbersList;
    std::vector<std::vector<int>> scratchNumbersList;

    while (std::getline(file, line)) {
        std::istringstream iss(line.substr(line.find(':') + 2));
        std::string leftLine, rightLine;
        std::getline(iss, leftLine, '|');
        std::getline(iss, rightLine);

        std::vector<int> winningNumbers;
        std::vector<int> scratchNumbers;

        std::stringstream ss(leftLine), ss2(rightLine);
        int number;

        while (ss >> number) {
            winningNumbers.push_back(number);
        }

        while (ss2 >> number) {
            scratchNumbers.push_back(number);
        }

        winningNumbersList.push_back(winningNumbers);
        scratchNumbersList.push_back(scratchNumbers);
    }

    file.close();

    std::vector<int> cardCounts(winningNumbersList.size(), 1);

    for (size_t i = 0; i < winningNumbersList.size(); ++i) {
        const auto &winningNumbers = winningNumbersList[i];
        const auto &scratchNumbers = scratchNumbersList[i];
        std::vector<int> matches;

        for (const auto& num : scratchNumbers) {
            if (std::find(winningNumbers.begin(), winningNumbers.end(), num) != winningNumbers.end()) {
                matches.push_back(num);
            }
        }

        for (size_t j = i + 1; j <= i + matches.size(); ++j) {
            cardCounts[j] += cardCounts[i];
        }
    }

    int totalScratchCards = 0;
    for (const auto &count : cardCounts) {
        totalScratchCards += count;
    }

    std::cout << "Total Scratch Cards: " << totalScratchCards << std::endl; // "Total Scratch Cards: 0
    
    return 0;
}
