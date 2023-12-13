#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <vector>

int navigateNetwork(const std::unordered_map<std::string, std::pair<std::string, std::string>> &nodes, const std::string &startNode, const std::string &endNode, std::vector<std::string> &instructionsVector) {
    std::string currentNode = startNode;
    int steps = 0;
    size_t index = 0;

    while (currentNode != endNode) {
        for (const std::string& instruction : instructionsVector) {
            for (char c : instruction) {
                if (c == 'L') {
                    std::string temp = currentNode;
                    currentNode = nodes.at(temp).first;
                    if (currentNode == temp) {
                        currentNode = nodes.at(temp).second;
                    }
                } else if (c == 'R') {
                    currentNode = nodes.at(currentNode).second;
                }

                steps++;

                if (currentNode == endNode) {
                    break;
                }
            }

            if (currentNode == endNode) {
                break;
            }
        }

        if (currentNode != endNode) {
            index = (index + 1) % instructionsVector.size();
        }
    }

    return steps;
}


int main() {
    std::ifstream file("Input.txt");

    if (!file.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    std::string line;
    std::unordered_map<std::string, std::pair<std::string, std::string>> nodes;
    std::vector<std::string> instructionsVector;

    std::string instructions;
    std::getline(file, instructions);

    std::istringstream iss(instructions);
    std::string instruction;
    while (iss >> instruction) {
        instructionsVector.push_back(instruction);
    }

    std::string startNode;
    std::string endNode;

    while (std::getline(file, line)) {
        std::string leftNode = line.substr(0, line.find(" "));
        std::string rightNode = line.substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
        
        std::string rightNode_LeftNode = rightNode.substr(0, rightNode.find(","));
        std::string rightNode_RightNode = rightNode.substr(rightNode.find(" ") + 1);

        nodes[leftNode] = std::make_pair(rightNode_LeftNode, rightNode_RightNode);

        if (startNode.empty()) {
            startNode = leftNode;
        }
        endNode = leftNode;
    }

    file.close();

    int steps = navigateNetwork(nodes, startNode, endNode, instructionsVector);

    std::cout << "Steps: " << steps << std::endl;

    return 0;
}
