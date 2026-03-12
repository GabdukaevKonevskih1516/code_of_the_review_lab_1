#include "Header.h"

bool IsInputValid(int InK, int InN)
{
    return (InK >= 2 && InK <= 10) &&
        (InN > 1 && InN < 20) &&
        (InN + InK < 26);
}

void SolveKNumericalTask()
{
    // FIX_ME: Использование std::cin напрямую без проверки потока и использование простых имен
    // int k, n; cin >> k >> n;
    int BaseK = 0;
    int LengthN = 0;

    std::cout << "Введите K (2<=K<=10) : ";
    if (!(std::cin >> BaseK)) return;

    std::cout << "Введите N (1<N<20, N+K<26) : ";
    if (!(std::cin >> LengthN)) return;

    if (!IsInputValid(BaseK, LengthN))
    {
        std::cout << "Ошибка: Введенные данные не соответствуют ограничениям." << std::endl;
        return;
    }

    // Состояния динамического программирования:
    // NonZeroLast: Числа длины i, не заканчивающиеся на 0, без двух нулей подряд.
    // OneZeroLast: Числа длины i, заканчивающиеся ровно на один 0, без двух нулей подряд.
    // TwoZerosAny: Числа длины i, которые уже содержат два и более нулей подряд.
    double NonZeroLast = BaseK - 1;
    double OneZeroLast = 0;
    double TwoZerosAny = 0;

    // FIX_ME: В оригинальном коде была путаница в инициализации (oz = 1), что логически неверно 
    // для первого разряда (первая цифра не может быть нулем). Исправлено.
    /*
    nz = k - 1;
    oz = 1;
    tz = 0;
    */

    // Инициализация для первого разряда (длина 1):
    // Цифра не может быть 0, значит есть (BaseK-1) вариантов для NonZeroLast.
    // OneZeroLast и TwoZerosAny равны 0.



    // Цикл вычисления количества чисел для длины от 2 до N
    for (int i = 2; i <= LengthN; ++i)
    {
        // Сохраняем значения предыдущего шага
        double PrevNonZero = NonZeroLast;
        double PrevOneZero = OneZeroLast;
        double PrevTwoZeros = TwoZerosAny;

        // Чтобы число НЕ закончилось на 0, к любому валидному числу (без 00) приписываем любую цифру, кроме 0.
        NonZeroLast = (PrevNonZero + PrevOneZero) * (BaseK - 1);

        // Чтобы число закончилось ровно на один 0, к числу, не заканчивающемуся на 0, приписываем 0.
        OneZeroLast = PrevNonZero;

        // Если число уже содержит 00, к нему можно приписать любую из K цифр.
        // Также к числу, заканчивающемуся на один 0, приписываем еще один 0.
        TwoZerosAny = (PrevTwoZeros * BaseK) + PrevOneZero;
    }

    // FIX_ME: Использование fixed без указания точности и отсутствие std::
    // cout << "Числа с двумя и более подряд идущими нулями: " << fixed << tz << "\n";
    std::cout << std::fixed << std::setprecision(0);
    std::cout << "Числа без двух подряд идущих нулей: " << (NonZeroLast + OneZeroLast) << std::endl;
    std::cout << "Числа с двумя и более подряд идущими нулями: " << TwoZerosAny << std::endl;
}
