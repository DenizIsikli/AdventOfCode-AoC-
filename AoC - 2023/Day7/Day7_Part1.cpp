#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

int getCardStrength(const char card) {
    if (card == '2') return 2;
    else if (card == '3') return 3;
    else if (card == '4') return 4;
    else if (card == '5') return 5;
    else if (card == '6') return 6;
    else if (card == '7') return 7;
    else if (card == '8') return 8;
    else if (card == '9') return 9;
    else if (card == 'T') return 10;
    else if (card == 'J') return 11;
    else if (card == 'Q') return 12;
    else if (card == 'K') return 13;
    else if (card == 'A') return 14;
    return -1;
}

bool compareCards(const std::string card1, const std::string card2) {
    for (size_t i = 0; i < card1.size() && i < card2.size(); i++) {
        int strength1 = getCardStrength(card1[i]);
        int strength2 = getCardStrength(card2[i]);

        std::cout << card1[i] << " " << card2[i] << std::endl;
        std::cout << strength1 << " " << strength2 << std::endl;    

        
    }
    return card1.size() < card2.size();
}

size_t cardStrengthOrder(std::vector<std::string> &cards) {
    std::vector<std::string> strengthOrder;

    for (size_t i = 0; i < cards.size(); i++) {
        std::sort(cards[i].begin(), cards[i].end(), compareCards);
        
    }
}

int main() {
    std::ifstream file("Input.txt");

    if (!file.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    std::string line;
    int lineCount = 1;
    std::unordered_map<int, std::pair<std::string, int>> rankings;

    while(std::getline(file, line)) {
        std::istringstream iss(line);
        std::string cardValue, winnings;
        iss >> cardValue >> winnings;
        
        std::vector<std::string> cards;
        cards.push_back(cardValue);

        size_t cardStrength = cardStrengthOrder(cards);

        int winningsInt = std::stoi(winnings);

        rankings[lineCount++] = std::make_pair(cardStrength, winningsInt);
    }

    file.close();

    int total_winnings;
    for (const auto &pair : rankings) {
        total_winnings += pair.first * pair.second.second; 
        std::cout << pair.first << ": " << pair.second.first << " " << pair.second.second << std::endl;
    }

    std::cout << total_winnings << std::endl;

    return 0;
}