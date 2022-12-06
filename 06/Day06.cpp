#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

using uint = unsigned int;
constexpr auto PATH = "input"; // input, sample

uint findDistinctCharacters(const std::string& line, const uint length)
{
    for (uint i = 0; i < line.length() - length; i++)
    {
        std::unordered_set<char> prevChars;

        for (uint j = 0; j < length; j++)
        {
            prevChars.insert(line.at(i + j));
        }

        if (prevChars.size() == length)
            return (i + length);
    }

    return -1;
}

int main()
{
    std::ifstream input(PATH);
    std::string line;
    std::getline(input, line);
    std::cout << "1 - Para encontrar el inicio del paquete son necesarios "
        << findDistinctCharacters(line, 4) << " caracteres\n";
    std::cout << "1 - Para encontrar el inicio del mensaje son necesarios "
        << findDistinctCharacters(line, 14) << " caracteres\n";
}

// Primer marcador: 1480
// Segundo marcador: 2746