#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <numeric>
#include <algorithm>

int main() {
    std::ifstream file("Input.txt");
    std::string line;
    int totalSum = 0;

    while(std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<int> numbers;
        int number;

        while (iss >> number) {
            numbers.push_back(number);
        }

        std::reverse(numbers.begin(), numbers.end());
        
        std::vector<int> differences;

        while (!numbers.empty()) {
            differences.push_back(numbers.back());
            for (size_t i = 0; i < numbers.size(); ++i) {
                numbers[i] = numbers[i + 1] - numbers[i];
            }
            numbers.pop_back();

            if (std::all_of(numbers.begin(), numbers.end(), [](int n) { return n == 0; })) {
                break;
            }
        }
        
        totalSum += std::accumulate(differences.begin(), differences.end(), 0);              
    }  

    std::cout << totalSum << std::endl;

    return 0;
}
