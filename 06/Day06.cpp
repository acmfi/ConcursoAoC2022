#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

using uint = unsigned int;
constexpr auto PATH = "input"; // input, sample

int main()
{
    std::ifstream input(PATH);
    std::string line;
    std::getline(input, line);
    for (uint i = 0; i < line.length() - 3; i++)
    {
        std::unordered_set<char> prevChars;

        prevChars.insert(line.at(i));
        prevChars.insert(line.at(i + 1));
        prevChars.insert(line.at(i + 2));
        prevChars.insert(line.at(i + 3));
        if (prevChars.size() == 4)
            return (i + 3 + 1);
    }
}