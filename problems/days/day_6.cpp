#include "day_6.h"

#include "../common_includes.h"

PROBLEM_CLASS_CPP(6);

size_t charToIndex(char c) { return c - 'a'; }

size_t findUniqueMarker(std::ifstream& input, size_t window_size)
{
	std::unique_ptr<char[]> window(new char[window_size]);
	char seen[26] = { 0 };
	size_t window_i = 0;
	size_t copies = 0;
	unsigned int count = 0;
	while (!input.eof()) {
		std::string input_line;
		std::getline(input, input_line);

		for (char input_char : input_line) {
			++count;
			// If the character we're going to overwrite was a copy, remove it's count
			if (window[window_i] != '\0') {
				if (--(seen[charToIndex(window[window_i])]) > 0) {
					--copies;
				}
			}

			// If there was already a count for this char, mark the copy
			if ((seen[charToIndex(input_char)])++ > 0) {
				++copies;
			}

			window[window_i] = input_char;
			window_i = (++window_i) % window_size;
			if (copies == 0 && count >= window_size) {
				return count;
			}
		}
	}
	return 0;
}

void problem_1::solve(const std::string& file_name)
{
	std::ifstream input(file_name);

	if (!input.is_open()) {
		return;
	}

	size_t count = findUniqueMarker(input, 4);

	input.close();

	std::string answer;
	answer = std::to_string(count);
	output_answer(answer);
}

void problem_2::solve(const std::string& file_name)
{
	std::ifstream input(file_name);

	if (!input.is_open()) {
		return;
	}

	size_t count = findUniqueMarker(input, 14);

	input.close();

	std::string answer;
	answer = std::to_string(count);
	output_answer(answer);
}