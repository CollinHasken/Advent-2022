#include "day_5.h"

#include "../common_includes.h"
#include "vector"
#include "stack"

PROBLEM_CLASS_CPP(5);

void reverse(std::stack<char>& stack)
{
	std::stack<char> temp;
	while (!stack.empty()) {
		temp.push(stack.top());
		stack.pop();
	}
	temp.swap(stack);
}

void problem_1::solve(const std::string& file_name)
{
	std::ifstream input(file_name);

	if (!input.is_open()) {
		return;
	}

	std::vector<std::stack<char>> cargo_stacks;
	while (!input.eof()) {
		std::string input_line;
		std::getline(input, input_line);

		if (input_line.empty()) {
			break;
		}

		unsigned int space_count = 0;
		size_t current_stack = 0;
		for (char input_char : input_line) {
			if (input_char >= 'A' && input_char <= 'Z') {
				while (current_stack >= cargo_stacks.size()) {
					cargo_stacks.emplace_back();
				}
				cargo_stacks[current_stack++].push(input_char);
				space_count = 0;
			} else if (input_char == ' ') {
				++space_count;
				if (space_count == 4) {
					++current_stack;
					space_count = 0;
				}
			}
		}
	}

	for (auto& cargo_stack : cargo_stacks) {
		reverse(cargo_stack);
	}

	while (!input.eof()) {
		std::string input_line;
		std::getline(input, input_line);
		std::istringstream input_ss(input_line);
		char temp[5];
		size_t amount, source, dest;
		input_ss >> temp >> amount >> temp >> source >> temp >> dest;
		--source; --dest;
		for (size_t i = 0; i < amount; ++i) {
			cargo_stacks[dest].push(cargo_stacks[source].top());
			cargo_stacks[source].pop();
		}
	}

	input.close();

	std::string answer;
	for (const auto& cargo_stack : cargo_stacks) {
		answer += cargo_stack.top();
	}
	output_answer(answer);
}

void problem_2::solve(const std::string& file_name)
{
	std::ifstream input(file_name);

	if (!input.is_open()) {
		return;
	}

	std::vector<std::stack<char>> cargo_stacks;
	while (!input.eof()) {
		std::string input_line;
		std::getline(input, input_line);

		if (input_line.empty()) {
			break;
		}

		unsigned int space_count = 0;
		size_t current_stack = 0;
		for (char input_char : input_line) {
			if (input_char >= 'A' && input_char <= 'Z') {
				while (current_stack >= cargo_stacks.size()) {
					cargo_stacks.emplace_back();
				}
				cargo_stacks[current_stack++].push(input_char);
				space_count = 0;
			} else if (input_char == ' ') {
				++space_count;
				if (space_count == 4) {
					++current_stack;
					space_count = 0;
				}
			}
		}
	}

	for (auto& cargo_stack : cargo_stacks) {
		reverse(cargo_stack);
	}

	while (!input.eof()) {
		std::string input_line;
		std::getline(input, input_line);
		std::istringstream input_ss(input_line);
		char temp[5];
		size_t amount, source, dest;
		input_ss >> temp >> amount >> temp >> source >> temp >> dest;
		--source; --dest;
		std::stack<char> temp_stack;
		for (size_t i = 0; i < amount; ++i) {
			temp_stack.push(cargo_stacks[source].top());
			cargo_stacks[source].pop();
		}
		for (size_t i = 0; i < amount; ++i) {
			cargo_stacks[dest].push(temp_stack.top());
			temp_stack.pop();
		}
	}

	input.close();

	std::string answer;
	for (const auto& cargo_stack : cargo_stacks) {
		answer += cargo_stack.top();
	}
	output_answer(answer);
}