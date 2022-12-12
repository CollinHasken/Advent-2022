#include "day_9.h"

#include "../common_includes.h"

PROBLEM_CLASS_CPP(9);

#include "set"

typedef std::pair<short, short> coord;

void problem_1::solve(const std::string& file_name)
{
	std::ifstream input(file_name);

	if (!input.is_open()) {
		return;
	}

	std::set<coord> visited_coords;

	short head_x = 0, head_y = 0;
	short tail_x = 0, tail_y = 0;
	while (!input.eof()) {
		std::string input_line;
		std::getline(input, input_line);

		char direction;
		unsigned short distance;
		std::istringstream input_ss(input_line);

		input_ss >> direction >> distance;
		for (unsigned short i = 0; i < distance; ++i) {
			switch (direction) {
				case 'R':
					if (head_x > tail_x) {
						++tail_x;
						tail_y = head_y;
					}
					++head_x;
					break;
				case 'L':
					if (head_x < tail_x) {
						--tail_x;
						tail_y = head_y;
					}
					--head_x;
					break;
				case 'U':
					if (head_y > tail_y) {
						++tail_y;
						tail_x = head_x;
					}
					++head_y;
					break;
				case 'D':
					if (head_y < tail_y) {
						--tail_y;
						tail_x = head_x;
					}
					--head_y;
					break;
				default:
					break;
			}
			visited_coords.insert(std::make_pair(tail_x, tail_y));
		}
	}

	input.close();

	size_t visits = visited_coords.size();

	std::string answer;
	answer = std::to_string(visits);
	output_answer(answer);
}

class knot
{
public:
	knot(const coord& start_coord) : m_coord(start_coord) {};
	~knot() { if (m_next_knot) delete m_next_knot; };
	knot* makeKnot();
	bool move(const coord& new_coord);
	const coord& getCoord() { return m_coord; }

private:
	coord m_coord = std::make_pair(0, 0);
	knot* m_next_knot = nullptr;
};

knot* knot::makeKnot()
{
	m_next_knot = new knot(m_coord);
	return m_next_knot;
}

bool knot::move(const coord& new_coord)
{
	if (new_coord == m_coord) {
		return false;
	}

	m_coord = new_coord;

	if (m_next_knot) {
		const coord& next_coord = m_next_knot->m_coord;
		// Need to move to the right?
		coord new_coord = next_coord;
		if (abs(next_coord.first - m_coord.first) == 2) {
			new_coord.first += next_coord.first < m_coord.first ? 1 : -1;
			if (next_coord.second != m_coord.second) {
				new_coord.second += next_coord.second < m_coord.second ? 1 : -1;
			}
		} else if (abs(next_coord.second - m_coord.second) == 2) {
			new_coord.second += next_coord.second < m_coord.second ? 1 : -1;
			if (next_coord.first != m_coord.first) {
				new_coord.first += next_coord.first < m_coord.first ? 1 : -1;
			}
		}

		return m_next_knot->move(new_coord);
	}

	return true;
}

static constexpr coord ORIGIN = std::make_pair(0, 0);
static constexpr size_t NUM_KNOTS = 10;

void problem_2::solve(const std::string& file_name)
{
	std::ifstream input(file_name);

	if (!input.is_open()) {
		return;
	}

	knot* head_knot = new knot(ORIGIN);
	knot* tail_knot = head_knot;
	for (size_t k = 1; k < NUM_KNOTS; ++k) {
		tail_knot = tail_knot->makeKnot();
	}
	coord head_coord = ORIGIN;

	std::set<coord> visited_coords;
	visited_coords.insert(tail_knot->getCoord());

	while (!input.eof()) {
		std::string input_line;
		std::getline(input, input_line);

		char direction;
		unsigned short distance;
		std::istringstream input_ss(input_line);

		input_ss >> direction >> distance;
		for (unsigned short i = 0; i < distance; ++i) {
			switch (direction) {
				case 'R':
					++head_coord.first;
					break;
				case 'L':
					--head_coord.first;
					break;
				case 'U':
					++head_coord.second;
					break;
				case 'D':
					--head_coord.second;
					break;
				default:
					break;
			}
			if (head_knot->move(head_coord)) {
				visited_coords.insert(tail_knot->getCoord());
			}
		}
	}

	input.close();
	delete head_knot;

	size_t visits = visited_coords.size();

	std::string answer;
	answer = std::to_string(visits);
	output_answer(answer);
}