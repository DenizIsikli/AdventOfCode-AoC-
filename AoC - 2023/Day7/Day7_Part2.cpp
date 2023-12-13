#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <unordered_map>
#include <algorithm>

int get_type(const std::string &hand) {
    int jokers = std::count(hand.begin(), hand.end(), 'J');
    std::unordered_map<char, int> counts;

    for (char c : hand) {
        if (c != 'J') {
            counts[c]++;
        }
    }

    std::vector<int> sorted_counts;
    for (const auto &pair : counts) {
        sorted_counts.push_back(pair.second);
    }
    std::sort(sorted_counts.rbegin(), sorted_counts.rend());

    if (sorted_counts.empty()) {
        sorted_counts.push_back(0);
    }

    if (sorted_counts[0] + jokers == 5) return 6;
    if (sorted_counts[0] + jokers == 4) return 5;
    if (sorted_counts[0] + jokers == 3 && sorted_counts.size() > 1 && sorted_counts[1] == 2) return 4;
    if (sorted_counts[0] + jokers == 3) return 3;
    if (sorted_counts[0] == 2 && (jokers || (sorted_counts.size() > 1 && sorted_counts[1] == 2))) return 2;
    if (sorted_counts[0] == 2 || jokers) return 1;
    
    return 0;
}

int compare(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {
    int type_a = get_type(a.first);
    int type_b = get_type(b.first);
    
    std::string cards = "J23456789TQKA";
    for (size_t i = 0; i < a.first.size(); ++i) {
        if (a.first[i] == b.first[i]) {
            continue;
        }
        if (type_a > type_b) {
            return 1;
        }
        if (type_a < type_b) {
            return -1;
        }
        
        bool a_wins = (cards.find(a.first[i]) > cards.find(b.first[i]));
        return (a_wins) ? 1 : -1;
    }
    return 0;
}

int main() {
    std::ifstream file("Input.txt");

    if (!file.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    std::vector<std::pair<std::string, int>> hands;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string cardValue, winnings;
        iss >> cardValue >> winnings;

        int winningsInt = std::stoi(winnings);

        hands.emplace_back(cardValue, winningsInt);
    }

    std::sort(hands.begin(), hands.end(), [](const auto &a, const auto &b) {
        return compare(a, b) < 0;
    });

    int totalWinnings = 0;
    for (size_t rank = 1; rank <= hands.size(); ++rank) {
        totalWinnings += rank * hands[rank - 1].second;
    }

    std::cout << "Result: " << totalWinnings << std::endl;

    file.close();

    return 0;
}
