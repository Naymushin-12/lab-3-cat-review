#include "Header02.h"
#include <stdexcept>
#include <algorithm>

AviationNetwork::AviationNetwork()
    : NumCities(0)
{
}

bool AviationNetwork::LoadFromFile(const std::string& FileName)
{
    std::ifstream InputFile(FileName);
    if (!InputFile.is_open())
    {
        throw std::runtime_error("Ошибка: не удалось открыть файл " + FileName);
    }

    // Читаем количество городов
    InputFile >> NumCities;
    if (NumCities <= 0 || NumCities > 25)
    {
        throw std::runtime_error("Ошибка: некорректное количество городов");
    }

    AdjacencyMatrix.resize(NumCities, std::vector<int>(NumCities));

    // Читаем матрицу смежности
    for (int i = 0; i < NumCities; ++i)
    {
        for (int j = 0; j < NumCities; ++j)
        {
            InputFile >> AdjacencyMatrix[i][j];
            if (AdjacencyMatrix[i][j] != 0 && AdjacencyMatrix[i][j] != 1)
            {
                throw std::runtime_error("Ошибка: некорректные данные в матрице смежности");
            }
        }
    }

    InputFile.close();
    return true;
}

bool AviationNetwork::ValidateInput(int K, int L) const
{
    if (K < 1 || K > NumCities)
    {
        throw std::runtime_error("Ошибка: номер города K выходит за допустимые пределы");
    }
    if (L < 0)
    {
        throw std::runtime_error("Ошибка: количество пересадок L не может быть отрицательным");
    }
    return true;
}

std::vector<int> AviationNetwork::FindCitiesWithTransfers(int K, int L) const
{
    // Проверяем корректность входных данных
    if (K < 1 || K > NumCities)
    {
        throw std::runtime_error("Ошибка: номер города K выходит за допустимые пределы");
    }
    if (L < 0)
    {
        throw std::runtime_error("Ошибка: количество пересадок L не может быть отрицательным");
    }

    std::vector<int> Distance(NumCities, -1);
    std::queue<int> Queue;

    int StartIndex = K - 1;
    Distance[StartIndex] = 0;
    Queue.push(StartIndex);

    // BFS — поиск кратчайших путей
    while (!Queue.empty())
    {
        int Current = Queue.front();
        Queue.pop();

        for (int Next = 0; Next < NumCities; ++Next)
        {
            if (AdjacencyMatrix[Current][Next] == 1 && Distance[Next] == -1)
            {
                Distance[Next] = Distance[Current] + 1;
                Queue.push(Next);
            }
        }
    }

    // Ключевое изменение: правильная интерпретация L пересадок
    // L пересадок = L промежуточных городов = L+1 перелётов
    std::vector<int> Result;
    int RequiredFlights = L + 1;  // Количество перелётов для L пересадок

    for (int City = 0; City < NumCities; ++City)
    {
        // Исключаем исходный город из результата
        if (Distance[City] == RequiredFlights && City != StartIndex)
        {
            Result.push_back(City + 1);  // Возвращаем к 1-индексации
        }
    }

    // Если нет городов с нужным количеством пересадок, возвращаем {-1}
    if (Result.empty())
    {
        return { -1 };
    }

    // Сортируем результат в порядке возрастания
    std::sort(Result.begin(), Result.end());
    return Result;
}