#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <set>

std::string cleanPath(const std::string &path) {
    if (path.empty() || path == "/") return "/";
    if (path.back() != '/') return path;
    return path;
}

void traverseDirectory(std::map<std::string, std::vector<std::string>> &directories, std::string &cwd, std::ifstream &file);

void processCommand(const std::string &line, std::map<std::string, std::vector<std::string>> &directories, std::string &cwd, std::ifstream &file) {
    std::istringstream iss(line.substr(2));
    std::string command;
    iss >> command;

    if (command == "cd") {
        std::string arg;
        iss >> arg;

        if (arg == "..") {
            if (cwd != "/") {
                int pos = cwd.find_last_of('/');
                cwd = cwd.substr(0, pos);
            }
        } else if (arg == "/") {
            cwd = arg;
        } else {
            cwd = cleanPath(cwd) + arg;
            directories[cwd] = {};
        }
        cwd = cleanPath(cwd);
    }

    traverseDirectory(directories, cwd, file);
}

void traverseDirectory(std::map<std::string, std::vector<std::string>> &directories, std::string &cwd, std::ifstream &file) {
    std::string line;
    while (getline(file, line) && line[0] != '$') {
        if (!line.empty()) {
            directories[cwd].push_back(line);
        }
    }
    
    if (line[0] == '$') {
        processCommand(line, directories, cwd, file);
    }
}

int extractSize(const std::string& entry) {
    std::istringstream iss(entry);
    int size;
    iss >> size;
    return size;
}

int calculateDirectorySize(const std::string& directory, std::map<std::string, std::vector<std::string>>& directories) {
    int totalSize = 0;
    for (const std::string& entry : directories[directory]) {
        if (entry.find("dir") != std::string::npos) {
            std::istringstream iss(entry);
            std::string subdir;
            iss >> subdir;
            iss >> subdir;
            std::string fullPath = cleanPath(directory) + subdir;
            totalSize += calculateDirectorySize(fullPath, directories);
        } else {
            totalSize += extractSize(entry);
        }
    }
    return totalSize;
}

int main() {
    std::ifstream file("Input7.txt");
    std::string line;

    std::map<std::string, std::vector<std::string>> directories;
    std::string cwd = "/";

    directories[cwd] = {};

    while (getline(file, line)) {
        if (line[0] == '$') {
            processCommand(line, directories, cwd, file);
        }
    }
    
    std::map<std::string, int> directorySizes;

    for (const auto& dir : directories) {
        directorySizes[dir.first] = calculateDirectorySize(dir.first, directories);
    }

    std::cout << "Directories with size less than 100000:" << std::endl;
    int sumOfSizes = 0;
    for (const auto& dirSize : directorySizes) {
        if (dirSize.second < 100000) {
            std::cout << "Directory: " << dirSize.first << ", Size: " << dirSize.second << std::endl;
            sumOfSizes += dirSize.second;
        }
    }

    std::cout << "Sum of the sizes of these directories: " << sumOfSizes << std::endl;
}

