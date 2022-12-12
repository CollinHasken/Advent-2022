#include "day_8.h"

#include "../common_includes.h"

#include "vector"

PROBLEM_CLASS_CPP(8);

typedef std::vector<char> row;
typedef std::vector<row> grid;
typedef std::vector<bool> found_row;
typedef std::vector<found_row> found_grid;

bool hasTreeBeenFound(const found_grid& cur_grid, size_t x, size_t y)
{
	if (y >= cur_grid.size()) {
		return false;
	}
	if (x >= cur_grid[y].size()) {
		return false;
	}
	return cur_grid[y][x];
}

void markTreeFound(found_grid& cur_grid, size_t x, size_t y)
{
	while (y >= cur_grid.size()) {
		cur_grid.emplace_back();
	}
	while (x >= cur_grid[y].size()) {
		cur_grid[y].emplace_back(false);
	}
	cur_grid[y][x] = true;
}

void problem_1::solve(const std::string& file_name)
{
	std::ifstream input(file_name);

	if (!input.is_open()) {
		return;
	}

	grid tree_grid;
	found_grid found_tree_grid;
	while (!input.eof()) {
		std::string input_line;
		std::getline(input, input_line);
		row input_row;
		for (char input_char : input_line) {
			input_row.push_back(input_char - '0');
		}
		tree_grid.emplace_back(input_row);
	}
	if (tree_grid.empty()) {
		return;
	}

	size_t row_length = tree_grid[0].size();
	unsigned long long visible_trees = 4; // For the 4 skipped corners
	for (size_t row_i = 1; row_i < tree_grid.size() - 1; ++row_i) {
		// Check left visibility
		const row& cur_row = tree_grid[row_i];
		int highest_tree = -1;
		for (size_t tree_l = 0; tree_l < row_length - 1; ++tree_l) {
			if (cur_row[tree_l] > highest_tree) {
				highest_tree = cur_row[tree_l];
				if (!hasTreeBeenFound(found_tree_grid, tree_l, row_i)) {
					++visible_trees;
					markTreeFound(found_tree_grid, tree_l, row_i);
				}
				if (highest_tree == 9) {
					break;
				}
			}
		}
		// Check right visibility
		highest_tree = -1;
		for (size_t tree_r = row_length - 1; tree_r > 0; --tree_r) {
			if (cur_row[tree_r] > highest_tree) {
				highest_tree = cur_row[tree_r];
				if (!hasTreeBeenFound(found_tree_grid, tree_r, row_i)) {
					++visible_trees;
					markTreeFound(found_tree_grid, tree_r, row_i);
				}
				if (highest_tree == 9) {
					break;
				}
			}
		}
	}

	for (size_t col_i = 1; col_i < row_length - 1; ++col_i) {
		// Check down visibility
		int highest_tree = -1;
		for (size_t row_i = 0; row_i < tree_grid.size() - 1; ++row_i) {
			if (tree_grid[row_i][col_i] > highest_tree) {
				highest_tree = tree_grid[row_i][col_i];
				if (!hasTreeBeenFound(found_tree_grid, col_i, row_i)) {
					++visible_trees;
					markTreeFound(found_tree_grid, col_i, row_i);
				}
				if (highest_tree == 9) {
					break;
				}
			}
		}
		// Check up visibility
		highest_tree = -1;
		for (size_t row_i = tree_grid.size() - 1; row_i > 0; --row_i) {
			if (tree_grid[row_i][col_i] > highest_tree) {
				highest_tree = tree_grid[row_i][col_i];
				if (!hasTreeBeenFound(found_tree_grid, col_i, row_i)) {
					++visible_trees;
					markTreeFound(found_tree_grid, col_i, row_i);
				}
				if (highest_tree == 9) {
					break;
				}
			}
		}
	}

	input.close();

	std::string answer;
	answer = std::to_string(visible_trees);
	output_answer(answer);
}

void problem_2::solve(const std::string& file_name)
{
	std::ifstream input(file_name);

	if (!input.is_open()) {
		return;
	}

	grid tree_grid;
	while (!input.eof()) {
		std::string input_line;
		std::getline(input, input_line);
		row input_row;
		for (char input_char : input_line) {
			input_row.push_back(input_char - '0');
		}
		tree_grid.emplace_back(input_row);
	}
	if (tree_grid.empty()) {
		return;
	}

	unsigned long long best_score = 0;
	for (size_t cur_row_i = 1; cur_row_i < tree_grid.size() - 1; ++cur_row_i) {
		const row& cur_row = tree_grid[cur_row_i];
		for (size_t cur_col_i = 1; cur_col_i < cur_row.size() - 1; ++cur_col_i) {
			char cur_place = cur_row[cur_col_i];
			unsigned long long cur_score = 1;
			unsigned long long cur_trees = 0;
			// Check right
			for (size_t test_col_i = cur_col_i + 1; test_col_i < cur_row.size(); ++test_col_i) {
				++cur_trees;
				if (cur_row[test_col_i] >= cur_place) {
					break;
				}
			}
			cur_score *= cur_trees;

			// Check left
			cur_trees = 0;
			for (int test_col_i = cur_col_i - 1; test_col_i >= 0; --test_col_i) {
				++cur_trees;
				if (cur_row[test_col_i] >= cur_place) {
					break;
				}
			}
			cur_score *= cur_trees;

			// Check up
			cur_trees = 0;
			for (int test_row_i = cur_row_i + 1; test_row_i < tree_grid.size(); ++test_row_i) {
				++cur_trees;
				if (tree_grid[test_row_i][cur_col_i] >= cur_place) {
					break;
				}
			}
			cur_score *= cur_trees;

			// Check down
			cur_trees = 0;
			for (int test_row_i = cur_row_i - 1; test_row_i >= 0; --test_row_i) {
				++cur_trees;
				if (tree_grid[test_row_i][cur_col_i] >= cur_place) {
					break;
				}
			}
			cur_score *= cur_trees;
			if (cur_score > best_score) {
				best_score = cur_score;
			}
		}
	}

	input.close();

	std::string answer;
	answer = std::to_string(best_score);
	output_answer(answer);
}