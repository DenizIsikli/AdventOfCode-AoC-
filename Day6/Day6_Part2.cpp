#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>

int safeStringToInt(const std::string &str) {
    std::istringstream iss(str);
    int result;
    if (!(iss >> result)) {
        result = std::numeric_limits<int>::min(); // Or any other value you prefer as default
    }
    return result;
}

int main() {
    std::ifstream file("Input.txt");

    if (!file.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    std::vector<int> timeList;
    std::vector<int> distanceList;

    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line.substr(line.find(':') + 1));

        if (line.find("Time") != std::string::npos) {
            std::string concatenatedValue;
            std::string value;
            while (iss >> value) {
                concatenatedValue += value;
            }
            timeList.push_back(safeStringToInt(concatenatedValue));
        } 
        else if (line.find("Distance") != std::string::npos) {
            std::string concatenatedValue;
            std::string value;
            while (iss >> value) {
                concatenatedValue += value;
            }
            distanceList.push_back(safeStringToInt(concatenatedValue));
        }
    }

    int totalPossibilities = 1;
    
    for (size_t i = 0; i < timeList.size(); i++) {
        int raceTime = timeList[i];
        int recordDistance = distanceList[i];

        int possibilities = 0;

        for (int heldTime = 0; heldTime <= raceTime; heldTime++) {
            int remainingTime = raceTime - heldTime;
            if (heldTime * remainingTime > recordDistance) {
                possibilities++;
            }
        }

        totalPossibilities *= possibilities;
    }

    std::cout << "Total Possibilities: " << totalPossibilities << std::endl;

    return 0;
}
