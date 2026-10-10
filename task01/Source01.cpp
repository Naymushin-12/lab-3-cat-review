#include "Header01.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <clocale>

FTelegraph::FTelegraph()
{
    // Инициализация словаря азбуки Морзе для русского алфавита
    // Используем заглавные буквы как ключи
    MorseDictionary = {
        {'А', ".-"}, {'Б', "-..."}, {'В', ".--"}, {'Г', "--."},
        {'Д', "-.."}, {'Е', "."}, {'Ж', "...-"}, {'З', "--.."},
        {'И', ".."}, {'Й', ".---"}, {'К', "-.-"}, {'Л', ".-.."},
        {'М', "--"}, {'Н', "-."}, {'О', "---"}, {'П', ".--."},
        {'Р', ".-."}, {'С', "..."}, {'Т', "-"}, {'У', "..-"},
        {'Ф', "..-."}, {'Х', "...."}, {'Ц', "-.-."}, {'Ч', "---."},
        {'Ш', "----"}, {'Щ', "--.-"}, {'Ъ', ".--.-."}, {'Ы', "-.--"},
        {'Ь', "-..-"}, {'Э', "..-.."}, {'Ю', "..--"}, {'Я', ".-."}
    };
}

void FTelegraph::SetupRussianConsole()
{
#ifdef _WIN32
    // Устанавливаем кодировку консоли Windows на CP1251
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif
    // Устанавливаем локаль для корректного ввода/вывода русских букв
    setlocale(LC_ALL, "Russian");
    std::setlocale(LC_ALL, "Russian");
}

bool FTelegraph::IsRussianLetter(char Symbol) const
{
    // Проверяем, является ли символ русской буквой (как заглавной, так и строчной)
    unsigned char Char = static_cast<unsigned char>(Symbol);

    // Диапазоны русских букв в CP1251
    // А-Я: 192-223, а-я: 224-255, Ё: 168, ё: 184
    return (Char >= 192 && Char <= 255) || Char == 168 || Char == 184;
}

char FTelegraph::ToRussianUpper(char Symbol) const
{
    unsigned char Char = static_cast<unsigned char>(Symbol);

    // Преобразование строчных русских букв в заглавные (CP1251)
    if (Char >= 224 && Char <= 255)
    {
        // а-я -> А-Я
        return static_cast<char>(Char - 32);
    }
    else if (Char == 184) // ё -> Ё
    {
        return static_cast<char>(168);
    }

    // Если символ уже заглавный или не русский, возвращаем как есть
    return Symbol;
}

std::string FTelegraph::ToUpperCase(const std::string& Text) const
{
    std::string Result;
    Result.reserve(Text.length());

    for (char Symbol : Text)
    {
        if (IsRussianLetter(Symbol))
        {
            Result += ToRussianUpper(Symbol);
        }
        else
        {
            // Для не русских символов используем стандартный toupper
            Result += static_cast<char>(std::toupper(static_cast<unsigned char>(Symbol)));
        }
    }

    return Result;
}

bool FTelegraph::IsValidRussianLetter(char Symbol) const
{
    // Проверяем, является ли символ русской буквой и есть ли он в словаре
    return IsRussianLetter(Symbol) && MorseDictionary.find(Symbol) != MorseDictionary.end();
}

std::string FTelegraph::GetAvailableSymbols() const
{
    std::string AvailableSymbols;
    for (const auto& Pair : MorseDictionary)
    {
        AvailableSymbols += Pair.first;
        AvailableSymbols += " ";
    }
    return AvailableSymbols;
}

std::string FTelegraph::ConvertCharToMorse(char Symbol) const
{
    auto It = MorseDictionary.find(Symbol);
    if (It != MorseDictionary.end())
    {
        return It->second;
    }
    return "";
}

std::string FTelegraph::ConvertToMorse(const std::string& InputText) const
{
    if (InputText.empty())
    {
        return "";
    }

    std::string UpperText = ToUpperCase(InputText);
    std::string Result;

    for (char Symbol : UpperText)
    {
        if (Symbol == ' ')
        {
            // Пробел между словами (в азбуке Морзе это пауза)
            Result += "  ";
        }
        else if (IsValidRussianLetter(Symbol))
        {
            std::string MorseCode = ConvertCharToMorse(Symbol);
            Result += MorseCode;
            Result += " "; // Пробел между буквами
        }
        else
        {
            // Некорректный символ - выбрасываем исключение
            std::string ErrorMsg = "Некорректный символ: '";
            ErrorMsg += Symbol;
            ErrorMsg += "' (код: " + std::to_string(static_cast<unsigned char>(Symbol)) + ")";
            throw std::invalid_argument(ErrorMsg);
        }
    }

    // Удаляем последний пробел, если он есть
    if (!Result.empty() && Result.back() == ' ')
    {
        Result.pop_back();
    }

    return Result;
}

void FTelegraph::PrintWelcomeMessage() const
{
    std::cout << "========================================\n";
    std::cout << "       ТЕЛЕГРАФ - АЗБУКА МОРЗЕ        \n";
    std::cout << "========================================\n";
    std::cout << "Программа для преобразования текста\n";
    std::cout << "в азбуку Морзе (русский алфавит)\n";
    std::cout << "========================================\n\n";
}

void FTelegraph::PrintHelp() const
{
    std::cout << "\n=== СПРАВКА ===\n";
    std::cout << "Доступные символы (русские буквы):\n";
    std::cout << GetAvailableSymbols() << "\n";
    std::cout << "Поддерживаются заглавные и строчные буквы\n";
    std::cout << "Символы в азбуке Морзе: '.' (точка) и '-' (тире)\n";
    std::cout << "Пробелы между словами сохраняются\n";
    std::cout << "Для выхода введите 'exit', 'quit' или 'выход'\n";
    std::cout << "Для справки введите 'help' или 'помощь'\n";
    std::cout << "================\n\n";
}