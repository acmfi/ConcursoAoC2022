#include <iostream>
#include <fstream>

using uint = unsigned int;
constexpr auto PATH = "input"; // input, sample

uint matchScoreByShape()
{
	std::ifstream input;
	input.open(PATH);

	uint score{};
	char rivalMove;
	char ourMove;

	while (input >> rivalMove && input >> ourMove)
	{
		score += (uint)(ourMove - 'X') + 1;

		// Congruencias módulo 3
		switch ((uint)(ourMove - rivalMove) % 3) {
		case (uint)('X' - 'A') % 3:
			score += 3;
			break;
		case (uint)('Y' - 'A') % 3:
			score += 6;
		}
	}

	return score;
}

uint matchScoreByResult()
{
	std::ifstream input;
	input.open(PATH);

	uint score{};
	char rivalMove;
	char duelResult;

	while (input >> rivalMove && input >> duelResult)
	{
		switch (duelResult) {
		case 'Y':
			score += 3;
			break;
		case 'Z':
			score += 6;
		}

		uint a = (uint)((duelResult - 'X' + 3) + (rivalMove - 'A')) % 3;
		// Si el resto es 0, añade 3 puntos
		score += a ? a : 3;
	}

	return score;
}

int main()
{
	// Parte 1 - Juega la partida asumiendo que dice qué jugar
	std::cout << "1 - El resultado del primer modelo es " << matchScoreByShape() << '\n';
	// Parte 2 - Juega la partida asumiendo si ganar, perder o empatar
	std::cout << "2 - El resultado del segundo modelo es " << matchScoreByResult() << '\n';
}

// Primer modelo: 12855
// Segundo modelo: 13726