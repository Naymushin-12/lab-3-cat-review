#include "Header03.h"

int main()
{
    setlocale(LC_ALL, "ru");

    try
    {
        Tree tree;

        // Загрузка из файла
        tree.LoadFromFile("filename.txt");

        cout << "Исходное дерево:\n";
        tree.PrintTree();

        // Упрощение
        tree.Simplify();

        cout << "Преобразованное дерево:\n";
        tree.PrintTree();

        // Вывод указателя на корень
        cout << "Адрес корня: " << tree.GetRoot() << endl;
    }
    catch (const exception& ex)
    {
        cout << "Ошибка: " << ex.what() << endl;
    }

    return 0;
}