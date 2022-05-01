#include "corelabafive.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>

// Конструктор по-умолчанию
CoreLabaFive::CoreLabaFive()
    : countGenerateNumber(5),
      maxPowerBeginMoment(1),
      maxPowerCentralMoment(2),
      mathematicalExpectationExponential(0),
      dispersionExponential(0)
{}

// Сеттер количества сгенерированных чисел
void CoreLabaFive::setCountGenerateNumber(int countGenerateNumber)
{
    this->countGenerateNumber = abs(countGenerateNumber);
}

// Сеттер порядка моментов
void CoreLabaFive::setBeginAndCentralMomentPower(double maxPowerBeginMoment, double maxPowerCentralMoment)
{
    this->maxPowerBeginMoment = abs(maxPowerBeginMoment);
    this->maxPowerCentralMoment = abs(maxPowerCentralMoment);
}

// Сеттер параметра лямбды для показательного распределения
void CoreLabaFive::setLambda(double lambda)
{
    this->lambda = abs(lambda);
}

// Геттер массива относительных частот
std::vector<double> CoreLabaFive::getVectorRegardingFrequency() const
{
    return this->vectorRegardingFrequencyExponential;
}

// Геттер массива накопленных частот
std::vector<double> CoreLabaFive::getVectorAccumulationFrequency() const
{
    return this->vectorAccumulationFrequencyExponential;
}

// Геттер математического ожидания
double CoreLabaFive::getMathematicalExpectation() const
{
    return this->mathematicalExpectationExponential;
}

// Геттер дисперсии
double CoreLabaFive::getDispersion() const
{
    return this->dispersionExponential;
}

// Геттер начальных моментов
std::vector<double> CoreLabaFive::getBeginMoment() const
{
    return this->vectorBeginMomentExponential;
}

// Геттер центральных моментов
std::vector<double> CoreLabaFive::getCentralMoment() const
{
    return this->vectorCentralMomentExponential;
}

// Геттер вектора случаный сгенерированных величин
std::vector<double> CoreLabaFive::getVectorValueGenerate() const
{
    return this->vectorValueGenerateExponential;
}

// Начало всех вычислений
void CoreLabaFive::calculateMain()
{
    // Генерирование чисел равномерного распределения
    generateValueNumberEvenly();

    // Генерирование чисел нормального распределения
    generateValueNumberExponential();

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
void CoreLabaFive::generateValueNumberEvenly()
{
    /*
     * Генерирование равномерно распределённых чисел
    */

    // Предворительная очистка массивов
    vectorValueGenerateEvenly.clear();

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

        vectorValueGenerateEvenly.push_back(tmpValue - (int)tmpValue);
    }
}

// Генерирование чисел показательного распределения
void CoreLabaFive::generateValueNumberExponential()
{
    // Предворительная очистка массивов
    vectorValueGenerateExponential.clear();

    // Генерирование случайных чисел по нормальному распределению
    for (size_t i = 0; i < (size_t)countGenerateNumber; i++)
    {
        vectorValueGenerateExponential.push_back(-1/lambda
                        * log(vectorValueGenerateEvenly[i]));
    }
}

// Вычисление интервалов
void CoreLabaFive::calculateIntervalHistogram()
{
    // Максимальное и минимальное значение для случайных чисел
    double maxExponential(vectorValueGenerateExponential[0]),
            minExponential(vectorValueGenerateExponential[0]);

    // Поиск минимальных и максимальных значений
    for (size_t i = 1; i < (size_t)countGenerateNumber; i++)
    {
        if (maxExponential < vectorValueGenerateExponential[i])
            maxExponential = vectorValueGenerateExponential[i];

        if (minExponential > vectorValueGenerateExponential[i])
            minExponential = vectorValueGenerateExponential[i];
    }

    // Вычисление интервалов
    intervalHistogramExponential = (maxExponential - minExponential)
            / floor(1 + 3.322 * log10(countGenerateNumber));

    // Запоминаем минимальные и максимальные значения
    this->minExponential = minExponential;
    this->maxExponential = maxExponential;
}

// Вычисление границ диапозонов
void CoreLabaFive::calculateBorderRange()
{
    // Очистка векторов
    vectorBorderRangeExponential.clear();

    // Нулевое значение
    vectorBorderRangeExponential.push_back(minExponential);

    double tmpValueBordeRangeExponential = minExponential + intervalHistogramExponential;

    for (size_t i = 1; maxExponential - tmpValueBordeRangeExponential > 0; i++)
    {
        vectorBorderRangeExponential.push_back(tmpValueBordeRangeExponential);

        tmpValueBordeRangeExponential = vectorBorderRangeExponential[i] + intervalHistogramExponential;
    }
}

// Вычисление частот
void CoreLabaFive::calculateFrequency()
{
    // Очистка массивов
    vectorFrequencyExponential.assign(vectorBorderRangeExponential.size() + 1, 0);

    // Вычисления частот
    for (size_t i = 0; i < (size_t)countGenerateNumber; i++)
    {
        for (size_t j = 1, maxJ = vectorBorderRangeExponential.size(); j < maxJ; j++)
        {
            if (vectorValueGenerateExponential[i] >= vectorBorderRangeExponential[j - 1]
                    && vectorValueGenerateExponential[i] < vectorBorderRangeExponential[j])
                vectorFrequencyExponential[j - 1]++;
        }
    }
}

// Вычисление суммы частот
void CoreLabaFive::calculateSummaFrequency()
{
    // Обнуление сумм
    summaFrequencyExponential = 0;

    // Суммирование
    for (size_t i = 0, maxI = vectorFrequencyExponential.size(); i < maxI; i++)
    {
        summaFrequencyExponential += vectorFrequencyExponential[i];
    }
}

// Вычисление относительных частот
void CoreLabaFive::calculateRegardingFrequency()
{
    // Очистка относительных частот
    vectorRegardingFrequencyExponential.clear();

    // Вычисление относительных частот
    for (size_t i = 0, maxI = vectorFrequencyExponential.size(); i < maxI; i++)
    {
        vectorRegardingFrequencyExponential.push_back(vectorFrequencyExponential[i]
                                                   / summaFrequencyExponential);
    }
}

// Вычисление накопленных частот
void CoreLabaFive::calculateAccumulationFrequency()
{
    // Очистка накопленных частот
    vectorAccumulationFrequencyExponential.clear();

    for (size_t i = 0, maxI = vectorRegardingFrequencyExponential.size(); i < maxI; i++)
    {
        if (i == 0)
        {
            vectorAccumulationFrequencyExponential.push_back(vectorRegardingFrequencyExponential[i]);
        }
        else
        {
            vectorAccumulationFrequencyExponential.push_back(vectorRegardingFrequencyExponential[i] + vectorAccumulationFrequencyExponential[i - 1]);
        }
    }
}

// Вычисление математического ожидания
void CoreLabaFive::calculateMathematicalExpectation()
{
    // Обнуление математического ожидания
    mathematicalExpectationExponential = 0;

    // Вычисление математического ожидания
    for (size_t i = 0; i < (size_t)countGenerateNumber; i++)
    {
        mathematicalExpectationExponential += vectorValueGenerateExponential[i];
    }

    mathematicalExpectationExponential /= countGenerateNumber;
}

// Вычисление дисперсии
void CoreLabaFive::calculateDispersion()
{
    // Обнуление дисперсии
     dispersionExponential = 0;

     for (size_t i = 0; i < (size_t)countGenerateNumber; i++)
        dispersionExponential += (vectorValueGenerateExponential[i] - mathematicalExpectationExponential)
                * (vectorValueGenerateExponential[i] - mathematicalExpectationExponential);

     dispersionExponential /= countGenerateNumber - 1;
}

// Вычисление начальных и центральных моментов
void CoreLabaFive::calculateMoment()
{
    /*
     * Начальные моменты
    */
    // Выделение памяти и обнуление
    vectorBeginMomentExponential.assign(maxPowerBeginMoment, 0);

    // Первая степень начального момента (она равна математическому ожиданию)
    vectorBeginMomentExponential[0] = mathematicalExpectationExponential;

    // Все остальные степени начальных моментов

    // Вероятности
    std::vector<double> vectorProbabilityExponential(vectorFrequencyExponential.size());

    for (size_t i = 0; i < (size_t)vectorFrequencyExponential.size(); i++)
        vectorProbabilityExponential[i] = vectorFrequencyExponential[i] / countGenerateNumber;

    // Начнём считать остальные степени начальных моментов, если они конечно есть
    for (size_t i = 2; i <= maxPowerBeginMoment; i++)
    {
        for (size_t j = 0, jBorder = 1; j < vectorProbabilityExponential.size(); j++, jBorder++)
            for (size_t k = 0; k < (size_t)countGenerateNumber; k++)
                if (vectorValueGenerateExponential[k] >= vectorBorderRangeExponential[jBorder - 1]
                    && vectorValueGenerateExponential[k] < vectorBorderRangeExponential[jBorder])
                    vectorBeginMomentExponential[i - 1] += vectorProbabilityExponential[j]
                            * pow(vectorValueGenerateExponential[k], i);
    }

    /*
     * Центральные моменты
    */
    // Выделение памяти и обнуление
    vectorCentralMomentExponential.assign(maxPowerCentralMoment, 0);

    // Центральные моменты второй степени
    vectorCentralMomentExponential[1] = dispersionExponential;

    // Вычисление остальных центральных моментов, если они есть
    for (size_t i = 3; i <= maxPowerCentralMoment; i++)
    {
        for (size_t j = 0, jBorder = 1; j < vectorProbabilityExponential.size(); j++, jBorder++)
            for (size_t k = 0; k < (size_t)countGenerateNumber; k++)
                if (vectorValueGenerateExponential[k] >= vectorBorderRangeExponential[jBorder - 1]
                    && vectorValueGenerateExponential[k] < vectorBorderRangeExponential[jBorder])
                    vectorCentralMomentExponential[i - 1] += vectorProbabilityExponential[j]
                            * pow(vectorValueGenerateExponential[k] - mathematicalExpectationExponential, i);
    }
}
