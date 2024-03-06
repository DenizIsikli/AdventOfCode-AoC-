#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>

std::unordered_map<std::string, int> counts = { {"red", 12}, {"green", 13}, {"blue", 14} };

int main() {
    std::ifstream file("Input.txt");
    std::string line;
    int game_id = 1;
    int total = 0;

    while (std::getline(file, line)) {
        std::string _line = line.substr(line.find(':') + 2);
        std::replace(_line.begin(), _line.end(), ';', ',');
        
        std::istringstream ss(_line);
        std::string segment;
        bool valid_game = true;

        while (std::getline(ss, segment, ',')) {
            std::istringstream segmentStream(segment);
            std::string value, color;
            segmentStream >> value >> color;

            int parsedValue = stoi(value);

            if (parsedValue > counts[color]) {
                valid_game = false;
                break;
            }
        }

        if (valid_game) {
            total += game_id;
        }

        game_id++;
    }

    file.close();

    printf("Total: %d\n", total);

    return 0;
}
