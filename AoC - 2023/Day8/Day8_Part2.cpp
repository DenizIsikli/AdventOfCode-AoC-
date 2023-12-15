#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <set>
#include <numeric>

bool endsWith(const std::string &str, char c) {
    return !str.empty() && str.back() == c;
}

long long navigateNetwork(const std::unordered_map<std::string, std::pair<std::string, std::string>> &nodes,
                          const std::string &instructions, const std::set<std::string> &startNodes) {
    std::vector<long long> cycles;

    for (std::string startNode : startNodes) {
        long long steps = 0;
        while (!endsWith(startNode, 'Z')) {
            char c = instructions[steps % instructions.size()];
            startNode = c == 'L' ? nodes.at(startNode).first : nodes.at(startNode).second;
            steps++;
        }
        cycles.push_back(steps);
    }

    long long lcm = cycles[0];
    for (size_t i = 1; i < cycles.size(); ++i) {
        lcm = std::lcm(lcm, static_cast<long long>(cycles[i]));
    }

    return lcm;
}

int main() {
    std::ifstream file("Input.txt");
    std::string line;
    
    std::unordered_map<std::string, std::pair<std::string, std::string>> nodes;
    std::set<std::string> startNodes;
    std::string emptyLine, instructions;
    std::getline(file, instructions);
    std::getline(file, emptyLine);

    while (std::getline(file, line)) {
        std::string leftNode = line.substr(0, line.find(" "));
        std::string rightNode = line.substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
    
        std::string rightNode_LeftNode = rightNode.substr(0, rightNode.find(","));
        std::string rightNode_RightNode = rightNode.substr(rightNode.find(" ") + 1);

        nodes[leftNode] = std::make_pair(rightNode_LeftNode, rightNode_RightNode);
        if (endsWith(leftNode, 'A')) {
            startNodes.insert(leftNode);
        }
    }

    file.close();

    long long totalSteps = navigateNetwork(nodes, instructions, startNodes);
    std::cout << "Steps: " << totalSteps << std::endl;

    return 0;
}
