#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>

int main() {
    uint32_t sum = 0;
    std::string line;

    std::ifstream inputFile("Input.txt");

    if (!inputFile.is_open()) {
        printf("Could not open file!");
        return 1;
    }

    while(getline(inputFile, line)) {
        uint32_t leftmost = -1;
        uint32_t rightmost = -1;

        for (int i = 0; i < line.length(); i++) {
            if (isdigit(line[i])) {
                if (leftmost == -1) {
                    leftmost = line[i] - '0';
                    rightmost = line[i] - '0';
                } else {
                    rightmost = line[i] - '0';
                }
            }
        }

        sum += leftmost * 10 + rightmost;
    }

    printf("Sum: %d\n", sum);
}
