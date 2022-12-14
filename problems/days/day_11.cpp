#include "day_11.h"

#include "../common_includes.h"

#include "queue"
#include "vector"

PROBLEM_CLASS_CPP(11);

static constexpr char WHITESPACE_CHAR = ' ';
static constexpr char NUL_CHAR = '\0';
static constexpr char ONE_CHAR = '1';
static constexpr char NINE_CHAR = '9';
static constexpr char ID_CHAR = 'M';
static constexpr char ITEMS_CHAR = 'S';
static constexpr char OPERATION_CHAR = 'O';
static constexpr char TEST_CHAR = 'T';
static constexpr char IF_CHAR = 'I';
static constexpr size_t TEST_POS = 3;
static constexpr char TRUE_CHAR = 't';
static constexpr char FALSE_CHAR = 'f';
static constexpr char PLUS_CHAR = '+';
static constexpr char MULT_CHAR = '*';
static constexpr char SQR_CHAR = 'o';

static constexpr size_t MAX_ROUNDS = 20;

class monkey
{
public:
	enum class problem_num
	{
		ONE,
		TWO
	};

	monkey(std::ifstream& input, problem_num problem);

	void storeMonkeyReferences(std::vector<monkey>& monkeys);
	void performTurn();
	unsigned long long getItemsInspected() const { return m_items_inspected; }
	int getDivisibleBy() const { return m_divisible_by; }
	void receiveItem(unsigned long long item) { m_items.push(item); }

private:
	enum class stress_operator
	{
		MULT,
		ADD,
		SQR
	};

	problem_num m_problem;

	unsigned int m_id = 0;
	std::queue<unsigned long long> m_items;
	stress_operator m_operator = stress_operator::MULT;
	int m_operator_int = 0;
	int m_divisible_by = 1;
	size_t m_true_monkey_id = 0;
	size_t m_false_monkey_id = 0;

	monkey* m_true_monkey = nullptr;
	monkey* m_false_monkey = nullptr;

	unsigned long long m_items_inspected = 0;

	void performTurn1();
	void performTurn2();

	static unsigned long long m_super_modulo;
};
unsigned long long monkey::m_super_modulo = 1;

monkey::monkey(std::ifstream& input, problem_num problem) : m_problem(problem)
{
	while (!input.eof()) {
		std::string input_line;
		std::getline(input, input_line);
		if (input_line.empty()) {
			break;
		}

		const char* first_char = input_line.c_str();
		while (first_char[0] == WHITESPACE_CHAR) {
			++first_char;
		}

		auto find_first_number = [](const char* input) -> const char* {
			while ((input[0] < ONE_CHAR || input[0] > NINE_CHAR) && input[0] != NUL_CHAR) {
				++input;
			}
			return input;
		};

		switch (first_char[0]) {
			case ID_CHAR:
				m_id = atoi(find_first_number(first_char));
				break;
			case ITEMS_CHAR:
			{
				std::istringstream input_ss(find_first_number(first_char));
				char comma;
				int stress;
				while (!input_ss.eof()) {
					input_ss >> stress;
					m_items.push(stress);
					input_ss >> comma;
				}
			}
				break;
			case OPERATION_CHAR:
				while (first_char[0] != PLUS_CHAR && first_char[0] != MULT_CHAR) {
					++first_char;
				}

				if (first_char[2] == SQR_CHAR) {
					m_operator = stress_operator::SQR;
				} else {
					m_operator = first_char[0] == PLUS_CHAR ? stress_operator::ADD : stress_operator::MULT;
					m_operator_int = atoi(first_char + 2);
				}
				break;
			case TEST_CHAR:
				m_divisible_by = atoi(find_first_number(first_char));
				if (monkey::m_super_modulo % m_divisible_by != 0) {
					monkey::m_super_modulo *= m_divisible_by;
				}
				break;
			case IF_CHAR:
				if (first_char[TEST_POS] == TRUE_CHAR) {
					m_true_monkey_id = atoi(find_first_number(first_char));
				} else {
					m_false_monkey_id = atoi(find_first_number(first_char));
				}
				break;			
			default:
				break;
		}
	}
}

void monkey::storeMonkeyReferences(std::vector<monkey>& monkeys)
{
	m_true_monkey = &monkeys[m_true_monkey_id];
	m_false_monkey = &monkeys[m_false_monkey_id];
}

void monkey::performTurn()
{
	switch (m_problem) {
		case monkey::problem_num::ONE:
			performTurn1();
			break;
		case monkey::problem_num::TWO:
			performTurn2();
			break;
		default:
			break;
	}
}

void monkey::performTurn1()
{
	while (!m_items.empty()) {
		long long item = m_items.front();
		m_items.pop();

		switch (m_operator) {
			case monkey::stress_operator::MULT:
				item *= m_operator_int;
				break;
			case monkey::stress_operator::ADD:
				item += m_operator_int;
				break;
			case monkey::stress_operator::SQR:
				item *= item;
				break;
			default:
				break;
		}

		item /= 3;

		if ((item % m_divisible_by) == 0) {
			m_true_monkey->receiveItem(item);
		} else {
			m_false_monkey->receiveItem(item);
		}

		++m_items_inspected;
	}
}

void monkey::performTurn2()
{
	while (!m_items.empty()) {
		unsigned long long item = m_items.front();
		m_items.pop();

		switch (m_operator) {
			case monkey::stress_operator::MULT:
				item *= m_operator_int;
				break;
			case monkey::stress_operator::ADD:
				item += m_operator_int;
				break;
			case monkey::stress_operator::SQR:
				item *= item;
				break;
			default:
				break;
		}

		item = item % monkey::m_super_modulo;

		if ((item % m_divisible_by) == 0) {
			m_true_monkey->receiveItem(item);
		} else {
			m_false_monkey->receiveItem(item);
		}

		++m_items_inspected;
	}
}

void problem_1::solve(const std::string& file_name)
{
	std::ifstream input(file_name);

	if (!input.is_open()) {
		return;
	}

	std::vector<monkey> monkeys;

	while (!input.eof()) {
		monkeys.emplace_back(input, monkey::problem_num::ONE);
	}
	input.close();

	for (monkey& cur_monkey : monkeys) {
		cur_monkey.storeMonkeyReferences(monkeys);
	}

	for (size_t i = 0; i < MAX_ROUNDS; ++i) {
		for (monkey& cur_monkey : monkeys) {
			cur_monkey.performTurn();
		}
	}

	std::sort(monkeys.begin(), monkeys.end(), [](const monkey& l, const monkey& r) {
		return l.getItemsInspected() > r.getItemsInspected();
		});

	unsigned long long shenanigans = monkeys[0].getItemsInspected() * monkeys[1].getItemsInspected();

	std::string answer;
	answer = std::to_string(shenanigans);
	output_answer(answer);
}

static constexpr size_t MAX_ROUNDS_2 = 10000;

void problem_2::solve(const std::string& file_name)
{
	std::ifstream input(file_name);

	if (!input.is_open()) {
		return;
	}

	std::vector<monkey> monkeys;

	while (!input.eof()) {
		monkeys.emplace_back(input, monkey::problem_num::TWO);
	}
	input.close();

	for (monkey& cur_monkey : monkeys) {
		cur_monkey.storeMonkeyReferences(monkeys);
	}

	for (size_t i = 0; i < MAX_ROUNDS_2; ++i) {
		for (monkey& cur_monkey : monkeys) {
			cur_monkey.performTurn();
		}
	}

	std::sort(monkeys.begin(), monkeys.end(), [](const monkey& l, const monkey& r) {
		return l.getItemsInspected() > r.getItemsInspected();
		});

	unsigned long long shenanigans = static_cast<unsigned long long>(monkeys[0].getItemsInspected()) * static_cast<unsigned long long>(monkeys[1].getItemsInspected());

	std::string answer;
	answer = std::to_string(shenanigans);
	output_answer(answer);
}