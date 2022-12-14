#include "day_10.h"

#include "../common_includes.h"

PROBLEM_CLASS_CPP(10);

static constexpr unsigned short CYCLE_START = 20;
static constexpr unsigned short CYCLE_INC = 40;

void problem_1::solve(const std::string& file_name)
{
	std::ifstream input(file_name);

	if (!input.is_open()) {
		return;
	}

	unsigned int signal_strength = 0;
	int reg_x = 1;
	unsigned short cycle = 0;
	unsigned short important_cycle = CYCLE_START;

	auto inc_cycle = [&cycle, &important_cycle, &reg_x, &signal_strength]() {
		++cycle;

		if (cycle == important_cycle) {
			important_cycle += CYCLE_INC;
			signal_strength += cycle * reg_x;
		}
	};

	while (!input.eof()) {
		std::string input_line;
		std::getline(input, input_line);

		if (input_line[0] == 'n') {
			inc_cycle();
			continue;
		}

		std::string temp;
		short inc;
		std::istringstream input_ss(input_line);
		input_ss >> temp >> inc;
		
		inc_cycle();
		inc_cycle();
		reg_x += inc;
	}

	input.close();

	std::string answer;
	answer = std::to_string(signal_strength);
	output_answer(answer);
}

static constexpr size_t CRT_WIDTH = 40;
static constexpr size_t CRT_HEIGHT = 6;

void problem_2::solve(const std::string& file_name)
{
	std::ifstream input(file_name);

	if (!input.is_open()) {
		return;
	}

	int reg_x = 1;
	unsigned short cycle = 0;

	size_t crt_x = 0, crt_y = 0;
	char crt[CRT_HEIGHT][CRT_WIDTH + 1];

	auto inc_cycle = [&cycle, &reg_x, &crt, &crt_x, &crt_y]() {
		if (static_cast<int>(crt_x) >= reg_x - 1 && static_cast<int>(crt_x) <= reg_x + 1) {
			crt[crt_y][crt_x] = '#';
		} else {
			crt[crt_y][crt_x] = '.';
		}

		++cycle;
		if (++crt_x == CRT_WIDTH) {
			crt[crt_y][crt_x] = crt_y == CRT_HEIGHT - 1 ? '\0' : '\n';
			crt_x = 0;
			++crt_y;
		}		
	};

	while (!input.eof()) {
		std::string input_line;
		std::getline(input, input_line);

		if (input_line[0] == 'n') {
			inc_cycle();
			continue;
		}

		std::string temp;
		short inc;
		std::istringstream input_ss(input_line);
		input_ss >> temp >> inc;

		inc_cycle();
		inc_cycle();
		reg_x += inc;
	}

	input.close();
	output_answer(crt[0]);
}