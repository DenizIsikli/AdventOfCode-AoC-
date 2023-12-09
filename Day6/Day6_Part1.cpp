#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

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
            int value;
            while (iss >> value) {
                timeList.push_back(value);
            }
        } 
        else if (line.find("Distance") != std::string::npos) {
            int value;
            while (iss >> value) {
                distanceList.push_back(value);
            }
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
