#pragma once

#include <iostream>
#include <string>

// Проверяет строку на наличие недопустимых символов и баланс скобок.
bool IsInputValid(const std::string & InS);

// Основная рекурсивная функция вычисления выражения.
int CalculateExpression(std::string InExpression);

// Вспомогательная рекурсивная функция для поиска оператора во время разбора.
int FindOperatorRecursive(const std::string& InS, int InIndex, int InLevel, const std::string& InOps);
