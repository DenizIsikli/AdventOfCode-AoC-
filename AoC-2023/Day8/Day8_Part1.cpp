#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>

int navigateNetwork(const std::unordered_map<std::string, std::pair<std::string, std::string>> &nodes,
                    const std::string &instructions, const std::string &startNode, const std::string &endNode) {
    std::string currentLeftNode = startNode;
    int steps = 0;

    while (currentLeftNode != endNode) {
        char c = instructions[steps % instructions.size()];
        currentLeftNode = c == 'L' ? nodes.at(currentLeftNode).first : nodes.at(currentLeftNode).second;
        steps++;
    }

    return steps;
}

int main() {
    std::ifstream file("Input.txt");
    std::string line;
    
    std::unordered_map<std::string, std::pair<std::string, std::string>> nodes;
    std::string emptyLine, instructions;
    std::getline(file, instructions);
    std::getline(file, emptyLine);

    while (std::getline(file, line)) {
        std::string leftNode = line.substr(0, line.find(" "));
        std::string rightNode = line.substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
        
        std::string rightNode_LeftNode = rightNode.substr(0, rightNode.find(","));
        std::string rightNode_RightNode = rightNode.substr(rightNode.find(" ") + 1);

        nodes[leftNode] = std::make_pair(rightNode_LeftNode, rightNode_RightNode);
    }

    file.close();

    std::string startNode = "AAA";
    std::string endNode = "ZZZ";

    int steps = navigateNetwork(nodes, instructions, startNode, endNode);

    std::cout << "Steps: " << steps << std::endl;

    return 0;
}
