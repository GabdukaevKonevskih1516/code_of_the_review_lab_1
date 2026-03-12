#include "Header.h"
#include <cctype> 

// Проверка строки на корректность : баланс скобок и допустимые символы.
bool IsInputValid(const std::string & InS)
{
    if (InS.empty()) return false;

    int BracketBalance = 0;
    for (char C : InS)
    {
        // 1. Проверка на недопустимые символы (буквы, спецсимволы)
        if (!std::isdigit(C) && C != '+' && C != '-' && C != '*' && C != '(' && C != ')')
        {
            return false;
        }

        // 2. Подсчет баланса скобок
        if (C == '(') BracketBalance++;
        if (C == ')') BracketBalance--;

        // Если закрывающих скобок стало больше, чем открывающих в любой момент
        if (BracketBalance < 0) return false;
    }

    return BracketBalance == 0;
}

// Рекурсивный поиск оператора(внутренняя логика).
int FindOperatorRecursive(const std::string & InS, int InIndex, int InLevel, const std::string & InOps)
{
    if (InIndex < 0) return -1;

    if (InS[InIndex] == ')') return FindOperatorRecursive(InS, InIndex - 1, InLevel + 1, InOps);
    if (InS[InIndex] == '(') return FindOperatorRecursive(InS, InIndex - 1, InLevel - 1, InOps);

    if (InLevel == 0 && InOps.find(InS[InIndex]) != std::string::npos)ф
    {
        return InIndex;
    }

    return FindOperatorRecursive(InS, InIndex - 1, InLevel, InOps);
}

int CalculateExpression(std::string InExpression)
{
    // Убираем внешние скобки, если они лишние: ( (2+2) ) -> (2+2)
    if (InExpression.length() > 2 && InExpression[0] == '(' && InExpression[InExpression.length() - 1] == ')')
    {
        // Проверяем, что эти скобки действительно пара (не (1+1)+(2+2))
        int OpPos = FindOperatorRecursive(InExpression, InExpression.length() - 1, 0, "+-*");
        if (OpPos == -1)
        {
            return CalculateExpression(InExpression.substr(1, InExpression.length() - 2));
        }
    }

    // Ищем + или -
    int OpPos = FindOperatorRecursive(InExpression, InExpression.length() - 1, 0, "+-");
    if (OpPos != -1)
    {
        char Op = InExpression[OpPos];
        std::string Left = InExpression.substr(0, OpPos);
        std::string Right = InExpression.substr(OpPos + 1);

        return (Op == '+') ?
            CalculateExpression(Left) + CalculateExpression(Right) :
            CalculateExpression(Left) - CalculateExpression(Right);
    }

    // Ищем *
    OpPos = FindOperatorRecursive(InExpression, InExpression.length() - 1, 0, "*");
    if (OpPos != -1)
    {
        return CalculateExpression(InExpression.substr(0, OpPos)) * CalculateExpression(InExpression.substr(OpPos + 1));
    }

    // Терминальный случай: это должна быть цифра
    if (!InExpression.empty() && std::isdigit(InExpression[0]))
    {
        return InExpression[0] - '0';
    }

    return 0;
}
