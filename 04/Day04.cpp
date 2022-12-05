#include <iostream>
#include <fstream>

using uint = unsigned int;
constexpr auto PATH = "input"; // input, sample

bool loadRange(std::ifstream& input, uint& r1Start, uint& r1End, uint& r2Start, uint& r2End)
{
	// Sólo comprobamos el primero
	if (!(input >> r1Start))
		return false;
	input.ignore(1);
	input >> r1End;
	input.ignore(1);
	input >> r2Start;
	input.ignore(1);
	input >> r2End;
	input.ignore(1);

	return true;
}

uint getAllContained()
{
	std::ifstream input;
	input.open(PATH);

	uint totalContained = 0;

	uint elfOneStart;
	uint elfOneEnd;
	uint elfTwoStart;
	uint elfTwoEnd;

	while (loadRange(input, elfOneStart, elfOneEnd, elfTwoStart, elfTwoEnd))
	{
		if ((elfOneStart >= elfTwoStart && elfOneEnd <= elfTwoEnd) ||
			(elfOneStart <= elfTwoStart && elfOneEnd >= elfTwoEnd))
		{
			totalContained++;
		}
	}

	return totalContained;
}

uint getAllOverlapped()
{
	std::ifstream input;
	input.open(PATH);

	uint totalOverlap = 0;

	uint elfOneStart;
	uint elfOneEnd;
	uint elfTwoStart;
	uint elfTwoEnd;

	while (loadRange(input, elfOneStart, elfOneEnd, elfTwoStart, elfTwoEnd))
	{
		if ((elfOneStart <= elfTwoStart && elfTwoStart <= elfOneEnd) ||
			(elfTwoStart <= elfOneStart && elfOneStart <= elfTwoEnd))
		{
			totalOverlap++;
		}
	}

	return totalOverlap;
}

int main()
{
	std::cout << "1 - El total de rangos contenidos es " << getAllContained() << '\n';
	std::cout << "2 - El total de rangos que se superponen es " << getAllOverlapped() << '\n';
}

// Primera parte: 444
// Segunda parte: 801