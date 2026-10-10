#include "Header01.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <algorithm>
#include <sstream>

/**
 * @brief Конструктор по умолчанию
 *
 * Инициализирует граф с нулевым количеством городов
 */
AviationGraph::AviationGraph() :
    n(0)
{
}

/**
 * @brief Загрузка данных из файла
 *
 * Функция читает файл с матрицей смежности и заполняет внутренние структуры данных
 *
 * @param FileName Имя файла для загрузки
 * @return true - если загрузка успешна, false - в противном случае
 */
bool AviationGraph::LoadFromFile(const std::string& FileName)
{
    std::ifstream InputFile(FileName);

    // Проверка на открытие файла
    if (!InputFile.is_open())
    {
        std::cerr << "Ошибка: Не удалось открыть файл " << FileName << std::endl;
        return false;
    }

    // Чтение количества городов
    std::string FirstLine;
    if (!std::getline(InputFile, FirstLine))
    {
        std::cerr << "Ошибка: Файл пуст" << std::endl;
        return false;
    }

    // Преобразование строки в число
    std::stringstream Ss(FirstLine);
    if (!(Ss >> n))
    {
        std::cerr << "Ошибка: Неверный формат первой строки (ожидается число)" << std::endl;
        return false;
    }

    // Проверка допустимого количества городов
    if (n <= 0 || n > 25)
    {
        std::cerr << "Ошибка: Количество городов должно быть от 1 до 25 (получено: " << n << ")" << std::endl;
        return false;
    }

    // Инициализация матрицы смежности
    AdjacencyMatrix.assign(n, std::vector<int>(n, 0));

    // Чтение матрицы смежности
    for (int i = 0; i < n; ++i)
    {
        std::string Line;
        if (!std::getline(InputFile, Line))
        {
            std::cerr << "Ошибка: Недостаточно строк в файле (ожидается " << n << " строк)" << std::endl;
            return false;
        }

        std::stringstream LineStream(Line);
        for (int j = 0; j < n; ++j)
        {
            int Value;
            if (!(LineStream >> Value))
            {
                std::cerr << "Ошибка: Неверный формат матрицы в строке " << (i + 2) << std::endl;
                return false;
            }

            // Проверка допустимых значений матрицы
            if (Value != 0 && Value != 1)
            {
                std::cerr << "Ошибка: В матрице смежности допустимы только 0 и 1 (строка " << (i + 2)
                    << ", столбец " << (j + 1) << ")" << std::endl;
                return false;
            }

            AdjacencyMatrix[i][j] = Value;
        }
    }

    InputFile.close();
    return true;
}

/**
 * @brief Поиск городов, достижимых из города K с L пересадками
 *
 * Функция использует BFS (поиск в ширину) для нахождения всех городов,
 * достижимых из заданного города ровно с L пересадками для самого короткого пути.
 *
 * Внимание: L пересадок означает, что в пути есть L промежуточных городов,
 * то есть количество перелетов = L + 1
 *
 * @param K Город отправления (нумерация с 1)
 * @param L Количество пересадок
 * @return Вектор с номерами городов (нумерация с 1), удовлетворяющих условию
 */
std::vector<int> AviationGraph::FindCitiesWithExactTransfers(int K, int L) const
{
    std::vector<int> Result;

    // Проверка корректности входных данных
    if (n == 0 || K < 1 || K > n)
    {
        std::cerr << "Ошибка: Неверный номер города K = " << K
            << " (допустимые значения: 1.." << n << ")" << std::endl;
        return Result;
    }

    if (L < 0)
    {
        std::cerr << "Ошибка: Количество пересадок не может быть отрицательным (L = " << L << ")" << std::endl;
        return Result;
    }

    // Массив для хранения расстояний (количества ПЕРЕЛЕТОВ) от города K
    std::vector<int> Distance(n, -1);

    // BFS (поиск в ширину)
    std::queue<int> Queue;
    int StartCity = K - 1; // Переход к нумерации с 0
    Distance[StartCity] = 0; // 0 перелетов до стартового города
    Queue.push(StartCity);

    while (!Queue.empty())
    {
        int Current = Queue.front();
        Queue.pop();

        // Обход всех соседних городов
        for (int Next = 0; Next < n; ++Next)
        {
            // Если есть прямой рейс и город еще не посещен
            if (AdjacencyMatrix[Current][Next] == 1 && Distance[Next] == -1)
            {
                Distance[Next] = Distance[Current] + 1; // Количество перелетов увеличивается на 1
                Queue.push(Next);
            }
        }
    }

    // Сбор городов, до которых количество ПЕРЕЛЕТОВ равно L + 1
    // Потому что L пересадок = L + 1 перелетов
    int RequiredFlights = L + 1;

    for (int i = 0; i < n; ++i)
    {
        // Исключаем сам город отправления и проверяем количество перелетов
        if (i != StartCity && Distance[i] == RequiredFlights)
        {
            Result.push_back(i + 1); // Переход к нумерации с 1
        }
    }

    // Сортировка результата в порядке возрастания
    std::sort(Result.begin(), Result.end());

    return Result;
}

/**
 * @brief Получение количества городов
 * @return Количество городов в графе
 */
int AviationGraph::GetCityCount() const
{
    return n;
}

/**
 * @brief Вывод матрицы смежности (для отладки)
 *
 * Функция выводит загруженную матрицу смежности на экран
 */
void AviationGraph::PrintAdjacencyMatrix() const
{
    if (n == 0)
    {
        std::cout << "Матрица не загружена" << std::endl;
        return;
    }

    std::cout << "\nМатрица смежности:" << std::endl;
    std::cout << "  ";
    for (int j = 0; j < n; ++j)
    {
        std::cout << j + 1 << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < n; ++i)
    {
        std::cout << i + 1 << " ";
        for (int j = 0; j < n; ++j)
        {
            std::cout << AdjacencyMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}