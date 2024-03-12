#include <iostream>
#include <string>
#include <set>

int findFirstMarker(const std::string &input) {
    for (int i = 0; i <= input.length() - 4; ++i) {
        std::set<char> uniqueChars(input.begin() + i, input.begin() + i + 4);
        if (uniqueChars.size() == 4) {
            return i + 4;
        }
    }
    return -1;
}

int main() {
    std::string line;
    
    while (getline(std::cin, line)) {
        int result = findFirstMarker(line);

        if (result != -1) {
            std::cout << result << std::endl;
        } else {
            std::cout << "No marker found" << std::endl;
        }
    }
}

