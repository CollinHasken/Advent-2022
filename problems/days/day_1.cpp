#include "day_1.h"

#include "../common_includes.h"

PROBLEM_CLASS_CPP(1);

void problem_1::solve(const std::string& file_name)
{
	std::ifstream input(file_name);

	if (!input.is_open()) {
		return;
	}

	unsigned int largest_cal = 0;
	unsigned int current_cal = 0;

	while (!input.eof()) {
		std::string input_line;
		std::getline(input, input_line);
		if (input_line.empty()) {
			if (current_cal > largest_cal) {
				largest_cal = current_cal;
			}
			current_cal = 0;
		} else {
			current_cal += std::atoi(input_line.c_str());
		}
	}

	input.close();

	std::string answer;
	answer = std::to_string(largest_cal);
	output_answer(answer);
}

void InsertSort(unsigned int cals[3], unsigned int cal)
{
	for (size_t i = 0; i < 3; ++i) {
		if (cal > cals[i]) {
			unsigned int temp;
			unsigned int prev = cal;
			for (size_t j = i; j < 3; ++j) {
				temp = cals[j];
				cals[j] = prev;
				prev = temp;
			}
			break;
		}
	}
}

void problem_2::solve(const std::string& file_name)
{
	std::ifstream input(file_name);

	if (!input.is_open()) {
		return;
	}

	unsigned int largest_cals[3] = { 0, 0, 0 };
	unsigned int current_cal = 0;

	while (!input.eof()) {
		std::string input_line;
		std::getline(input, input_line);
		if (input_line.empty()) {
			InsertSort(largest_cals, current_cal);
			current_cal = 0;
		} else {
			current_cal += std::atoi(input_line.c_str());
		}
	}

	input.close();

	unsigned int cal_sum = 0;
	for (unsigned int cal : largest_cals) {
		cal_sum += cal;
	}

	std::string answer;
	answer = std::to_string(cal_sum);
	output_answer(answer);
}