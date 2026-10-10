// https://chatgpt.com
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

// Узел дерева
struct TreeNode
{
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value);
};

// Класс дерева
class Tree
{
private:
    TreeNode* root;

    // Рекурсивное построение дерева из префиксной строки
    TreeNode* BuildTree(const string& expr, int& pos);

    // Рекурсивное упрощение дерева
    TreeNode* SimplifyTree(TreeNode* node);

    // Вычисление поддерева
    int Evaluate(TreeNode* node);

    // Удаление дерева (освобождение памяти)
    void DeleteTree(TreeNode* node);

    // Печать дерева боком
    void printTreeH(TreeNode const* node,
        string const& rpref,
        string const& cpref,
        string const& lpref) const;

public:
    Tree();
    ~Tree();

    // Загрузка выражения из файла и построение дерева
    void LoadFromFile(const string& filename);

    // Упрощение дерева (убрать + и -)
    void Simplify();

    // Печать дерева
    void PrintTree() const;

    TreeNode* GetRoot() const;
};