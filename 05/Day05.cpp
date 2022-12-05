#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using uint = unsigned int;
constexpr auto PATH = "input"; // input, sample

struct Instruction {
    uint from;
    uint to;
    uint places;
};

void loadData(
    std::vector<std::vector<char>>& crates,
    std::vector<Instruction>& instructions
)
{
    std::ifstream input(PATH);

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

    for(int i = 0; i < crates.size(); i++)
        std::reverse(std::begin(crates[i]), std::end(crates[i]));

    getline(input, line);
    while (std::getline(input, line))
    {
        uint places;
        uint from;
        uint to;

        std::istringstream stream(line);
        stream.ignore(5);
        stream >> places;
        stream.ignore(6);
        stream >> from;
        stream.ignore(4);
        stream >> to;

        instructions.push_back({from - 1, to - 1, places});
    }
}

char* moveOneByOne(std::vector<std::vector<char>>& crates, std::vector<Instruction> instructions)
{
    for (Instruction ins : instructions)
    {
        for (int _ = 0; _ < ins.places; _++)
        {
            if (ins.places == 2 && ins.from == 9 && ins.places == 5)
                break;
            crates[ins.to].push_back(crates[ins.from].back());
            crates[ins.from].pop_back();
        }
    }

    // Código de C que no debería estar aquí
    char* buffer = (char*)malloc((crates.size() + 1) * sizeof(char));
    for (uint i = 0; i < crates.size(); i++)
        buffer[i] = crates[i].back();
    buffer[crates.size()] = '\0';
    return buffer;
}

char* moveAll(std::vector<std::vector<char>>& crates, std::vector<Instruction> instructions)
{
    for (Instruction i : instructions)
    {
        for (auto it = std::end(crates[i.from]) - i.places; it < std::end(crates[i.from]); it++)
        {
            crates[i.to].push_back(*it);
        }

        crates[i.from].erase(std::end(crates[i.from]) - i.places, std::end(crates[i.from]));
    }

    // Código de C que no debería estar aquí
    char* buffer = (char*)malloc((crates.size() + 1) * sizeof(char));
    for (uint i = 0; i < crates.size(); i++)
        buffer[i] = crates[i].back();
    buffer[crates.size()] = '\0';
    return buffer;
}

int main()
{
    std::vector<std::vector<char>> crates;
    std::vector <Instruction> instructions;
    loadData(crates, instructions);

    std::cout << "La parte superior de las pilas es " << moveOneByOne(crates, instructions);
    return 0;
}