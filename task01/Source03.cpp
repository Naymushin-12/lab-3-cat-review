#include "Header03.h"

Telegraph::Telegraph()
{
    InitializeMorse();
}

void Telegraph::InitializeMorse()
{
    MorseMap = {
        {L'А', ".-"},    {L'Б', "-..."},  {L'В', ".--"},   {L'Г', "--."},
        {L'Д', "-.."},   {L'Е', "."},     {L'Ж', "...-"},  {L'З', "--.."},
        {L'И', ".."},    {L'Й', ".---"},  {L'К', "-.-"},   {L'Л', ".-.."},
        {L'М', "--"},    {L'Н', "-."},    {L'О', "---"},   {L'П', ".--."},
        {L'Р', ".-."},   {L'С', "..."},   {L'Т', "-"},     {L'У', "..-"},
        {L'Ф', "..-."},  {L'Х', "...."},  {L'Ц', "-.-."},  {L'Ч', "---."},
        {L'Ш', "----"},  {L'Щ', "--.-"},  {L'Ъ', ".--.-."},{L'Ы', "-.--"},
        {L'Ь', "-..-"},  {L'Э', "..-.."}, {L'Ю', "..--"},  {L'Я', ".-.-"}
    };
}

wchar_t Telegraph::ToUpperRus(wchar_t Symbol)
{
    // Преобразование строчных русских букв в заглавные (диапазон а-я: 0x0430-0x044F)
    if (Symbol >= L'а' && Symbol <= L'я')
    {
        return static_cast<wchar_t>(Symbol - 0x20);
    }
    // ё -> Ё
    if (Symbol == L'ё')
    {
        return L'Ё';
    }
    return Symbol;
}

std::string Telegraph::EncodeMessage(const std::wstring& Message)
{
    std::string Result;

    for (wchar_t Symbol : Message)
    {
        if (Symbol == L' ')
        {
            // Пробел между словами
            Result += "  ";
            continue;
        }

        wchar_t UpperSymbol = ToUpperRus(Symbol);

        auto It = MorseMap.find(UpperSymbol);

        if (It != MorseMap.end())
        {
            Result += It->second;
            Result += " "; // Пробел между буквами
        }
        else
        {
            // Недопустимый символ — пропускаем или выводим как есть
            Result += "? ";
        }
    }

    // Убираем последний пробел
    if (!Result.empty() && Result.back() == ' ')
    {
        Result.pop_back();
    }

    return Result;
}