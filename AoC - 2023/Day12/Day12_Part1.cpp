#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

int count(const std::string& cfg, std::vector<int>& nums, size_t pos = 0, size_t num_index = 0) {
    if (pos == cfg.size()) {
        return num_index == nums.size() ? 1 : 0;
    }

    if (num_index == nums.size()) {
        return cfg.find('#', pos) == std::string::npos ? 1 : 0;
    }

    int result = 0;

    if (cfg[pos] == '.' || cfg[pos] == '?') {
        result += count(cfg, nums, pos + 1, num_index);
    }

    if (cfg[pos] == '#' || cfg[pos] == '?') {
        if (nums[num_index] <= cfg.size() - pos) {
            std::string group = cfg.substr(pos, nums[num_index]);
            if (group.find('.') == std::string::npos) {
                if (pos + nums[num_index] < cfg.size() && cfg[pos + nums[num_index]] != '#') {
                    std::vector<int> next_nums(nums.begin() + 1, nums.end());
                    result += count(cfg, next_nums, pos + nums[num_index] + 1, 0);
                } else if (pos + nums[num_index] == cfg.size()) {
                    std::vector<int> next_nums(nums.begin() + 1, nums.end());
                    result += count(cfg, next_nums, pos + nums[num_index], 0);
                }
            }
        }
    }

    return result;
}

int main() {
    std::ifstream file("Input.txt");
    std::string line;
    int total = 0;

    while (std::getline(file, line)) {
        size_t spacePos = line.find(' ');
        std::string configuration = line.substr(0, spacePos);
        std::string springsString = line.substr(spacePos + 1);
    
        std::replace(springsString.begin(), springsString.end(), ',', ' ');

        std::vector<int> nums;
        std::istringstream iss(springsString);
        int spring;
        while (iss >> spring) {
            nums.push_back(spring);
        }
        
        int result = count(configuration, nums);
        total += result;
    }

    std::cout << "Total: " << total << std::endl;
    return 0;
}
