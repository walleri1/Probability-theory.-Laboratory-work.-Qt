#include "corelabatwo.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>

// Конструктор по-умолчанию
CoreLabaTwo::CoreLabaTwo()
    : countGenerateNumber(5),
      maxPowerBeginMoment(1),
      maxPowerCentralMoment(2),
      mathematicalExpectation(0.5),
      dispersion(0.08)
{}

// Сеттер количества сгенерированных чисел
void CoreLabaTwo::setCountGenerateNumber(int countGenerateNumber)
{
    this->countGenerateNumber = abs(countGenerateNumber);
}

// Сеттер порядка моментов
void CoreLabaTwo::setBeginAndCentralMomentPower(double maxPowerBeginMoment, double maxPowerCentralMoment)
{
    this->maxPowerBeginMoment = abs(maxPowerBeginMoment);
    this->maxPowerCentralMoment = abs(maxPowerCentralMoment);
}

// Сеттер математического ожидания и десперсии от специального блока
void CoreLabaTwo::setSpecBlock(double mathematicalExpectation, double dispersion)
{
    this->mathematicalExpectation = mathematicalExpectation;
    this->dispersion = dispersion;
}

// Геттер массива относительных частот
std::vector<double> CoreLabaTwo::getVectorRegardingFrequency(int numberAlgoritm) const
{
    switch (numberAlgoritm)
    {
    case 1:
        return this->vectorRegardingFrequencyOneAlgoritmNormally;

    case 2:
        return this->vectorRegardingFrequencyTwoAlgoritmNormally;
    }
}

// Геттер массива накопленных частот
std::vector<double> CoreLabaTwo::getVectorAccumulationFrequency(int numberAlgoritm) const
{
    switch (numberAlgoritm)
    {
    case 1:
        return this->vectorAccumulationFrequencyOneAlgoritmNormally;

    case 2:
        return this->vectorAccumulationFrequencyTwoAlgoritmNormally;
    }
}

// Геттер математического ожидания
double CoreLabaTwo::getMathematicalExpectation(int numberAlgoritm) const
{
    switch (numberAlgoritm)
    {
    case 1:
        return this->mathematicalExpectationOneAlgoritmNormally;

    case 2:
        return this->mathematicalExpectationTwoAlgoritmNormally;
    }
}

// Геттер дисперсии
double CoreLabaTwo::getDispersion(int numberAlgoritm) const
{
    switch (numberAlgoritm)
    {
    case 1:
        return this->dispersionOneAlgoritmNormally;

    case 2:
        return this->dispersionTwoAlgoritmNormally;
    }
}

// Геттер начальных моментов
std::vector<double> CoreLabaTwo::getBeginMoment(int numberAlgoritm) const
{
    switch (numberAlgoritm)
    {
    case 1:
        return this->vectorBeginMomentOneAlgoritmNormally;

    case 2:
        return this->vectorBeginMomentTwoAlgoritmNormally;
    }
}

// Геттер центральных моментов
std::vector<double> CoreLabaTwo::getCentralMoment(int numberAlgoritm) const
{
    switch (numberAlgoritm)
    {
    case 1:
        return this->vectorCentralMomentOneAlgoritmNormally;

    case 2:
        return this->vectorCentralMomentTwoAlgoritmNormally;
    }
}

// Геттер вектора случаный сгенерированных величин
std::vector<double> CoreLabaTwo::getVectorValueGenerate(int numberAlgoritm) const
{
    switch (numberAlgoritm)
    {
    case 1:
        return this->vectorValueGenerateOneAlgoritmNormally;

    case 2:
        return this->vectorValueGenerateTwoAlgoritmNormally;
    }
}

/*
    Начало всех вычислений
*/
void CoreLabaTwo::calculateMain()
{
    // Генерирование чисел равномерного распределения
    generateValueNumberEvenly();

    // Генерирование чисел нормального распределения
    generateValueNumberNormally();

    // Вычисление интервалов
    calculateIntervalHistogram();

    // Вычисление границ диапозонов
    calculateBorderRange();

    // Вычисление частот
    calculateFrequency();

    // Вычисление суммы частот
    calculateSummaFrequency();

    // Вычисление относительных частот
    calculateRegardingFrequency();

    // Вычисление накопленных частот
    calculateAccumulationFrequency();

    // Вычисление математического ожидания
    calculateMathematicalExpectation();

    // Вычисление дисперсии
    calculateDispersion();

    // Вычисление начальных и центральных моментов
    calculateMoment();
}

// Генерирование чисел равномерного распределения
void CoreLabaTwo::generateValueNumberEvenly()
{
    /*
     * Генерирование равномерно распределённых чисел
    */

    // Предворительная очистка массивов
    vectorValueGenerateEvenlyOne.clear();
    vectorValueGenerateEvenlyTwo.clear();

    // Ядро генерации для равномерного распределения (встроенного)
    srand(time(NULL));

    /*
     * Генерация равномерно распределённых чисел аддитивным алгоритмом
    */

    // Генерирование случайных чисел в пределах (0; 1)
    for (size_t i = 0; i < (size_t)countGenerateNumber; i++)
    {
        // Случайное число из раномерного распределения (стандартного)
        double tmpValue(0);

        for (size_t j = 0; j < 8; j++)
        {
            tmpValue += (double)rand() / RAND_MAX;
        }

        vectorValueGenerateEvenlyOne.push_back(tmpValue - (int)tmpValue);
    }

    // Генерирование случайных чисел в пределах (0; 1)
    for (size_t i = 0; i < (size_t)countGenerateNumber; i++)
    {
        // Случайное число из раномерного распределения (стандартного)
        double tmpValue(0);

        for (size_t j = 0; j < 8; j++)
        {
            tmpValue += (double)rand() / RAND_MAX;
        }

        vectorValueGenerateEvenlyTwo.push_back(tmpValue - (int)tmpValue);
    }

    /*
     * Вычисление математического ожидания и дисперсии равномерно распределённых чисел
    */
    /*
        Математическое ожидание
    */
    mathematicalExpectationOneAlgoritmEvenly = mathematicalExpectation;
    mathematicalExpectationTwoAlgoritmEvenly = mathematicalExpectation;

    /*
        Дисперсия
    */
    dispersionOneAlgoritmEvenly = dispersion;
    dispersionTwoAlgoritmEvenly = dispersion;
}

// Генерирование чисел нормального распределения
void CoreLabaTwo::generateValueNumberNormally()
{
    // Предворительная очистка массивов
    vectorValueGenerateOneAlgoritmNormally.clear();
    vectorValueGenerateTwoAlgoritmNormally.clear();

    /*
     * Первый алгоритм
    */

    // Генерирование случайных чисел по нормальному распределению
    for (size_t i = 0; i < (size_t)countGenerateNumber; i++)
    {
        vectorValueGenerateOneAlgoritmNormally.push_back(mathematicalExpectationOneAlgoritmEvenly
        + dispersionOneAlgoritmEvenly * sqrt(-2 * log(vectorValueGenerateEvenlyOne[i]))
                                        * cos(2 * M_PI * vectorValueGenerateEvenlyTwo[i]));
    }

    /*
     * Второй алгоритм
    */

    for (size_t i = 0; i < (size_t)countGenerateNumber; i++)
    {
        vectorValueGenerateTwoAlgoritmNormally.push_back(mathematicalExpectationTwoAlgoritmEvenly
        + dispersionTwoAlgoritmEvenly * sqrt(-2 * log(vectorValueGenerateEvenlyOne[i]))
                                        * sin(2 * M_PI * vectorValueGenerateEvenlyTwo[i]));
    }
}

// Вычисление интервалов
void CoreLabaTwo::calculateIntervalHistogram()
{
    // Максимальное и минимальное значение для случайных чисел
    double maxOneAlgoritmNormally(vectorValueGenerateOneAlgoritmNormally[0]),
            minOneAlgoritmNormally(vectorValueGenerateOneAlgoritmNormally[0]),
            maxTwoAlgoritmNormally(vectorValueGenerateTwoAlgoritmNormally[0]),
            minTwoAlgoritmNormally(vectorValueGenerateTwoAlgoritmNormally[0]);

    // Поиск минимальных и максимальных значений
    for (size_t i = 1; i < (size_t)countGenerateNumber; i++)
    {
        if (maxOneAlgoritmNormally < vectorValueGenerateOneAlgoritmNormally[i])
            maxOneAlgoritmNormally = vectorValueGenerateOneAlgoritmNormally[i];

        if (minOneAlgoritmNormally > vectorValueGenerateOneAlgoritmNormally[i])
            minOneAlgoritmNormally = vectorValueGenerateOneAlgoritmNormally[i];

        if (maxTwoAlgoritmNormally < vectorValueGenerateTwoAlgoritmNormally[i])
            maxTwoAlgoritmNormally = vectorValueGenerateTwoAlgoritmNormally[i];

        if (minTwoAlgoritmNormally > vectorValueGenerateTwoAlgoritmNormally[i])
            minTwoAlgoritmNormally = vectorValueGenerateTwoAlgoritmNormally[i];
    }

    // Вычисление интервалов
    intervalHistogramOneAlgoritmNormally = (maxOneAlgoritmNormally - minOneAlgoritmNormally)
            / floor(1 + 3.322 * log10(countGenerateNumber));

    intervalHistogramTwoAlgoritmNormally = (maxTwoAlgoritmNormally - minTwoAlgoritmNormally)
            / floor(1 + 3.322 * log10(countGenerateNumber));

    // Запоминаем минимальные и максимальные значения
    this->minOneAlgoritmNormally = minOneAlgoritmNormally;
    this->maxOneAlgoritmNormally = maxOneAlgoritmNormally;
    this->minTwoAlgoritmNormally = minTwoAlgoritmNormally;
    this->maxTwoAlgoritmNormally = maxTwoAlgoritmNormally;
}

// Вычисление границ диапозонов
void CoreLabaTwo::calculateBorderRange()
{
    // Очистка векторов
    vectorBorderRangeOneAlgoritmNormally.clear();
    vectorBorderRangeTwoAlgoritmNormally.clear();

    // Нулевое значение
    vectorBorderRangeOneAlgoritmNormally.push_back(minOneAlgoritmNormally);
    vectorBorderRangeTwoAlgoritmNormally.push_back(minTwoAlgoritmNormally);

    double tmpValueBordeRangeOneAlgoritmNormally = minOneAlgoritmNormally + intervalHistogramOneAlgoritmNormally;
    double tmpValueBordeRangeTwoAlgoritmNormally = minTwoAlgoritmNormally + intervalHistogramTwoAlgoritmNormally;

    for (size_t i = 1; maxOneAlgoritmNormally - tmpValueBordeRangeOneAlgoritmNormally > 0; i++)
    {
        vectorBorderRangeOneAlgoritmNormally.push_back(tmpValueBordeRangeOneAlgoritmNormally);

        tmpValueBordeRangeOneAlgoritmNormally = vectorBorderRangeOneAlgoritmNormally[i] + intervalHistogramOneAlgoritmNormally;
    }

    for (size_t i = 1; maxTwoAlgoritmNormally - tmpValueBordeRangeTwoAlgoritmNormally > 0; i++)
    {
        vectorBorderRangeTwoAlgoritmNormally.push_back(tmpValueBordeRangeTwoAlgoritmNormally);

        tmpValueBordeRangeTwoAlgoritmNormally = vectorBorderRangeTwoAlgoritmNormally[i] + intervalHistogramTwoAlgoritmNormally;
    }
}

// Вычисление частот
void CoreLabaTwo::calculateFrequency()
{
    // Очистка массивов
    vectorFrequencyOneAlgoritmNormally.assign(vectorBorderRangeOneAlgoritmNormally.size() + 1, 0);
    vectorFrequencyTwoAlgoritmNormally.assign(vectorBorderRangeTwoAlgoritmNormally.size() + 1, 0);

    // Вычисления частот
    for (size_t i = 0; i < countGenerateNumber; i++)
    {
        for (size_t j = 1, maxJ = vectorBorderRangeOneAlgoritmNormally.size(); j < maxJ; j++)
        {
            if (vectorValueGenerateOneAlgoritmNormally[i] >= vectorBorderRangeOneAlgoritmNormally[j - 1]
                    && vectorValueGenerateOneAlgoritmNormally[i] < vectorBorderRangeOneAlgoritmNormally[j])
                vectorFrequencyOneAlgoritmNormally[j - 1]++;
        }

        for (size_t j = 1, maxJ = vectorBorderRangeTwoAlgoritmNormally.size(); j < maxJ; j++)
        {
            if (vectorValueGenerateTwoAlgoritmNormally[i] >= vectorBorderRangeTwoAlgoritmNormally[j - 1]
                    && vectorValueGenerateTwoAlgoritmNormally[i] < vectorBorderRangeTwoAlgoritmNormally[j])
                vectorFrequencyTwoAlgoritmNormally[j - 1]++;
        }
    }
}

// Вычисление суммы частот
void CoreLabaTwo::calculateSummaFrequency()
{
    // Обнуление сумм
    summaFrequencyOneAlgoritmNormally = 0;
    summaFrequencyTwoAlgoritmNormally = 0;

    // Суммирование
    for (size_t i = 0, maxI = vectorFrequencyOneAlgoritmNormally.size(); i < maxI; i++)
    {
        summaFrequencyOneAlgoritmNormally += vectorFrequencyOneAlgoritmNormally[i];
    }

    for (size_t i = 0, maxI = vectorFrequencyTwoAlgoritmNormally.size(); i < maxI; i++)
    {
        summaFrequencyTwoAlgoritmNormally += vectorFrequencyTwoAlgoritmNormally[i];
    }
}

// Вычисление относительных частот
void CoreLabaTwo::calculateRegardingFrequency()
{
    // Очистка относительных частот
    vectorRegardingFrequencyOneAlgoritmNormally.clear();
    vectorRegardingFrequencyTwoAlgoritmNormally.clear();

    // Вычисление относительных частот
    for (size_t i = 0, maxI = vectorFrequencyOneAlgoritmNormally.size(); i < maxI; i++)
    {
        vectorRegardingFrequencyOneAlgoritmNormally.push_back(vectorFrequencyOneAlgoritmNormally[i]
                                                   / summaFrequencyOneAlgoritmNormally);
    }

    for (size_t i = 0, maxI = vectorFrequencyTwoAlgoritmNormally.size(); i < maxI; i++)
    {
        vectorRegardingFrequencyTwoAlgoritmNormally.push_back(vectorFrequencyTwoAlgoritmNormally[i]
                                                   / summaFrequencyTwoAlgoritmNormally);
    }
}

// Вычисление накопленных частот
void CoreLabaTwo::calculateAccumulationFrequency()
{
    // Очистка накопленных частот
    vectorAccumulationFrequencyOneAlgoritmNormally.clear();
    vectorAccumulationFrequencyTwoAlgoritmNormally.clear();

    for (size_t i = 0, maxI = vectorRegardingFrequencyOneAlgoritmNormally.size(); i < maxI; i++)
    {
        if (i == 0)
        {
            vectorAccumulationFrequencyOneAlgoritmNormally.push_back(vectorRegardingFrequencyOneAlgoritmNormally[i]);
        }
        else
        {
            vectorAccumulationFrequencyOneAlgoritmNormally.push_back(vectorRegardingFrequencyOneAlgoritmNormally[i] + vectorAccumulationFrequencyOneAlgoritmNormally[i - 1]);
        }
    }

    for (size_t i = 0, maxI = vectorRegardingFrequencyTwoAlgoritmNormally.size(); i < maxI; i++)
    {
        if (i == 0)
        {
            vectorAccumulationFrequencyTwoAlgoritmNormally.push_back(vectorRegardingFrequencyTwoAlgoritmNormally[i]);
        }
        else
        {
            vectorAccumulationFrequencyTwoAlgoritmNormally.push_back(vectorRegardingFrequencyTwoAlgoritmNormally[i] + vectorAccumulationFrequencyTwoAlgoritmNormally[i - 1]);
        }
    }
}

// Вычисление математического ожидания
void CoreLabaTwo::calculateMathematicalExpectation()
{
    // Обнуление математического ожидания
    mathematicalExpectationOneAlgoritmNormally = 0;
    mathematicalExpectationTwoAlgoritmNormally = 0;

    // Вычисление математического ожидания
    for (size_t i = 0; i < (size_t)countGenerateNumber; i++)
    {
        mathematicalExpectationOneAlgoritmNormally += vectorValueGenerateOneAlgoritmNormally[i];
        mathematicalExpectationTwoAlgoritmNormally += vectorValueGenerateTwoAlgoritmNormally[i];
    }

    mathematicalExpectationOneAlgoritmNormally /= countGenerateNumber;
    mathematicalExpectationTwoAlgoritmNormally /= countGenerateNumber;
}

// Вычисление дисперсии
void CoreLabaTwo::calculateDispersion()
{
    // Обнуление дисперсии
     dispersionOneAlgoritmNormally = 0;
     dispersionTwoAlgoritmNormally = 0;

     for (size_t i = 0; i < (size_t)countGenerateNumber; i++)
        dispersionOneAlgoritmNormally += (vectorValueGenerateOneAlgoritmNormally[i] - mathematicalExpectationOneAlgoritmNormally)
                * (vectorValueGenerateOneAlgoritmNormally[i] - mathematicalExpectationOneAlgoritmNormally);

     dispersionOneAlgoritmNormally /= countGenerateNumber - 1;

     for (size_t i = 0; i < (size_t)countGenerateNumber; i++)
        dispersionTwoAlgoritmNormally += (vectorValueGenerateTwoAlgoritmNormally[i] - mathematicalExpectationTwoAlgoritmNormally)
                * (vectorValueGenerateTwoAlgoritmNormally[i] - mathematicalExpectationTwoAlgoritmNormally);

     dispersionTwoAlgoritmNormally /= countGenerateNumber - 1;
}

// Вычисление начальных и центральных моментов
void CoreLabaTwo::calculateMoment()
{
    /*
     * Начальные моменты
    */
    // Выделение памяти и обнуление
    vectorBeginMomentOneAlgoritmNormally.assign(maxPowerBeginMoment, 0);
    vectorBeginMomentTwoAlgoritmNormally.assign(maxPowerBeginMoment, 0);

    // Первая степень начального момента (она равна математическому ожиданию)
    vectorBeginMomentOneAlgoritmNormally[0] = mathematicalExpectationOneAlgoritmNormally;
    vectorBeginMomentTwoAlgoritmNormally[0] = mathematicalExpectationTwoAlgoritmNormally;

    // Все остальные степени начальных моментов

    // Вероятности
    std::vector<double> vectorProbabilityOneAlgoritmNormally(vectorFrequencyOneAlgoritmNormally.size()),
            vectorProbabilityTwoAlgoritmNormally(vectorFrequencyTwoAlgoritmNormally.size());

    for (size_t i = 0; i < vectorFrequencyOneAlgoritmNormally.size(); i++)
        vectorProbabilityOneAlgoritmNormally[i] = vectorFrequencyOneAlgoritmNormally[i] / countGenerateNumber;

    for (size_t i = 0; i < vectorFrequencyTwoAlgoritmNormally.size(); i++)
        vectorProbabilityTwoAlgoritmNormally[i] = vectorFrequencyTwoAlgoritmNormally[i] / countGenerateNumber;

    // Начнём считать остальные степени начальных моментов, если они конечно есть
    for (size_t i = 2; i <= maxPowerBeginMoment; i++)
    {
        for (size_t j = 0, jBorder = 1; j < vectorProbabilityOneAlgoritmNormally.size(); j++, jBorder++)
            for (size_t k = 0; k < (size_t)countGenerateNumber; k++)
                if (vectorValueGenerateOneAlgoritmNormally[k] >= vectorBorderRangeOneAlgoritmNormally[jBorder - 1]
                    && vectorValueGenerateOneAlgoritmNormally[k] < vectorBorderRangeOneAlgoritmNormally[jBorder])
                    vectorBeginMomentOneAlgoritmNormally[i - 1] += vectorProbabilityOneAlgoritmNormally[j]
                            * pow(vectorValueGenerateOneAlgoritmNormally[k], i);

        for (size_t j = 0, jBorder = 1; j < vectorProbabilityTwoAlgoritmNormally.size(); j++, jBorder++)
            for (size_t k = 0; k < (size_t)countGenerateNumber; k++)
                if (vectorValueGenerateTwoAlgoritmNormally[k] >= vectorBorderRangeTwoAlgoritmNormally[jBorder - 1]
                    && vectorValueGenerateTwoAlgoritmNormally[k] < vectorBorderRangeTwoAlgoritmNormally[jBorder])
                    vectorBeginMomentTwoAlgoritmNormally[i - 1] += vectorProbabilityTwoAlgoritmNormally[j]
                            * pow(vectorValueGenerateTwoAlgoritmNormally[k], i);
    }

    /*
     * Центральные моменты
    */
    // Выделение памяти и обнуление
    vectorCentralMomentOneAlgoritmNormally.assign(maxPowerCentralMoment, 0);
    vectorCentralMomentTwoAlgoritmNormally.assign(maxPowerCentralMoment, 0);

    // Центральные моменты второй степени
    vectorCentralMomentOneAlgoritmNormally[1] = dispersionOneAlgoritmNormally;
    vectorCentralMomentTwoAlgoritmNormally[1] = dispersionTwoAlgoritmNormally;

    // Вычисление остальных центральных моментов, если они есть
    for (size_t i = 3; i <= maxPowerCentralMoment; i++)
    {
        for (size_t j = 0, jBorder = 1; j < vectorProbabilityOneAlgoritmNormally.size(); j++, jBorder++)
            for (size_t k = 0; k < (size_t)countGenerateNumber; k++)
                if (vectorValueGenerateOneAlgoritmNormally[k] >= vectorBorderRangeOneAlgoritmNormally[jBorder - 1]
                    && vectorValueGenerateOneAlgoritmNormally[k] < vectorBorderRangeOneAlgoritmNormally[jBorder])
                    vectorCentralMomentOneAlgoritmNormally[i - 1] += vectorProbabilityOneAlgoritmNormally[j]
                            * pow(vectorValueGenerateOneAlgoritmNormally[k] - mathematicalExpectationOneAlgoritmNormally, i);

        for (size_t j = 0, jBorder = 1; j < vectorProbabilityTwoAlgoritmNormally.size(); j++, jBorder++)
            for (size_t k = 0; k < (size_t)countGenerateNumber; k++)
                if (vectorValueGenerateTwoAlgoritmNormally[k] >= vectorBorderRangeTwoAlgoritmNormally[jBorder - 1]
                    && vectorValueGenerateTwoAlgoritmNormally[k] < vectorBorderRangeTwoAlgoritmNormally[jBorder])
                    vectorBeginMomentTwoAlgoritmNormally[i - 1] += vectorProbabilityTwoAlgoritmNormally[j]
                            * pow(vectorValueGenerateTwoAlgoritmNormally[k] - mathematicalExpectationTwoAlgoritmNormally, i);
    }
}
