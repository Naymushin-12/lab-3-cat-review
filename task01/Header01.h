// https://deepseek.com
#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

/**
 * Класс для преобразования текста в азбуку Морзе
 * Соответствует стандарту Epic Games C++ Coding Standard
 */
class FTelegraph
{
public:
    // Конструктор и деструктор
    FTelegraph();
    ~FTelegraph() = default;

    // Запрещаем копирование (RAII принцип)
    FTelegraph(const FTelegraph&) = delete;
    FTelegraph& operator=(const FTelegraph&) = delete;

    // Основные методы
    std::string ConvertToMorse(const std::string& InputText) const;
    bool IsValidRussianLetter(char Symbol) const;
    std::string GetAvailableSymbols() const;

    // Методы для UI
    void PrintWelcomeMessage() const;
    void PrintHelp() const;

    // Метод для установки русской кодировки
    static void SetupRussianConsole();

private:
    // Словарь азбуки Морзе для русских букв
    std::unordered_map<char, std::string> MorseDictionary;

    // Вспомогательные методы
    std::string ConvertCharToMorse(char Symbol) const;
    std::string ToUpperCase(const std::string& Text) const;
    bool IsRussianLetter(char Symbol) const;
    char ToRussianUpper(char Symbol) const;
};