#include "day_3.h"

#include "../common_includes.h"

PROBLEM_CLASS_CPP(3);

// Map a - z to 1 - 26 and A - Z to 27 - 52
unsigned int charToItemPriority(char item)
{
	return item > 'Z' ? item - 'a' + 1 : item - 'A' + 27;
}

void problem_1::solve(const std::string& file_name)
{
	std::ifstream input(file_name);

	if (!input.is_open()) {
		return;
	}

	unsigned int priorities = 0;
	while (!input.eof()) {
		std::string input_line;
		std::getline(input, input_line);

		// Make a mask of the found items, with their priority as the index
		// Iterate from both sides to find collision faster
		long long found_items_mask_l = 0;
		long long found_items_mask_r = 0;
		for (size_t l = 0, r = input_line.length() - 1; r > l; ++l, --r) {
			unsigned int item_l = charToItemPriority(input_line[l]);
			unsigned int item_r = charToItemPriority(input_line[r]);
			found_items_mask_l |= (1ll << item_l);
			// If the left item makes the masks collide, then this is the item type
			if (found_items_mask_l & found_items_mask_r) {
				priorities += item_l;
				break;
			}
			// If the right item makes the masks collide, then this is the item type
			found_items_mask_r |= (1ll << item_r);
			if (found_items_mask_l & found_items_mask_r) {
				priorities += item_r;
				break;
			}
		}
	}

	input.close();

	std::string answer;
	answer = std::to_string(priorities);
	output_answer(answer);
}

static constexpr size_t MAX_ELFS_IN_GROUP = 3;

void problem_2::solve(const std::string& file_name)
{
	std::ifstream input(file_name);

	if (!input.is_open()) {
		return;
	}

	unsigned int priorities = 0;
	while (!input.eof()) {

		// Collect each elf in the group's input and make a mask
		long long found_items_masks[MAX_ELFS_IN_GROUP] = { 0 };
		std::string input_lines[MAX_ELFS_IN_GROUP];
		size_t max_input_length = 0;
		size_t input_lengths[MAX_ELFS_IN_GROUP] = { 0 };
		for (size_t elf = 0; elf < MAX_ELFS_IN_GROUP; ++elf) {
			std::getline(input, input_lines[elf]);
			input_lengths[elf] = input_lines[elf].length();
			max_input_length = max(max_input_length, input_lengths[elf]);
		}

		// Go through each input at the same time to find collisions faster
		bool found_badge = false;
		for (size_t i = 0; i < max_input_length; ++i) {
			for (size_t elf = 0; elf < MAX_ELFS_IN_GROUP; ++elf) {
				// Don't iterate on shorter inputs
				if (i >= input_lengths[elf]) {
					continue;
				}

				unsigned int item = charToItemPriority(input_lines[elf][i]);
				found_items_masks[elf] |= (1ll << item);

				// See if this item is in all of the masks
				long long found_items_mask = found_items_masks[0];
				for (size_t elf_mask = 1; elf_mask < MAX_ELFS_IN_GROUP; ++elf_mask) {
					found_items_mask &= found_items_masks[elf_mask];
					if (!found_items_mask) {
						break;
					}
				}

				// Found the badge if all elves have it
				if (found_items_mask) {
					found_badge = true;
					priorities += item;
					break;
				}
			}
			if (found_badge) {
				break;
			}
		}
	}

	input.close();

	std::string answer;
	answer = std::to_string(priorities);
	output_answer(answer);
}