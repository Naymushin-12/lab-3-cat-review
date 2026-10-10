#include "Header01.h"
#include <iostream>
#include <string>
#include <limits>

/**
 * @brief Очистка буфера ввода
 *
 * Функция очищает буфер ввода после некорректного ввода
 */
void ClearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/**
 * @brief Вывод результата поиска
 *
 * @param Result Вектор с номерами городов
 */
void PrintResult(const std::vector<int>& Result)
{
    if (Result.empty())
    {
        std::cout << "-1" << std::endl;
    }
    else
    {
        for (size_t i = 0; i < Result.size(); ++i)
        {
            std::cout << Result[i];
            if (i < Result.size() - 1)
            {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

/**
 * @brief Главная функция программы
 *
 * Автоматически загружает файл FileName.txt и выполняет поиск городов
 * с заданным количеством пересадок
 *
 * @return int Код завершения программы
 */
int main()
{
    setlocale(LC_ALL, "ru");

    const std::string FileName = "FileName.txt";

    std::cout << "========================================" << std::endl;
    std::cout << "Анализ схемы авиационного сообщения" << std::endl;
    std::cout << "========================================" << std::endl;

    AviationGraph Graph;

    // Автоматическая загрузка файла
    std::cout << "Загрузка данных из файла " << FileName << "..." << std::endl;

    if (!Graph.LoadFromFile(FileName))
    {
        std::cerr << "Ошибка: Не удалось загрузить данные. Программа завершена." << std::endl;
        return 1;
    }

    std::cout << "Данные успешно загружены" << std::endl;
    std::cout << "Количество городов: " << Graph.GetCityCount() << std::endl;
    Graph.PrintAdjacencyMatrix();

    // Ввод данных для поиска
    int K, L;

    std::cout << "\nВведите номер города отправления K (1-" << Graph.GetCityCount() << "): ";
    if (!(std::cin >> K))
    {
        ClearInputBuffer();
        std::cerr << "Ошибка: Неверный ввод числа" << std::endl;
        return 1;
    }

    std::cout << "Введите количество пересадок L (0 и более): ";
    if (!(std::cin >> L))
    {
        ClearInputBuffer();
        std::cerr << "Ошибка: Неверный ввод числа" << std::endl;
        return 1;
    }

    std::cout << "\nРезультат поиска городов, в которые из города " << K
        << " можно долететь ровно с " << L << " пересадками:" << std::endl;

    std::vector<int> Result = Graph.FindCitiesWithExactTransfers(K, L);
    PrintResult(Result);

    return 0;
}