#include "Header.h"

int main()
{
    // Настройка локали для корректного отображения кириллицы
    setlocale(LC_ALL, "ru");

    // FIX_ME: Отсутствие std::, несколько операторов на одной строке
    // ind_i = i; ind_j = j; weight = main_vector[i][j]; volume = sum_volume_vector[i][j];

    SolveArchaeologistTask();

    std::cout << std::endl;
    return 0;
}
