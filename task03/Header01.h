// https://deepseek.com
#pragma once

#include <vector>
#include <string>

/**
 * @brief Класс для работы с графом авиасообщений
 *
 * Класс предоставляет функционал для загрузки матрицы смежности из файла
 * и поиска городов, достижимых из заданного города с заданным количеством пересадок
 */
class AviationGraph
{
private:
    int n;                                  // Количество городов
    std::vector<std::vector<int>> AdjacencyMatrix;  // Матрица смежности

public:
    /**
     * @brief Конструктор по умолчанию
     */
    AviationGraph();

    /**
     * @brief Загрузка данных из файла
     * @param FileName Имя файла для загрузки
     * @return true - если загрузка успешна, false - в противном случае
     */
    bool LoadFromFile(const std::string& FileName);

    /**
     * @brief Поиск городов, достижимых из города K с L пересадками
     * @param K Город отправления (нумерация с 1)
     * @param L Количество пересадок
     * @return Вектор с номерами городов (нумерация с 1), удовлетворяющих условию
     */
    std::vector<int> FindCitiesWithExactTransfers(int K, int L) const;

    /**
     * @brief Получение количества городов
     * @return Количество городов в графе
     */
    int GetCityCount() const;

    /**
     * @brief Вывод матрицы смежности (для отладки)
     */
    void PrintAdjacencyMatrix() const;
};

/**
 * @brief Очистка буфера ввода
 *
 * Функция очищает буфер ввода после некорректного ввода
 */
void ClearInputBuffer();


/**
 * @brief Вывод результата поиска
 *
 * @param Result Вектор с номерами городов
 */
void PrintResult(const std::vector<int>& Result);