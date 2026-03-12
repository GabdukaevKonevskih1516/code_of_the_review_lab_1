#include "Header.h"

bool IsCountValid(int InCount)
{
    return InCount > 0;
}

bool IsWeightValid(int InWeight)
{
    return InWeight >= 0;
}

void SolveArchaeologistTask()
{
    // FIX_ME: использование коротких имен (stream), отсутствие std::, отсутствие проверки открытия
    // ifstream stream; stream.open("a.txt");
    std::ifstream ArtifactInput("A.txt");

    if (!ArtifactInput.is_open())
    {
        std::cout << "Ошибка: Не удалось открыть файл A.txt" << std::endl;
        return;
    }

    // FIX_ME: некорректные имена (n, b), отсутствие проверок типа данных
    // int n, b; stream >> n >> b;
    int NumArtifacts = 0;
    int MaxWeightLimit = 0;

    if (!(ArtifactInput >> NumArtifacts >> MaxWeightLimit) || !IsCountValid(NumArtifacts))
    {
        std::cout << "Ошибка: Некорректные данные заголовка (N или B)" << std::endl;
        return;
    }

    // FIX_ME: использование snake_case, отсутствие префиксов, создание векторов без учета std::
    // vector <int> weight_vector(n+1);
    std::vector<int> ArtifactWeights(NumArtifacts);
    std::vector<int> ArtifactVolumes(NumArtifacts);

    // Считывание весов из второй строки
    for (int i = 0; i < NumArtifacts; ++i)
    {
        if (!(ArtifactInput >> ArtifactWeights[i]) || !IsWeightValid(ArtifactWeights[i]))
        {
            std::cout << "Ошибка: Некорректный вес артефакта " << i + 1 << std::endl;
            return;
        }
    }

    // Считывание объемов из третьей строки
    for (int i = 0; i < NumArtifacts; ++i)
    {
        if (!(ArtifactInput >> ArtifactVolumes[i]))
        {
            std::cout << "Ошибка: Некорректный объем артефакта " << i + 1 << std::endl;
            return;
        }
    }
    ArtifactInput.close();

    // Подготовка таблиц динамического программирования
    // DPCount[w] — макс. количество предметов для веса w
    // DPSumVolume[w] — суммарный объем для веса w
    std::vector<int> DPCount(MaxWeightLimit + 1, -1);
    std::vector<int> DPSumVolume(MaxWeightLimit + 1, 0);

    // Матрица Keep[i][w] — был ли взят i-й предмет для достижения веса w
    std::vector<std::vector<bool>> Keep(NumArtifacts, std::vector<bool>(MaxWeightLimit + 1, false));

    DPCount[0] = 0;

    // FIX_ME: старая логика main_vector[i][j] = main_vector[i-1][j] + weight_vector[i] 
    // не учитывала приоритет на максимальное количество предметов.


    // Основной алгоритм: классический рюкзак 0/1 с приоритетом на количество предметов
    for (int i = 0; i < NumArtifacts; ++i)
    {
        for (int w = MaxWeightLimit; w >= ArtifactWeights[i]; --w)
        {
            if (DPCount[w - ArtifactWeights[i]] != -1)
            {
                int NewCount = DPCount[w - ArtifactWeights[i]] + 1;
                int NewVolume = DPSumVolume[w - ArtifactWeights[i]] + ArtifactVolumes[i];

                // Если новый набор дает больше предметов (или столько же — по условию решение единственно)
                if (NewCount > DPCount[w])
                {
                    DPCount[w] = NewCount;
                    DPSumVolume[w] = NewVolume;
                    Keep[i][w] = true;
                }
            }
        }
    }

    // Поиск наиболее близкого к B веса, который удалось собрать
    int BestWeight = -1;
    for (int w = MaxWeightLimit; w >= 0; --w)
    {
        if (DPCount[w] != -1)
        {
            BestWeight = w;
            break;
        }
    }

    if (BestWeight == -1)
    {
        std::cout << "Решение не найдено." << std::endl;
        return;
    }

    // Вывод итоговых характеристик
    std::cout << "Вес: " << BestWeight << " Объем: " << DPSumVolume[BestWeight] << std::endl;
    std::cout << "Номера артефактов: ";

    // FIX_ME: рекурсия find_numbers заменена безопасным итеративным циклом
    // FIX_ME: исправлена ошибка входа в условия 
    int CurrentWeight = BestWeight;
    for (int i = NumArtifacts - 1; i >= 0; --i)
    {
        if (Keep[i][CurrentWeight])
        {
            std::cout << i + 1 << " "; // Вывод порядкового номера (1-based)
            CurrentWeight -= ArtifactWeights[i];
        }
    }
    std::cout << std::endl;
}
