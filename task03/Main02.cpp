#include "Header02.h"
#include <iostream>
#include <algorithm>

int main()
{
    setlocale(LC_ALL, "ru");

    try
    {
        std::string FileName;
        FileName = "FileName.txt";

        AviationNetwork Network;
        if (!Network.LoadFromFile(FileName))
        {
            throw std::runtime_error("Ошибка при загрузке данных из файла");
        }

        int K, L;
        std::cout << "Введите номер исходного города K: ";
        std::cin >> K;
        std::cout << "Введите количество пересадок L: ";
        std::cin >> L;

        std::vector<int> Cities = Network.FindCitiesWithTransfers(K, L);

        // Выводим результат
        std::cout << "Города, в которые можно долететь с " << L << " пересадками: ";
        for (size_t i = 0; i < Cities.size(); ++i)
        {
            std::cout << Cities[i];
            if (i < Cities.size() - 1)
            {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    catch (const std::exception& Exception)
    {
        std::cerr << "Ошибка: " << Exception.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "Неизвестная ошибка произошла во время выполнения программы." << std::endl;
        return 2;
    }

    main();

    return 0;
}