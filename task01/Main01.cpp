#include "Header01.h"
#include <iostream>
#include <string>
#include <limits>

/**
 * Обрабатывает пользовательский ввод и выводит результат
 */
void ProcessUserInput(FTelegraph& Telegraph, const std::string& Input)
{
    try
    {
        if (Input.empty())
        {
            std::cout << "Ошибка: Введена пустая строка\n";
            return;
        }

        // Проверка на пустую строку с пробелами
        bool OnlySpaces = true;
        for (char Symbol : Input)
        {
            if (Symbol != ' ')
            {
                OnlySpaces = false;
                break;
            }
        }

        if (OnlySpaces)
        {
            std::cout << "Ошибка: Строка содержит только пробелы\n";
            return;
        }

        std::string MorseResult = Telegraph.ConvertToMorse(Input);

        std::cout << "\n=== РЕЗУЛЬТАТ ===\n";
        std::cout << "Исходное сообщение: " << Input << "\n";
        std::cout << "Азбука Морзе: " << MorseResult << "\n";
        std::cout << "==================\n\n";
    }
    catch (const std::invalid_argument& Exception)
    {
        std::cout << "\n!!! ОШИБКА !!!\n";
        std::cout << Exception.what() << "\n";
        std::cout << "Используйте только русские буквы и пробелы.\n";
        std::cout << "Введите 'help' для списка доступных символов.\n\n";
    }
    catch (const std::exception& Exception)
    {
        std::cout << "\n!!! НЕИЗВЕСТНАЯ ОШИБКА !!!\n";
        std::cout << Exception.what() << "\n\n";
    }
}

/**
 * Основная функция программы
 */
int main()
{
    // Устанавливаем русскую кодировку консоли
    FTelegraph::SetupRussianConsole();

    FTelegraph Telegraph;

    // Выводим приветственное сообщение
    Telegraph.PrintWelcomeMessage();
    Telegraph.PrintHelp();

    std::string UserInput;

    // Основной цикл программы
    while (true)
    {
        std::cout << "Введите сообщение: ";

        // Очищаем поток ввода перед getline для корректной работы
        std::getline(std::cin, UserInput);

        // Проверка на ошибку ввода
        if (std::cin.eof())
        {
            std::cout << "\nДо свидания! Спасибо за использование программы.\n";
            break;
        }

        // Проверка на команды выхода
        if (UserInput == "exit" || UserInput == "quit" ||
            UserInput == "выход" || UserInput == "ВЫХОД")
        {
            std::cout << "\nДо свидания! Спасибо за использование программы.\n";
            break;
        }

        // Проверка на команду справки
        if (UserInput == "help" || UserInput == "HELP" ||
            UserInput == "помощь" || UserInput == "ПОМОЩЬ")
        {
            Telegraph.PrintHelp();
            continue;
        }

        // Обработка обычного ввода
        ProcessUserInput(Telegraph, UserInput);
    }

    return 0;
}