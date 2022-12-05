#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using uint = unsigned int;
constexpr auto PATH = "sample"; // input, sample

std::vector<std::vector<char>> loadCrates() {
    std::ifstream input(PATH);
    std::vector<std::vector<char>> crates;

    std::string line;
    std::getline(input, line);

    for (uint i = 0; (i * 4) + 1 < line.length(); i++)
    {
        char c = line[(i * 4) + 1];
        crates.push_back(std::vector<char>());
        if (c != ' ')
            crates[i].push_back(c);
    }

    while (std::getline(input, line) && line[1] != '1')
    {
        for (uint i = 0; (i * 4) + 1 < line.length(); i++)
        {
            char c = line[(i * 4) + 1];
            if (c != ' ')
                crates[i].push_back(c);
        }
    }

    return crates;
}

int main()
{
    auto crates = loadCrates();

}