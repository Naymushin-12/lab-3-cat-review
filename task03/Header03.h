// https://alice.yandex.ru
#pragma once
#include <iostream>
#include <vector>
#include <string>

// Класс графа авиасообщения
class Graph
{
public:
    Graph();

    // Загрузка графа из файла
    void LoadGraphFromFile(const std::string& FileName);

    // Поиск городов с L пересадками
    std::vector<int> FindReachableCities(int StartCity, int Transfers);

private:
    int CityCount;
    std::vector<std::vector<int>> AdjacencyMatrix;
};