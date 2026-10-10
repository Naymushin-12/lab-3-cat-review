// https://deepseek.com
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>

// Коды операций
const int OPERATION_ADD = -1;      // Сложение
const int OPERATION_SUB = -2;      // Вычитание
const int OPERATION_MUL = -3;      // Умножение
const int OPERATION_DIV = -4;      // Деление нацело

// Структура узла дерева
struct TreeNode
{
    int Value;                              // Значение узла (отрицательное - операция, неотрицательное - операнд)
    std::shared_ptr<TreeNode> Left;         // Левый потомок
    std::shared_ptr<TreeNode> Right;        // Правый потомок

    // Конструктор
    TreeNode(int InValue) : Value(InValue), Left(nullptr), Right(nullptr) {}
};

// Класс для работы с деревом выражений
class ExpressionTree
{
public:
    ExpressionTree() : Root(nullptr) {}

    // Построение дерева из префиксного выражения
    bool BuildFromPrefix(const std::vector<std::string>& InTokens);

    // Загрузка выражения из файла
    bool LoadFromFile(const std::string& InFilename);

    // Преобразование дерева (удаление операций сложения и вычитания)
    void SimplifyAddSub();

    // Вычисление значения дерева
    int Evaluate();

    // Вывод дерева в красивой форме боком
    void PrintTree(bool bShowSimplified = false);

    // Получение корня дерева
    std::shared_ptr<TreeNode> GetRoot() const { return Root; }

private:
    std::shared_ptr<TreeNode> Root;

    // Рекурсивное построение дерева из токенов
    std::shared_ptr<TreeNode> BuildTreeRecursive(const std::vector<std::string>& InTokens, int& InOutIndex);

    // Рекурсивное упрощение дерева (удаление операций сложения и вычитания)
    std::shared_ptr<TreeNode> SimplifyNode(std::shared_ptr<TreeNode> InNode);

    // Вычисление значения узла
    int EvaluateNode(std::shared_ptr<TreeNode> InNode);

    // Рекурсивный вывод дерева боком с красивым форматированием
    void PrintTreeHorizontal(std::shared_ptr<TreeNode> InNode,
        const std::string& InRightPrefix = "",
        const std::string& InCurrentPrefix = "",
        const std::string& InLeftPrefix = "");

    // Получение строкового представления значения узла
    std::string GetNodeValueString(std::shared_ptr<TreeNode> InNode);

    // Проверка, является ли узел операцией
    bool IsOperation(std::shared_ptr<TreeNode> InNode) const;

    // Проверка, является ли узел операцией сложения или вычитания
    bool IsAddOrSub(std::shared_ptr<TreeNode> InNode) const;

    // Проверка корректности токенов
    bool ValidateTokens(const std::vector<std::string>& InTokens);
};