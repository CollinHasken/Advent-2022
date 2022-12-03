#include "day_2.h"

#include "../common_includes.h"

PROBLEM_CLASS_CPP(2);

static constexpr unsigned int LOSS_POINTS = 0;
static constexpr unsigned int TIE_POINTS = 3;
static constexpr unsigned int WIN_POINTS = 6;

enum class rps
{
	ROCK = 0,
	PAPER,
	SCISSORS,

	COUNT
};

rps charToRPS(char c)
{
	switch (c) {
		case 'A':
		case 'X':
			return rps::ROCK;
		case 'B':
		case 'Y':
			return rps::PAPER;
		case 'C':
		case 'Z':
			return rps::SCISSORS;
		default:
			return rps::COUNT;
	}
}

rps getPreviousRPS(rps cur)
{
	int prev = static_cast<int>(cur) - 1;
	return prev < 0 ? getPreviousRPS(rps::COUNT) : static_cast<rps>(prev);
}

unsigned int getPoints(rps cur)
{
	return static_cast<unsigned int>(cur) + 1;
}

unsigned int calculateMatchPoints(rps player, rps opponent)
{
	unsigned int points = getPoints(player);
	if (player == opponent) {
		return points + TIE_POINTS;
	}
	if (getPreviousRPS(player) == opponent) {
		return points + WIN_POINTS;
	}
	return points + LOSS_POINTS;
}

void problem_1::solve(const std::string& file_name)
{
	std::ifstream input(file_name);

	if (!input.is_open()) {
		return;
	}

	unsigned int sum = 0;
	while (!input.eof()) {
		std::string input_line;
		std::getline(input, input_line);

		rps opponent = charToRPS(input_line[0]);
		rps player = charToRPS(input_line[2]);

		sum += calculateMatchPoints(player, opponent);
	}

	input.close();

	std::string answer;
	answer = std::to_string(sum);
	output_answer(answer);
}

enum class outcome
{
	LOSS,
	TIE,
	WIN,

	COUNT
};

outcome charToOutcome(char c)
{
	switch (c) {
		case 'X':
			return outcome::LOSS;
		case 'Y':
			return outcome::TIE;
		case 'Z':
			return outcome::WIN;
		default:
			return outcome::COUNT;
	}
}

rps getNextRPS(rps cur)
{
	unsigned int next = static_cast<unsigned int>(cur) + 1;
	return next == static_cast<unsigned int>(rps::COUNT) ? static_cast<rps>(0) : static_cast<rps>(next);
}

rps getRequiredResponse(rps opponent, outcome _outcome)
{
	switch (_outcome) {
		case outcome::LOSS:
			return getPreviousRPS(opponent);
		case outcome::TIE:
			return opponent;
		case outcome::WIN:
			return getNextRPS(opponent);
		default:
			return opponent;
	}
}

unsigned int calculateMatchPoints2(rps opponent, outcome _outcome)
{
	rps response = getRequiredResponse(opponent, _outcome);
	unsigned int points = getPoints(response);
	switch (_outcome) {
		case outcome::LOSS:
			return points + LOSS_POINTS;
		case outcome::TIE:
			return points + TIE_POINTS;
		case outcome::WIN:
			return points + WIN_POINTS;
		default:
			return 0;
	}
}

void problem_2::solve(const std::string& file_name)
{
	std::ifstream input(file_name);

	if (!input.is_open()) {
		return;
	}

	unsigned int sum = 0;
	while (!input.eof()) {
		std::string input_line;
		std::getline(input, input_line);

		rps opponent = charToRPS(input_line[0]);
		outcome _outcome = charToOutcome(input_line[2]);

		sum += calculateMatchPoints2(opponent, _outcome);
	}

	input.close();

	std::string answer;
	answer = std::to_string(sum);
	output_answer(answer);
}