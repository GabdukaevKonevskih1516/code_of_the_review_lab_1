#include "Header.h"

int main()
{
    // FIX_ME: Отсутствие локали и вызов логики прямо в main
    // setlocale полезен для вывода
    std::setlocale(LC_ALL, "ru");

    SolveKNumericalTask();

    return 0;
}
