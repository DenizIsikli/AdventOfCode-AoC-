#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
	std::ifstream file("Input.txt");
	std::string line;
	std::vector<int> numbers;
	int sum = 0;
	int temp = 0;

	while(getline(file, line)) {
		if(line != "") {
			temp += std::stoi(line);
		} else {
			numbers.push_back(temp);
			temp = 0;
		}
	}
	
	if (temp != 0) {
		numbers.push_back(temp);
	}

	sort(numbers.begin(), numbers.end(), std::greater<int>());

	for(int i = 0; i < 3; i++) {
		sum += numbers[i];
	}

	std::cout << sum << std::endl;
}

