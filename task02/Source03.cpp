#include "Header03.h"

// Конструктор узла
TreeNode::TreeNode(int value)
{
    data = value;
    left = nullptr;
    right = nullptr;
}

// Конструктор дерева
Tree::Tree()
{
    root = nullptr;
}

// Деструктор дерева
Tree::~Tree()
{
    DeleteTree(root);
}

// Удаление дерева
void Tree::DeleteTree(TreeNode* node)
{
    if (!node) return;
    DeleteTree(node->left);
    DeleteTree(node->right);
    delete node;
}

// Загрузка из файла и построение дерева
void Tree::LoadFromFile(const string& filename)
{
    ifstream file(filename);
    if (!file)
        throw runtime_error("Ошибка открытия файла");

    string expr;
    file >> expr;

    int pos = 0;
    root = BuildTree(expr, pos);

    if (pos != expr.size())
        throw runtime_error("Некорректное выражение");
}

// Построение дерева из префиксного выражения
TreeNode* Tree::BuildTree(const string& expr, int& pos)
{
    if (pos >= expr.size())
        throw runtime_error("Ошибка разбора выражения");

    char ch = expr[pos++];

    // Операнд
    if (isdigit(ch))
    {
        return new TreeNode(ch - '0');
    }

    // Операция
    int op;
    switch (ch)
    {
    case '+': op = -1; break;
    case '-': op = -2; break;
    case '*': op = -3; break;
    case '/': op = -4; break;
    default:
        throw runtime_error("Неизвестный символ");
    }

    TreeNode* node = new TreeNode(op);
    node->left = BuildTree(expr, pos);
    node->right = BuildTree(expr, pos);

    return node;
}

// Вычисление поддерева
int Tree::Evaluate(TreeNode* node)
{
    if (!node)
        throw runtime_error("Ошибка вычисления");

    // Если число
    if (node->data >= 0)
        return node->data;

    int left = Evaluate(node->left);
    int right = Evaluate(node->right);

    switch (node->data)
    {
    case -1: return left + right;
    case -2: return left - right;
    case -3: return left * right;
    case -4:
        if (right == 0)
            throw runtime_error("Деление на ноль");
        return left / right;
    }

    throw runtime_error("Неизвестная операция");
}

// Упрощение дерева (замена + и - на число)
TreeNode* Tree::SimplifyTree(TreeNode* node)
{
    if (!node) return nullptr;

    node->left = SimplifyTree(node->left);
    node->right = SimplifyTree(node->right);

    if (node->data == -1 || node->data == -2)
    {
        int value = Evaluate(node);

        DeleteTree(node->left);
        DeleteTree(node->right);

        node->left = nullptr;
        node->right = nullptr;
        node->data = value;
    }

    return node;
}

// Запуск упрощения
void Tree::Simplify()
{
    root = SimplifyTree(root);
}

// Печать дерева
void Tree::printTreeH(TreeNode const* node,
    string const& rpref,
    string const& cpref,
    string const& lpref) const
{
    if (!node) return;

    if (node->right)
    {
        printTreeH(node->right,
            rpref + "    ",
            rpref + "--- ",
            rpref + "|   ");
    }

    cout << cpref << node->data << endl;

    if (node->left)
    {
        printTreeH(node->left,
            lpref + "|   ",
            lpref + "--- ",
            lpref + "    ");
    }
}

// Публичный вывод дерева
void Tree::PrintTree() const
{
    printTreeH(root, "", "", "");
    cout << endl;
}

// Получить корень
TreeNode* Tree::GetRoot() const
{
    return root;
}