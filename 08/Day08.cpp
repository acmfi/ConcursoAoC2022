#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using uint = unsigned int;
#define Map std::vector<std::vector<Tree>>
constexpr auto PATH = "input"; // input, sample

struct Tree
{
    const uint height;
    bool bIsVisible;
};

Map readMap()
{
    std::ifstream input(PATH);
    std::string line;
    Map map;
    while (std::getline(input, line))
    {
        std::vector<Tree> row;
        for (char c : line)
            row.push_back(Tree{ (uint)(c - '0'), false });
        map.push_back(row);
    }

    return map;
}

void calculateVisibility(Map* map)
{
    // Izquierda a derecha
    for (uint i = 0; i < map->size(); i++)
    {
        Tree* currentTree = &(map->at(i).at(0));
        currentTree->bIsVisible = true;
        uint maxHeight = currentTree->height;

        for (uint j = 1; j < map->at(i).size(); j++)
        {
            currentTree = &(map->at(i).at(j));
            if (currentTree->height > maxHeight)
            {
                maxHeight = currentTree->height;
                currentTree->bIsVisible = true;
            }
        }
    }

    // Derecha a izquierda
    for (uint i = 0; i < map->size(); i++)
    {
        uint lastIndex = map->at(i).size() - 1;
        Tree* currentTree = &(map->at(i).at(lastIndex));
        currentTree->bIsVisible = true;
        uint maxHeight = currentTree->height;

        for (int j = lastIndex - 1; j >= 0; j--)
        {
            currentTree = &(map->at(i).at(j));
            if (currentTree->height > maxHeight)
            {
                maxHeight = currentTree->height;
                currentTree->bIsVisible = true;
            }
        }
    }

    // Arriba a abajo
    // Asume que son todos del mismo tamaño
    for (uint j = 1; j < map->at(0).size(); j++)
    {
        Tree* currentTree = &(map->at(0).at(j));
        currentTree->bIsVisible = true;
        uint maxHeight = currentTree->height;

        for (uint i = 1; i < map->size(); i++)
        {
            currentTree = &(map->at(i).at(j));
            if (currentTree->height > maxHeight)
            {
                maxHeight = currentTree->height;
                currentTree->bIsVisible = true;
            }
        }
    }

    // Abajo a arriba
    for (uint j = 1; j < map->at(0).size(); j++)
    {
        uint lastIndex = map->size() - 1;
        Tree* currentTree = &(map->at(lastIndex).at(j));
        currentTree->bIsVisible = true;
        uint maxHeight = currentTree->height;

        for (int i = lastIndex - 1; i >= 0; i--)
        {
            currentTree = &(map->at(i).at(j));
            if (currentTree->height > maxHeight)
            {
                maxHeight = currentTree->height;
                currentTree->bIsVisible = true;
            }
        }
    }
}

uint countVisibleTrees(const Map& map)
{
    uint visibleCount = 0;
    for (std::vector<Tree> row : map)
        for (Tree tree : row)
            if(tree.bIsVisible) visibleCount++;

    return visibleCount;
}

uint calculateHighestScore(const Map& map)
{
    uint highestScore = 0;
    for (uint i = 1; i < map.size() - 1; i++)
        for (uint j = 1; j < map.at(i).size() - 1; j++)
        {
            uint totalScore;
            uint sideScore;
            int x;
            Tree currentTree(map.at(i).at(j));

            // Vistas hacia la izquierda
            sideScore = 0;
            x = j - 1;
            while (x >= 0)
            {
                sideScore++;
                if (map.at(i).at(x).height >= currentTree.height)
                    break;
                x--;
            }
            totalScore = sideScore;

            // Vistas hacia arriba
            sideScore = 0;
            x = i - 1;
            while (x >= 0)
            {
                sideScore++;
                if (map.at(x).at(j).height >= currentTree.height)
                    break;
                x--;
            }
            totalScore *= sideScore;

            // Vistas hacia la derecha
            sideScore = 0;
            x = j + 1;
            while (x < map.at(i).size())
            {
                sideScore++;
                if (map.at(i).at(x).height >= currentTree.height)
                    break;
                x++;
            }
            totalScore *= sideScore;

            // Vistas hacia abajo
            sideScore = 0;
            x = i + 1;
            while (x < map.at(i).size())
            {
                sideScore++;
                if (map.at(x).at(j).height >= currentTree.height)
                    break;
                x++;
            }
            totalScore *= sideScore;

            if (totalScore > highestScore)
                highestScore = totalScore;
        }

    return highestScore;
}

int main()
{
    Map map = readMap();
    calculateVisibility(&map);
    std::cout << "1 - El total visible es " << countVisibleTrees(map) << '\n';
    std::cout << "2 - La mayor cantidad de puntos es " << calculateHighestScore(map) << '\n';
}

// Árboles visibles: 1794
// Mejor puntuaje: 199272