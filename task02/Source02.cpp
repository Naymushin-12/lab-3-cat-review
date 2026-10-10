#include "Header02.h"

bool Tree::BuildFromPrefix(const std::string& Expression)
{
    size_t Pos = 0;
    Root = ParsePrefix(Expression, Pos);
    return Root != nullptr;
}

std::shared_ptr<TreeNode> Tree::ParsePrefix(const std::string& Expr, size_t& Pos)
{
    if (Pos >= Expr.size())
    {
        return nullptr;
    }

    char Current = Expr[Pos++];

    // Пропускаем пробелы
    while (Pos < Expr.size() && Expr[Pos] == ' ')
    {
        Pos++;
    }

    if (isdigit(Current))
    {
        // Операнд (цифра 0–9)
        return std::make_shared<TreeNode>(Current - '0');
    }
    else
    {
        // Операция
        int OpCode;
        switch (Current)
        {
        case '+':
            OpCode = -1;
            break;
        case '-':
            OpCode = -2;
            break;
        case '*':
            OpCode = -3;
            break;
        case '/':
            OpCode = -4;
            break;
        default:
            return nullptr; // Неизвестная операция
        }

        auto Node = std::make_shared<TreeNode>(OpCode);
        Node->Left = ParsePrefix(Expr, Pos);
        Node->Right = ParsePrefix(Expr, Pos);
        return Node;
    }
}

void Tree::TransformTree()
{
    if (Root)
    {
        EvaluateAndReplace(Root);
    }
}

int Tree::EvaluateAndReplace(std::shared_ptr<TreeNode>& Node)
{
    if (!Node)
    {
        return 0;
    }

    // Если это лист (операнд), возвращаем его значение
    if (!Node->Left && !Node->Right)
    {
        return Node->Data;
    }

    // Рекурсивно вычисляем значения поддеревьев
    int LeftVal = EvaluateAndReplace(Node->Left);
    int RightVal = EvaluateAndReplace(Node->Right);

    // Выполняем операцию в зависимости от кода
    switch (Node->Data)
    {
    case -1: // Сложение (+)
    case -2: // Вычитание (-)
    {
        int Result;
        if (Node->Data == -1)
        {
            Result = LeftVal + RightVal;
        }
        else
        {
            Result = LeftVal - RightVal;
        }
        // Заменяем узел с операцией на узел с результатом
        Node = std::make_shared<TreeNode>(Result);
        return Result;
    }
    case -3: // Умножение (*)
    case -4: // Деление (/)
    {
        if (Node->Data == -4 && RightVal == 0)
        {
            throw std::runtime_error("Ошибка: деление на ноль");
        }
        return (Node->Data == -3) ? LeftVal * RightVal : LeftVal / RightVal;
    }
    default:
        throw std::runtime_error("Неизвестная операция в дереве");
    }
}

void Tree::PrintTree() const
{
    PrintTreeH(Root, "", "", "");
    std::cout << std::endl;
}

void Tree::PrintTreeH(std::shared_ptr<TreeNode> const& Node,
    const std::string& RPref,
    const std::string& CPref,
    const std::string& LPref) const
{
    if (!Node)
    {
        return;
    }

    if (Node->Right)
    {
        PrintTreeH(Node->Right,
            RPref + "    ",
            RPref + "--- ",
            RPref + "|   ");
    }

    std::cout << CPref << Node->Data << std::endl;

    if (Node->Left)
    {
        PrintTreeH(Node->Left,
            LPref + "|   ",
            LPref + "--- ",
            LPref + "    ");
    }
}