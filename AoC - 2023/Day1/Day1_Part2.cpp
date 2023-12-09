#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>

typedef struct {
    std::string str;
    int i;
} lookup_t;

lookup_t lookup[] = {
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5}, 
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9}
};

uint32_t getNumber(std::string &slice) {
    for (int i = 0; i < 9; i++) {
        if (lookup[i].str == slice) {
            return lookup[i].i;
        }
    }

    if (std::isdigit(slice[0])) {
        return std::stoi(slice);
    }

    return -1;
}

int main() {
    uint32_t sum = 0;
    std::string line;

    std::ifstream inputFile("Input.txt");

    if (!inputFile.is_open()) {
        printf("Could not open file!");
        return 1;
    }

    while (getline(inputFile, line)) {
        uint32_t leftmost = -1;
        uint32_t rightmost = -1;

        for (int i = 0; i < line.length(); i++) {
            for (int j = 1; j <= 5; j++) {
                std::string slice = line.substr(i, j);
                uint32_t number = getNumber(slice);

                if (number != -1) {
                    if (leftmost == -1) {
                        leftmost = number;
                        rightmost = number;
                    } else {
                        rightmost = number;
                    }
                }
            }
        }
        sum += leftmost * 10 + rightmost;
    }
        
    printf("Sum: %d\n", sum);
}
