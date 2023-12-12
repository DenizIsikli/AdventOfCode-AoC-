#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <vector>

int navigateNetwork(std::unordered_map<std::string, std::string> nodes) {
    const std::string startNode = "AAA";
    const std::string endNode = "ZZZ";
    
    std::string currentNode = startNode;
    int steps = 0;

    

    return steps;
}

int main() {
    std::ifstream file("Input.txt");

    if (!file.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    std::string line;
    std::unordered_map<std::string, std::string> nodes;

    while (std::getline(file, line) && !line.empty()) {}

    while (std::getline(file, line)) {
        std::string nodeLabel = line.substr(0, line.find(' '));
        std::string connections = line.substr(line.find(' ') + 4);
        connections = connections.replace(connections.find(','), 1, " ").replace(connections.find(')'), 1, " ");
        std::string leftNode, rightNode;
        std::stringstream ss(connections);
        ss >> leftNode >> rightNode;
        

        std::cout << nodeLabel << std::endl;
        std::cout << leftNode << " " << rightNode << std::endl;
        nodes[nodeLabel] = connections;
    }

    file.close();

    int step = navigateNetwork(nodes);

    std::cout << "Steps: " << step << std::endl;

    return 0;
}
