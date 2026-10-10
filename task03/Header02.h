// https://alice.yandex.ru/
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

/**
 * Класс для работы со схемой авиационного сообщения.
 */
class AviationNetwork
{
public:
    /**
     * Конструктор. Инициализирует объект.
     */
    AviationNetwork();

    /**
     * Загружает данные из файла: количество городов и матрицу смежности.
     * @param FileName Имя файла с данными.
     * @return true, если загрузка успешна, false в противном случае.
     */
    bool LoadFromFile(const std::string& FileName);

    /**
     * Находит города, в которые можно долететь из города K ровно с L пересадками по кратчайшему пути.
     * @param K Исходный город (нумерация с 1).
     * @param L Количество пересадок.
     * @return Вектор номеров городов в порядке возрастания или {-1}, если таких городов нет.
     */
    std::vector<int> FindCitiesWithTransfers(int K, int L) const;

private:
    int NumCities; // Количество городов
    std::vector<std::vector<int>> AdjacencyMatrix; // Матрица смежности

    /**
     * Проверяет корректность входных параметров.
     * @param K Исходный город.
     * @param L Количество пересадок.
     * @return true, если параметры корректны, false иначе.
     */
    bool ValidateInput(int K, int L) const;
};