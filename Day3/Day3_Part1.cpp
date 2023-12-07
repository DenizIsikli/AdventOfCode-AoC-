#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <regex>
#include <unordered_map>
#include <sstream>
#include <numeric>

struct PairHash {
    size_t operator()(const std::pair<int, int>& p) const {
        return static_cast<size_t>(p.first) ^ static_cast<size_t>(p.second);
    }
};

int main() {
    std::ifstream file("Input.txt");
    
    if (!file.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    std::map<std::pair<int, int>, char> symbols;
    for (int y = 0; y < lines.size(); ++y) {
        for (int x = 0; x < lines[y].size(); ++x) {
            char c = lines[y][x];
            if (c != '.' && !isdigit(c)) {
                symbols[{x, y}] = c;
            }
        }
    }

    std::unordered_map<std::pair<int, int>, std::vector<int>, PairHash> gears;
    int partNumbersSum = 0;

    for (int y = 0; y < lines.size(); ++y) {
        std::regex numberRegex("\\d+");
        std::sregex_iterator matchIterator(lines[y].begin(), lines[y].end(), numberRegex);
        std::sregex_iterator end;

        while (matchIterator != end) {
            int startX = matchIterator->position();
            int endX = startX + matchIterator->length();
            int num = std::stoi(matchIterator->str());

            for (const auto& symbol : symbols) {
                int sX = symbol.first.first;
                int sY = symbol.first.second;
                char c = symbol.second;
                if ((startX - 1 <= sX && sX <= endX) && (y - 1 <= sY && sY <= y + 1)) {
                    partNumbersSum += num;
                    if (c == '*') {
                        gears[{sX, sY}].push_back(num);
                    }
                    break;
                }
            }
            ++matchIterator;
        }
    }

    std::cout << "Sum: " << partNumbersSum << std::endl;

    return 0;
}
