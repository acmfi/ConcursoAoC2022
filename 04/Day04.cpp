#include <iostream>
#include <fstream>

using uint = unsigned int;
constexpr auto PATH = "input"; // input, sample

uint getAllContained() {
    std::ifstream input;
    input.open(PATH);

    uint totalContained = 0;

    while (!input.eof())
    {
        uint elfOneStart;
        uint elfOneEnd;
        uint elfTwoStart;
        uint elfTwoEnd;

        input >> elfOneStart;
        input.ignore(1);
        input >> elfOneEnd;
        input.ignore(1);
        input >> elfTwoStart;
        input.ignore(1);
        input >> elfTwoEnd;

        if (elfOneStart > elfTwoStart && elfOneEnd <= elfTwoEnd)
            totalContained++;
        else if (elfOneStart < elfTwoStart && elfOneEnd >= elfTwoEnd)
            totalContained++;
        else if (elfOneStart == elfTwoStart)
            totalContained++;
    }

    return totalContained;
}

int main()
{
    std::cout << "El total de rangos contenidos es " << getAllContained();
}