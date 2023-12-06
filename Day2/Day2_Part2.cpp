#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>

int main() {
    std::ifstream inputFile("Input.txt");
    std::string line;
    int total_sum = 0;

    while (std::getline(inputFile, line)) {
        std::string _line = line.substr(line.find(':') + 2);
        std::replace(_line.begin(), _line.end(), ';', ',');
        
        std::unordered_map<std::string, int> counts = { {"red", 0}, {"green", 0}, {"blue", 0} };

        std::istringstream ss(_line);
        std::string segment;

        while (std::getline(ss, segment, ',')) {
            std::istringstream segmentStream(segment);
            std::string value, color;
            segmentStream >> value >> color;

            int parsedValue = stoi(value);

            if (parsedValue > counts[color]) {
                counts[color] = parsedValue;
            }   
        }
        
        int max_red = counts["red"];
        int max_green = counts["green"];
        int max_blue = counts["blue"];

        total_sum += max_red * max_green * max_blue;   
    }

    std::cout << "Total: " << total_sum << std::endl;

    return 0;
}
