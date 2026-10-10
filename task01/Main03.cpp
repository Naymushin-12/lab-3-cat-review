#include <iostream>
#include <locale>
#include <windows.h>
#include "Header03.h"

int main()
{
    // Включаем UTF-8 в консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::locale::global(std::locale(""));

    std::wcin.imbue(std::locale());
    std::wcout.imbue(std::locale());

    Telegraph TelegraphApp;

    std::wstring Input;

    std::wcout << L"=== ТЕЛЕГРАФ (АЗБУКА МОРЗЕ) ===\n";
    std::wcout << L"Введите сообщение на русском языке:\n";

    std::getline(std::wcin, Input);

    if (Input.empty())
    {
        std::wcout << L"Ошибка: пустая строка!\n";
        return 1;
    }

    std::string Result = TelegraphApp.EncodeMessage(Input);

    std::cout << "\nРЕЗУЛЬТАТ:\n";
    std::cout << Result << std::endl;

    main();
    return 0;
}