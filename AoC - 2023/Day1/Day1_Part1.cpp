#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>

int main() {
    std::ifstream file("Input.txt");
    std::string line;
    uint32_t sum = 0;


    while(getline(file, line)) {
        uint32_t leftmost = -1;
        uint32_t rightmost = -1;

        for (int i = 0; i < line.length(); i++) {
            if (isdigit(line[i])) {
                if (leftmost == -1) {
                    // line[i] - '0' converts the char to an int
                    leftmost = line[i] - '0';
                    rightmost = line[i] - '0';
                } else {
                    rightmost = line[i] - '0';
                }
            }
        }

        sum += leftmost * 10 + rightmost;
    }

    file.close();

    printf("Sum: %d\n", sum);
}
