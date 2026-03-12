#include "Header.h"

int main()
{
    setlocale(LC_ALL, "ru");

    std::string InputS;
    std::cout << "Введите выражение (только цифры и знаки + - *):" << std::endl;
    std::cin >> InputS;

    // FIX_ME: Добавлена итеративная проверка ввода 
    if (!IsInputValid(InputS))
    {
        std::cout << "Ошибка: Некорректный формат выражения или неверные символы!" << std::endl;
        return 1;
    }

    // Выполнение основного алгоритма (рекурсивный разбор без циклов)
    int Result = CalculateExpression(InputS);
    std::cout << "Результат: " << Result << std::endl;

    return 0;
}
