#include "day_7.h"

#include "../common_includes.h"

#include "stack"

PROBLEM_CLASS_CPP(7);

static constexpr char COMMAND_CHAR = '$';
static constexpr char CD_FIRST_CHAR = 'c';
static constexpr char LS_FIRST_CHAR = 'l';
static constexpr char DIR_FIRST_CHAR = 'd';
static constexpr char ROOT_CHAR = '/';
static constexpr char BACK_FIRST_CHAR = '.';

static constexpr size_t COMMAND_INDEX = 2;
static constexpr size_t CD_NAME_INDEX = 5;

static constexpr unsigned long long DIR_MAX = 100000;

void problem_1::solve(const std::string& file_name)
{
	std::ifstream input(file_name);

	if (!input.is_open()) {
		return;
	}

	unsigned long long total_size = 0;
	unsigned long long cur_size = 0;
	std::stack<unsigned long long> cur_dir_sizes;
	while (!input.eof()) {
		std::string input_line;
		std::getline(input, input_line);
		if (input_line.empty()) {
			continue;
		}

		if (input_line[0] == COMMAND_CHAR) {
			if (input_line[COMMAND_INDEX] == CD_FIRST_CHAR) {
				if (input_line[CD_NAME_INDEX] == ROOT_CHAR) {
					continue;
				} else if (input_line[CD_NAME_INDEX] == BACK_FIRST_CHAR) {
					if (cur_size <= DIR_MAX) {
						total_size += cur_size;
					}
					cur_size += cur_dir_sizes.top();
					cur_dir_sizes.pop();
				} else {
					cur_dir_sizes.push(cur_size);
					cur_size = 0;
				}
			} else if (input_line[COMMAND_INDEX] == LS_FIRST_CHAR) {
				continue;
			}
		} else if (input_line[0] == DIR_FIRST_CHAR) {
			continue;
		} else {
			std::istringstream input_ss(input_line);
			unsigned long long size;
			input_ss >> size;
			cur_size += size;
		}
	}

	input.close();

	std::string answer;
	answer = std::to_string(total_size);
	output_answer(answer);
}


static constexpr unsigned long long FILESYSTEM_MAX = 70000000;
static constexpr unsigned long long NEEDED_SIZE = 30000000;

void problem_2::solve(const std::string& file_name)
{
	std::ifstream input(file_name);

	if (!input.is_open()) {
		return;
	}

	unsigned long long total_size = 0;
	unsigned long long cur_size = 0;
	std::stack<unsigned long long> cur_dir_sizes;
	std::stack<unsigned long long> all_dir_sizes;
	while (!input.eof()) {
		std::string input_line;
		std::getline(input, input_line);
		if (input_line.empty()) {
			continue;
		}

		if (input_line[0] == COMMAND_CHAR) {
			if (input_line[COMMAND_INDEX] == CD_FIRST_CHAR) {
				if (input_line[CD_NAME_INDEX] == ROOT_CHAR) {
					continue;
				} else if (input_line[CD_NAME_INDEX] == BACK_FIRST_CHAR) {
					if (cur_size <= DIR_MAX) {
						total_size += cur_size;
					}
					all_dir_sizes.push(cur_size);
					cur_size += cur_dir_sizes.top();
					cur_dir_sizes.pop();
				} else {
					cur_dir_sizes.push(cur_size);
					cur_size = 0;
				}
			} else if (input_line[COMMAND_INDEX] == LS_FIRST_CHAR) {
				continue;
			}
		} else if (input_line[0] == DIR_FIRST_CHAR) {
			continue;
		} else {
			std::istringstream input_ss(input_line);
			unsigned long long size;
			input_ss >> size;
			cur_size += size;
		}
	}

	unsigned long long free_space = FILESYSTEM_MAX - cur_size - cur_dir_sizes.top();
	unsigned long long delete_space = NEEDED_SIZE - free_space;

	unsigned long long best_space = FILESYSTEM_MAX;
	while (!all_dir_sizes.empty()) {
		cur_size = all_dir_sizes.top();
		all_dir_sizes.pop();
		if (cur_size <= best_space && cur_size >= delete_space) {
			best_space = cur_size;
		}
	}

	input.close();

	std::string answer;
	answer = std::to_string(best_space);
	output_answer(answer);
}