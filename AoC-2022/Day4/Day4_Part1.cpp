#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream file("Input4.txt");

    std::string line;
    
    int total_pairs = 0;

    while (getline(std::cin, line)) {
        std::string left_side = line.substr(0, line.find(','));
        std::string right_side = line.substr(line.find(',') + 1);
        
        int left1 = std::stoi(left_side.substr(0, left_side.find('-')));
        int left2 = std::stoi(left_side.substr(left_side.find('-') + 1));

        int right1 = std::stoi(right_side.substr(0, right_side.find('-')));
        int right2 = std::stoi(right_side.substr(right_side.find('-') + 1));
        
        if ((left1 <= right1 && left2 >= right2) || (right1 <= left1 && right2 >= left2)) {
            total_pairs += 1;
        }
    }

    std::cout << total_pairs << std::endl;
}

