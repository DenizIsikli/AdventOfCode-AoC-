#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

int main() {
	std::ifstream file("Input2.txt");
	std::string line;

	char opponent_play, my_play;

	std::map<char, int> play_scores = {{'X', 1}, {'Y', 2}, {'Z', 3}};
	std::map<char, char> win_map = {{'A', 'Y'}, {'B', 'Z'}, {'C', 'X'}};
	std::map<char, char> draw_map = {{'A', 'X'}, {'B', 'Y'}, {'C', 'Z'}};

	int win_score = 6;
	int draw_score = 3;
	int total_score = 0;

	while (std::getline(file, line)) {
		std::istringstream iss(line);
		iss >> opponent_play >> my_play;

		int play_score = play_scores[my_play];
		
		if (win_map[opponent_play] == my_play) {
			total_score += win_score + play_score;
		} else if (draw_map[opponent_play] == my_play) {
			total_score += draw_score + play_score;
		} else {
			total_score += play_score;
		}
	}

	std::cout << total_score << std::endl;
	return 0;
}

