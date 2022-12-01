#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

constexpr auto PATH = "input"; // input, sample

using uint = unsigned int;

// Devuelve un vector con las calorías ordenadas de menor a mayor
std::vector<uint> getSortedCalories()
{
    std::vector<uint> caloriesList;

    std::ifstream input;
    input.open(PATH);

    std::string line;
    while (!input.eof())
    {
        uint elfCalories{};
        while (std::getline(input, line) && !line.empty())
        {
            elfCalories += std::stoul(line);
        }
        caloriesList.push_back(elfCalories);
    }

    std::sort(caloriesList.begin(), caloriesList.end());
    return caloriesList;
}

int main()
{
    std::vector<uint> calList = getSortedCalories();

    // Parte 1 - Selecciona de la lista la mayor cantidad de calorías empaquetadas
    std::cout
        << "1 - La mayor cantidad de cal. es "
        << calList.back() << '\n';

    // Parte 2 - Selecciona de la lista la suma de las 3 mayores cantidades de calorías empaquetadas
    std::cout
        << "2 - La suma de las 3 mayores cal. es "
        << std::accumulate(calList.end() - 3, calList.end(), 0) << '\n';
}

// Mayor cantidad: 70613
// Suma 3 mayores: 205805