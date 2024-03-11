#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <tuple>
#include <algorithm>
#include <deque>

void get_cargo(std::map<int, std::deque<char>> &cargo, int num, int from, int to) {
    std::deque<char> temp;

    for (int i = 0; i < num; i++) {
        temp.push_back(cargo[from].front());
        cargo[from].pop_front();
    }
    
    std::deque<char> temp2;
    while (!temp.empty()) {
        temp2.push_front(temp.front());
        temp.pop_front();
    }
    temp = temp2;

    while (!temp.empty()) {
        cargo[to].push_front(temp.front());
        temp.pop_front();
    }
}

std::string top_cargo(std::map<int, std::deque<char>> &cargo) {
    std::string top_crate;

    for (int i = 1; i <= cargo.size(); i++) {
        if (!cargo.at(i).empty()) {
           top_crate.push_back(cargo.at(i).front());
        }
    }

    return top_crate;
}

int main() {
    std::string line;
    std::vector<std::string> docker;
    std::map<int, std::deque<char>> cargo;
    std::map<int, std::deque<char>> temp;
    std::vector<std::tuple<int, int, int>> instructions;

    while (getline(std::cin, line)) {
        docker.push_back(line);
    }
    
    for (auto &line : docker) {
        if (line.empty()) {
            break;
        }

        for (int i = 0; i < line.size(); i++) {
            if (line[i] != ' ' && line[i] != '[' && line[i] != ']' && !isdigit(line[i])) {
                temp[i].push_back(line[i]);
            }
        }

        int count = 1;
        for (auto line : temp) {
            cargo[count] = line.second;
            count++;
        }
    }

    for (auto it = docker.rbegin(); it != docker.rend(); ++it) {
        if (it->find("move") == 0) {
            int num, from, to;
            std::istringstream iss(*it);
            std::string temp;
            iss >> temp >> num >> temp >> from >> temp >> to;
            instructions.emplace_back(num, from, to);
        } else if (it->empty()) {
            break;
        }
    }

    std::reverse(instructions.begin(), instructions.end());
 
    for (auto &instruction : instructions) {
        get_cargo(cargo, std::get<0>(instruction), std::get<1>(instruction), std::get<2>(instruction));
    }
    
    std::string top_crate = top_cargo(cargo);
    std::cout << top_crate << std::endl;
}

