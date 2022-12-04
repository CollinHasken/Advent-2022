#include "day_4.h"

#include "../common_includes.h"

PROBLEM_CLASS_CPP(4);

struct elf_cleaning_info
{
	unsigned int min_cleaning_uid;
	unsigned int max_cleaning_uid;
};

void problem_1::solve(const std::string& file_name)
{
	std::ifstream input(file_name);

	if (!input.is_open()) {
		return;
	}

	unsigned int overlap_pairs = 0;
	while (!input.eof()) {
		std::string input_line;
		std::getline(input, input_line);

		std::istringstream input_ss(input_line);

		elf_cleaning_info elf1, elf2;
		char temp;
		input_ss >> elf1.min_cleaning_uid >> temp >> elf1.max_cleaning_uid >> temp
			>> elf2.min_cleaning_uid >> temp >> elf2.max_cleaning_uid;

		if (((elf1.min_cleaning_uid > elf2.min_cleaning_uid) == (elf1.max_cleaning_uid < elf2.max_cleaning_uid))
			|| elf1.min_cleaning_uid == elf2.min_cleaning_uid || elf1.max_cleaning_uid == elf2.max_cleaning_uid) {
			++overlap_pairs;
		}
	}

	input.close();

	std::string answer;
	answer = std::to_string(overlap_pairs);
	output_answer(answer);
}

void problem_2::solve(const std::string& file_name)
{
	std::ifstream input(file_name);

	if (!input.is_open()) {
		return;
	}

	unsigned int overlap_pairs = 0;
	while (!input.eof()) {
		std::string input_line;
		std::getline(input, input_line);

		std::istringstream input_ss(input_line);

		elf_cleaning_info elf1, elf2;
		char temp;
		input_ss >> elf1.min_cleaning_uid >> temp >> elf1.max_cleaning_uid >> temp
			>> elf2.min_cleaning_uid >> temp >> elf2.max_cleaning_uid;

		if (((elf1.min_cleaning_uid >= elf2.min_cleaning_uid) && (elf1.min_cleaning_uid <= elf2.max_cleaning_uid))
			|| ((elf2.min_cleaning_uid >= elf1.min_cleaning_uid) && (elf2.min_cleaning_uid <= elf1.max_cleaning_uid))
			|| ((elf1.max_cleaning_uid >= elf2.min_cleaning_uid) && (elf1.max_cleaning_uid <= elf2.max_cleaning_uid))
			|| ((elf2.max_cleaning_uid >= elf1.min_cleaning_uid) && (elf2.max_cleaning_uid <= elf1.max_cleaning_uid))) {
			++overlap_pairs;
		}
	}

	input.close();

	std::string answer;
	answer = std::to_string(overlap_pairs);
	output_answer(answer);
}