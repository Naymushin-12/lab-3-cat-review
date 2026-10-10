#include "Header03.h"

int main()
{
    setlocale(LC_ALL, "ru");

    try
    {
        Graph FlightGraph;

        // Загружаем данные из файла
        FlightGraph.LoadGraphFromFile("FileName.txt");

        int StartCity;
        int Transfers;

        std::cout << "Введите город K: ";
        std::cin >> StartCity;

        std::cout << "Введите количество пересадок L: ";
        std::cin >> Transfers;

        if (Transfers < 0)
        {
            throw std::runtime_error("Количество пересадок не может быть отрицательным");
        }

        std::vector<int> Cities = FlightGraph.FindReachableCities(StartCity, Transfers);

        if (Cities.empty())
        {
            std::cout << -1 << std::endl;
        }
        else
        {
            for (int City : Cities)
            {
                std::cout << City << " ";
            }
            std::cout << std::endl;
        }
    }
    catch (const std::exception& Error)
    {
        std::cout << "Ошибка: " << Error.what() << std::endl;
    }

    main();
    return 0;
}