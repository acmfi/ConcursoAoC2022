#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <stdio.h>

using uint = unsigned int;
constexpr auto PATH = "input"; // input, sample

uint addStrengths(const std::unordered_set<uint>& readCycles)
{
    std::ifstream input(PATH);
    std::string line;

    int reg = 1;
    uint cycles = 0;
    uint strength = 0;

    while (std::getline(input, line))
    {
        std::istringstream ss(line);
        std::string op;
        std::getline(ss, op, ' ');

        cycles++;
        if (readCycles.find(cycles) != readCycles.end())
        {
            strength += reg * cycles;
        }

        if (op[0] == 'a')
        {
            cycles++;
            if (readCycles.find(cycles) != readCycles.end())
            {
                strength += reg * cycles;
            }
            std::string valString;
            std::getline(ss, valString, ' ');
            reg += std::stoi(valString);
        }
    }

    return strength;
}

void drawPixel(const uint& pos, const int& reg)
{
    int dif = (pos % 40) - reg;
    if (abs(dif) <= 1)
    {
        printf("#");
    }
    else
    {
        printf(".");
    }

    if ((pos % 40) == 39)
    {
        printf("\n");
    }
}

void drawScreen()
{
    std::ifstream input(PATH);
    std::string line;

    int reg = 1;
    uint cycles = 0;

    while (std::getline(input, line))
    {
        std::istringstream ss(line);
        std::string op;
        std::getline(ss, op, ' ');


        drawPixel(cycles, reg);
        cycles++;

        if (op[0] == 'a')
        {
            drawPixel(cycles, reg);
            cycles++;

            std::string valString;
            std::getline(ss, valString, ' ');
            reg += std::stoi(valString);
        }
    }
}

int main()
{
    std::unordered_set<uint> readCycles = { 20, 60, 100, 140, 180, 220 };
    std::cout << "1 - La suma de los valores del resgistro es "
        << addStrengths(readCycles) << '\n';
    std::cout << "2 - La pantalla dibujada es:\n";
    drawScreen();
}

// Los valores suman: 14560
// Las letras son: EKRHEPUZ