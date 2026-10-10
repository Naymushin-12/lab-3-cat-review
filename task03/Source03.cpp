#include "Header03.h"
#include <fstream>
#include <queue>
#include <stdexcept>
#include <algorithm>

// Конструктор
Graph::Graph()
{
    CityCount = 0;
}

// Загрузка графа из файла
void Graph::LoadGraphFromFile(const std::string& FileName)
{
    std::ifstream File(FileName);

    if (!File)
    {
        throw std::runtime_error("Не удалось открыть файл");
    }

    File >> CityCount;

    if (CityCount <= 0 || CityCount > 25)
    {
        throw std::runtime_error("Некорректное количество городов");
    }

    AdjacencyMatrix.assign(CityCount, std::vector<int>(CityCount));

    for (int i = 0; i < CityCount; i++)
    {
        for (int j = 0; j < CityCount; j++)
        {
            File >> AdjacencyMatrix[i][j];

            if (AdjacencyMatrix[i][j] != 0 && AdjacencyMatrix[i][j] != 1)
            {
                throw std::runtime_error("Матрица должна содержать только 0 и 1");
            }
        }
    }
}

// Поиск городов с L пересадками
std::vector<int> Graph::FindReachableCities(int StartCity, int Transfers)
{
    if (StartCity < 1 || StartCity > CityCount)
    {
        throw std::runtime_error("Некорректный номер города");
    }

    std::vector<int> Distance(CityCount, -1);
    std::queue<int> Queue;

    int StartIndex = StartCity - 1;
    Distance[StartIndex] = 0;
    Queue.push(StartIndex);

    // BFS — поиск кратчайших путей
    while (!Queue.empty())
    {
        int Current = Queue.front();
        Queue.pop();

        for (int i = 0; i < CityCount; i++)
        {
            if (AdjacencyMatrix[Current][i] == 1 && Distance[i] == -1)
            {
                Distance[i] = Distance[Current] + 1;
                Queue.push(i);
            }
        }
    }

    std::vector<int> Result;
    int RequiredDistance = Transfers + 1;

    for (int i = 0; i < CityCount; i++)
    {
        if (Distance[i] == RequiredDistance)
        {
            Result.push_back(i + 1);
        }
    }

    std::sort(Result.begin(), Result.end());

    return Result;
}