#include "Header.h"

bool IsBoardSizeValid(int InN)
{
    return InN > 1 && InN < 80;
}

void SolveLameKingTask()
{
    // FIX_ME: Использование коротких имен (inputFile), отсутствие проверки открытия в стиле Epic
    // ifstream inputFile("input1.txt");
    std::ifstream KingInput("input1.txt");
    std::ofstream KingOutput("output1.txt");

    if (!KingInput.is_open())
    {
        std::cerr << "Error: Could not open input1.txt" << std::endl;
        return;
    }

    int BoardSize = 0;
    if (!(KingInput >> BoardSize) || !IsBoardSizeValid(BoardSize))
    {
        std::cerr << "Error: Invalid board size" << std::endl;
        return;
    }

    // FIX_ME: Использование snake_case (board), отсутствие std::
    // vector<vector<int>> board(n, vector<int>(n));
    std::vector<std::vector<int>> BoardGrid(BoardSize, std::vector<int>(BoardSize));

    // Цикл считывания значений неприятностей на доске
    for (int i = 0; i < BoardSize; ++i)
    {
        for (int j = 0; j < BoardSize; ++j)
        {
            if (!(KingInput >> BoardGrid[i][j]))
            {
                std::cerr << "Error: Failed to read board values" << std::endl;
                return;
            }
        }
    }
    KingInput.close();

    // Таблицы для динамического программирования
    // MinDistances[i][j] — минимальные неприятности до клетки (i, j)
    std::vector<std::vector<int>> MinDistances(BoardSize, std::vector<int>(BoardSize, 0));
    // PathSteps[i][j] — символ движения ('L' или 'D')
    std::vector<std::vector<char>> PathSteps(BoardSize, std::vector<char>(BoardSize, ' '));

    // Начальная точка: правый верхний угол (0, N-1)
    MinDistances[0][BoardSize - 1] = BoardGrid[0][BoardSize - 1];

    // Цикл заполнения первого столбца (движение только вниз от старта)
    for (int i = 1; i < BoardSize; ++i)
    {
        MinDistances[i][BoardSize - 1] = MinDistances[i - 1][BoardSize - 1] + BoardGrid[i][BoardSize - 1];
        PathSteps[i][BoardSize - 1] = 'D';
    }

    // Цикл заполнения первой строки (движение только влево от старта)
    for (int j = BoardSize - 2; j >= 0; --j)
    {
        MinDistances[0][j] = MinDistances[0][j + 1] + BoardGrid[0][j];
        PathSteps[0][j] = 'L';
    }

    // 

    // Основной цикл DP: заполнение оставшейся части доски
    for (int i = 1; i < BoardSize; ++i)
    {
        for (int j = BoardSize - 2; j >= 0; --j)
        {
            // Сравниваем, откуда дешевле прийти: сверху (D) или справа (L)
            if (MinDistances[i - 1][j] < MinDistances[i][j + 1])
            {
                MinDistances[i][j] = MinDistances[i - 1][j] + BoardGrid[i][j];
                PathSteps[i][j] = 'D';
            }
            else
            {
                MinDistances[i][j] = MinDistances[i][j + 1] + BoardGrid[i][j];
                PathSteps[i][j] = 'L';
            }
        }
    }

    // Восстановление пути от финиша (левый нижний угол) к старту
    std::string RouteResult = "";
    int CurrentRow = BoardSize - 1;
    int CurrentCol = 0;

    // Цикл обратного прохода по матрице путей
    while (CurrentRow != 0 || CurrentCol != BoardSize - 1)
    {
        RouteResult += PathSteps[CurrentRow][CurrentCol];
        if (PathSteps[CurrentRow][CurrentCol] == 'D')
        {
            CurrentRow--;
        }
        else
        {
            CurrentCol++;
        }
    }

    // FIX_ME: reverse(route.begin(), route.end()) — использование без std::
    std::reverse(RouteResult.begin(), RouteResult.end());

    // Вывод результата
    if (KingOutput.is_open())
    {
        KingOutput << MinDistances[BoardSize - 1][0] << std::endl;
        KingOutput << RouteResult << std::endl;
        KingOutput.close();
    }
}
