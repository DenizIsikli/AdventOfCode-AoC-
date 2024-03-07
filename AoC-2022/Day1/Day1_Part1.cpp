#include <iostream>
#include <fstream>
#include <string>

int main() {
	std::ifstream file("Input.txt");
	std::string line;
	int sum = 0;

	while(getline(file, line)) {
		int temp;

		if(line != "") {
			temp += std::stoi(line);
		} else if (line == "" and temp > sum) {
			sum = temp;
			temp = 0;
		} else {
			temp = 0;
		}
	}

	std::cout << sum << std::endl;
	return 0;
}

