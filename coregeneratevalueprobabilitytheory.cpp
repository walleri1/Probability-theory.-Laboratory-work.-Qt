#include "coregeneratevalueprobabilitytheory.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>

// Конструктор по-умолчанию
CoreGenerateValueProbabilityTheory::CoreGenerateValueProbabilityTheory()
    : countGenerateNumber(100), begin(0), end(1),
      valueA(171), valueB(177), valueC(2), valueD(30269), maxPowerBeginMoment(1), maxPowerCentralMoment(2) {}

// Сеттер величин A,B,C,D для усовершенствованного конгурентного алгоритма
void CoreGenerateValueProbabilityTheory::setValueABCD(int valueA, int valueB, int valueC, int valueD)
{
    this->valueA = valueA;
    this->valueB = valueB;
    this->valueC = valueC;
    this->valueD = valueD;
}

// Сеттер количества сгенерированных чисел
void CoreGenerateValueProbabilityTheory::setCountGenerateNumber(int countGenerateNumber)
{
    this->countGenerateNumber = abs(countGenerateNumber);
}

// Сеттер начала диапозона для генерации чисел
void CoreGenerateValueProbabilityTheory::setBegin(double begin)
{
    this->begin = begin;
}

// Сеттер конца диапозона для генерации чисел
void CoreGenerateValueProbabilityTheory::setEnd(double end)
{
    this->end = end;
}

// Сеттер порядка моментов
void CoreGenerateValueProbabilityTheory::setBeginAndCentralMomentPower(double maxPowerBeginMoment, double maxPowerCentralMoment)
{
    this->maxPowerBeginMoment = abs(maxPowerBeginMoment);
    this->maxPowerCentralMoment = abs(maxPowerCentralMoment);
}

// Геттер массива относительных частот
std::vector<double> CoreGenerateValueProbabilityTheory::getVectorRegardingFrequency(int numberAlgoritm) const
{
    switch (numberAlgoritm)
    {
    case 1:
        return this->vectorRegardingFrequencyAdditive;

    case 2:
        return this->vectorRegardingFrequencyCongruent;

    case 3:
        return this->vectorRegardingFrequencyAdvancedCongruent;
    }
}

// Геттер массива накопленных частот
std::vector<double> CoreGenerateValueProbabilityTheory::getVectorAccumulationFrequency(int numberAlgoritm) const
{
    switch (numberAlgoritm)
    {
    case 1:
        return this->vectorAccumulationFrequencyAdditive;

    case 2:
        return this->vectorAccumulationFrequencyCongruent;

    case 3:
        return this->vectorAccumulationFrequencyAdvancedCongruent;
    }
}

// Геттер математического ожидания
double CoreGenerateValueProbabilityTheory::getMathematicalExpectation(int numberAlgoritm) const
{
    switch (numberAlgoritm)
    {
    case 1:
        return this->mathematicalExpectationAdditive;

    case 2:
        return this->mathematicalExpectationCongruent;

    case 3:
        return this->mathematicalExpectationAdvancedCongruent;
    }

    return 0;
}

// Геттер дисперсии
double CoreGenerateValueProbabilityTheory::getDispersion(int numberAlgoritm) const
{
    switch (numberAlgoritm)
    {
    case 1:
        return this->dispersionAdditive;

    case 2:
        return this->dispersionCongruent;

    case 3:
        return this->dispersionAdvancedCongruent;
    }

    return 0;
}

// Геттер начальных моментов
std::vector<double> CoreGenerateValueProbabilityTheory::getBeginMoment(int numberAlgoritm) const
{
    switch (numberAlgoritm)
    {
    case 1:
        return this->vectorBeginMomentAdditive;

    case 2:
        return this->vectorBeginMomentCongruent;

    case 3:
        return this->vectorBeginMomentAdvancedCongruent;
    }
}

// Геттер центральных моментов
std::vector<double> CoreGenerateValueProbabilityTheory::getCentralMoment(int numberAlgoritm) const
{
    switch (numberAlgoritm)
    {
    case 1:
        return this->vectorCentralMomentAdditive;

    case 2:
        return this->vectorCentralMomentCongruent;

    case 3:
        return this->vectorCentralMomentAdvancedCongruent;
    }
}

// Геттер вектора случаный сгенерированных величин
std::vector<double> CoreGenerateValueProbabilityTheory::getVectorValueGenerate(int numberAlgoritm) const
{
    switch (numberAlgoritm)
    {
    case 1:
        return this->vectorValueGenerateAdditive;

    case 2:
        return this->vectorValueGenerateCongruent;

    case 3:
        return this->vectorValueGenerateAdvancedCongruent;
    }
}

// Начало всех вычислений
void CoreGenerateValueProbabilityTheory::calculateMain()
{
    // Генерирование случайных чисел
    generateValueNumber();

    // Вычисление интервалов гистограммы
    calculateIntervalHistogram();

    // Вычсиление границ диапозонов
    calculateBorderRange();

    // Вычисление частот
    calculateFrequency();

    // Вычисление суммы частот
    calculateSummaFrequency();

    // Вычисление относительных частот
    calculateRegardingFrequency();

    // Вычисление накопительных частот
    calculateAccumulationFrequency();

    // Вычисление математического ожидания
    calculateMathematicalExpectation();

    // Вычисление дисперсии
    calculateDispersion();

    // Вычисления моментов
    calculateMoment();
}

// Генерирование чисел
void CoreGenerateValueProbabilityTheory::generateValueNumber()
{
    // Предворительная очистка массивов
    vectorValueGenerateAdditive.clear();
    vectorValueGenerateCongruent.clear();
    vectorValueGenerateAdvancedCongruent.clear();

    // Ядро генерации для равномерного распределения (встроенного)
    srand(time(NULL));

    /*
        Аддитивный алгоритм
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

        vectorValueGenerateAdditive.push_back(tmpValue - (int)tmpValue);
    }

    // Преобразование сгенерированных чисел в нужный диапозон
    for (size_t i = 0; i < (size_t)countGenerateNumber; i++)
    {
        vectorValueGenerateAdditive[i] = vectorValueGenerateAdditive[i]*(end - begin) + begin;
    }

    /*
        Конгруэнтный алгоритм
    */
    for (size_t i = 0, next = (int)rand(); i < (size_t)countGenerateNumber; i++)
    {
        next = ((8 * next) + 65) % 100;

        vectorValueGenerateCongruent.push_back(next / 100.);
    }

    // Преобразование сгенерированных чисел в нужный диапозон
    for (size_t i = 0; i < (size_t)countGenerateNumber; i++)
    {
        vectorValueGenerateCongruent[i] = vectorValueGenerateCongruent[i]*(end - begin) + begin;
    }

    /*
        Усовершенствованный конгруэнтный алгоритм
    */
    for (size_t i = 0; i < (size_t)countGenerateNumber; i++)
    {
        // Датчик генерации
        double tmpValueGenerateSensor = (double)rand() / RAND_MAX;

        // Равномерно распределённые числа от датчика в диапозоне (0;1)
        double valueTmpGenerate;

        // Сумма трёх распределённых чисел от датчиков
        double summaValueTmpGenerate(0);

        for (size_t j = 0; j < 3; j++)
        {
            tmpValueGenerateSensor = valueA * (mod(tmpValueGenerateSensor, valueB))
                    - valueC * tmpValueGenerateSensor / valueB;

            valueTmpGenerate = tmpValueGenerateSensor / (double)valueD;

            summaValueTmpGenerate += valueTmpGenerate;
        }

        vectorValueGenerateAdvancedCongruent.push_back(mod(summaValueTmpGenerate, 1));
    }

    // Преобразование сгенерированных чисел в нужный диапозон
    for (size_t i = 0; i < (size_t)countGenerateNumber; i++)
    {
        vectorValueGenerateAdvancedCongruent[i] = vectorValueGenerateAdvancedCongruent[i]*(end - begin)
                + begin;
    }
}

// Вычисление интервалов
void CoreGenerateValueProbabilityTheory::calculateIntervalHistogram()
{
    // Максимальное и минимальное значение для случайных чисел
    double maxAdditive(vectorValueGenerateAdditive[0]),
            minAdditive(vectorValueGenerateAdditive[0]),
            maxCongruent(vectorValueGenerateCongruent[0]),
            minCongruent(vectorValueGenerateCongruent[0]),
            maxAdvancedCongruent(vectorValueGenerateAdvancedCongruent[0]),
            minAdvancedCongruent(vectorValueGenerateAdvancedCongruent[0]);

    // Поиск минимальных и максимальных значений
    for (size_t i = 1; i < (size_t)countGenerateNumber; i++)
    {
        if (maxAdditive < vectorValueGenerateAdditive[i])
            maxAdditive = vectorValueGenerateAdditive[i];

        if (minAdditive > vectorValueGenerateAdditive[i])
            minAdditive = vectorValueGenerateAdditive[i];

        if (maxCongruent < vectorValueGenerateCongruent[i])
            maxCongruent = vectorValueGenerateCongruent[i];

        if (minCongruent > vectorValueGenerateCongruent[i])
            minCongruent = vectorValueGenerateCongruent[i];

        if (maxAdvancedCongruent < vectorValueGenerateAdvancedCongruent[i])
            maxAdvancedCongruent = vectorValueGenerateAdvancedCongruent[i];

        if (minAdvancedCongruent > vectorValueGenerateAdvancedCongruent[i])
            minAdvancedCongruent = vectorValueGenerateAdvancedCongruent[i];
    }

    // Вычисление интервалов
    intervalHistogramAdditive = (maxAdditive - minAdditive)
            / floor(1 + 3.322 * log10(countGenerateNumber));

    intervalHistogramCongruent = (maxCongruent - minCongruent)
            / floor(1 + 3.322 * log10(countGenerateNumber));

    intervalHistogramAdvancedCongruent = (maxAdvancedCongruent - minAdvancedCongruent)
            / floor(1 + 3.322 * log10(countGenerateNumber));

    // Запоминаем минимальные и максимальные значения
    this->minAdditive = minAdditive;
    this->maxAdditive = maxAdditive;
    this->minCongruent = minCongruent;
    this->maxCongruent = maxCongruent;
    this->minAdvancedCongruent = minAdvancedCongruent;
    this->maxAdvancedCongruent = maxAdvancedCongruent;
}

// Вычисление границ диапозонов
void CoreGenerateValueProbabilityTheory::calculateBorderRange()
{
    // Очистка векторов
    vectorBorderRangeAdditive.clear();
    vectorBorderRangeCongruent.clear();
    vectorBorderRangeAdvancedCongruent.clear();

    // Нулевое значение
    vectorBorderRangeAdditive.push_back(minAdditive);
    vectorBorderRangeCongruent.push_back(minCongruent);
    vectorBorderRangeAdvancedCongruent.push_back(minAdvancedCongruent);

    double tmpValueBordeRangeAdditive = minAdditive + intervalHistogramAdditive;
    double tmpValueBordeRangeCongruent = minCongruent + intervalHistogramCongruent;
    double tmpValueBordeRangeAdvancedCongruent = minAdvancedCongruent + intervalHistogramAdvancedCongruent;

    for (size_t i = 1; maxAdditive - tmpValueBordeRangeAdditive > 0; i++)
    {
        vectorBorderRangeAdditive.push_back(tmpValueBordeRangeAdditive);

        tmpValueBordeRangeAdditive = vectorBorderRangeAdditive[i] + intervalHistogramAdditive;
    }

    for (size_t i = 1; maxCongruent - tmpValueBordeRangeCongruent > 0; i++)
    {
        vectorBorderRangeCongruent.push_back(tmpValueBordeRangeCongruent);

        tmpValueBordeRangeCongruent = vectorBorderRangeCongruent[i] + intervalHistogramCongruent;
    }

    for (size_t i = 1; maxAdvancedCongruent - tmpValueBordeRangeAdvancedCongruent > 0; i++)
    {
        vectorBorderRangeAdvancedCongruent.push_back(tmpValueBordeRangeAdvancedCongruent);

        tmpValueBordeRangeAdvancedCongruent = vectorBorderRangeAdvancedCongruent[i]
                + intervalHistogramAdvancedCongruent;
    }
}

// Вычисление частот
void CoreGenerateValueProbabilityTheory::calculateFrequency()
{
    // Очистка массивов
    vectorFrequencyAdditive.assign(vectorBorderRangeAdditive.size() + 1, 0);
    vectorFrequencyCongruent.assign(vectorBorderRangeAdditive.size() + 1, 0);
    vectorFrequencyAdvancedCongruent.assign(vectorBorderRangeAdditive.size() + 1, 0);

    // Вычисления частот
    for (size_t i = 0; i < countGenerateNumber; i++)
    {
        for (size_t j = 1, maxJ = vectorBorderRangeAdditive.size(); j < maxJ; j++)
        {
            if (vectorValueGenerateAdditive[i] >= vectorBorderRangeAdditive[j - 1]
                    && vectorValueGenerateAdditive[i] < vectorBorderRangeAdditive[j])
                vectorFrequencyAdditive[j - 1]++;
        }

        for (size_t j = 1, maxJ = vectorBorderRangeCongruent.size(); j < maxJ; j++)
        {
            if (vectorValueGenerateCongruent[i] >= vectorBorderRangeCongruent[j - 1]
                    && vectorValueGenerateCongruent[i] < vectorBorderRangeCongruent[j])
                vectorFrequencyCongruent[j - 1]++;
        }

        for (size_t j = 1, maxJ = vectorBorderRangeAdvancedCongruent.size(); j < maxJ; j++)
        {
            if (vectorValueGenerateAdvancedCongruent[i] >= vectorBorderRangeAdvancedCongruent[j - 1]
                    && vectorValueGenerateAdvancedCongruent[i] < vectorBorderRangeAdvancedCongruent[j])
                vectorFrequencyAdvancedCongruent[j - 1]++;
        }
    }
}

// Вычисление суммы частот
void CoreGenerateValueProbabilityTheory::calculateSummaFrequency()
{
    // Обнуление сумм
    summaFrequencyAdditive = 0;
    summaFrequencyCongruent = 0;
    summaFrequencyAdvancedCongruent = 0;

    // Суммирование
    for (size_t i = 0, maxI = vectorFrequencyAdditive.size(); i < maxI; i++)
    {
        summaFrequencyAdditive += vectorFrequencyAdditive[i];
    }

    for (size_t i = 0, maxI = vectorFrequencyCongruent.size(); i < maxI; i++)
    {
        summaFrequencyCongruent += vectorFrequencyCongruent[i];
    }

    for (size_t i = 0, maxI = vectorFrequencyAdvancedCongruent.size(); i < maxI; i++)
    {
        summaFrequencyAdvancedCongruent += vectorFrequencyAdvancedCongruent[i];
    }
}

// Вычисление относительных частот
void CoreGenerateValueProbabilityTheory::calculateRegardingFrequency()
{
    // Очистка относительных частот
    vectorRegardingFrequencyAdditive.clear();
    vectorRegardingFrequencyCongruent.clear();
    vectorRegardingFrequencyAdvancedCongruent.clear();

    // Вычисление относительных частот
    for (size_t i = 0, maxI = vectorFrequencyAdditive.size(); i < maxI; i++)
    {
        vectorRegardingFrequencyAdditive.push_back(vectorFrequencyAdditive[i]
                                                   / summaFrequencyAdditive);
    }

    for (size_t i = 0, maxI = vectorFrequencyCongruent.size(); i < maxI; i++)
    {
        vectorRegardingFrequencyCongruent.push_back(vectorFrequencyCongruent[i]
                                                    / summaFrequencyCongruent);
    }

    for (size_t i = 0, maxI = vectorFrequencyAdvancedCongruent.size(); i < maxI; i++)
    {
        vectorRegardingFrequencyAdvancedCongruent.push_back(vectorFrequencyAdvancedCongruent[i]
                                                            / summaFrequencyAdvancedCongruent);
    }
}

// Вычисление накопленных частот
void CoreGenerateValueProbabilityTheory::calculateAccumulationFrequency()
{
    // Очистка накопленных частот
    vectorAccumulationFrequencyAdditive.clear();
    vectorAccumulationFrequencyCongruent.clear();
    vectorAccumulationFrequencyAdvancedCongruent.clear();

    for (size_t i = 0, maxI = vectorRegardingFrequencyAdditive.size(); i < maxI; i++)
    {
        if (i == 0)
        {
            vectorAccumulationFrequencyAdditive.push_back(vectorRegardingFrequencyAdditive[i]);
        }
        else
        {
            vectorAccumulationFrequencyAdditive.push_back(vectorRegardingFrequencyAdditive[i] + vectorAccumulationFrequencyAdditive[i - 1]);
        }
    }

    for (size_t i = 0, maxI = vectorRegardingFrequencyCongruent.size(); i < maxI; i++)
    {
        if (i == 0)
        {
            vectorAccumulationFrequencyCongruent.push_back(vectorRegardingFrequencyCongruent[i]);
        }
        else
        {
            vectorAccumulationFrequencyCongruent.push_back(vectorRegardingFrequencyCongruent[i] + vectorAccumulationFrequencyCongruent[i - 1]);
        }
    }

    for (size_t i = 0, maxI = vectorRegardingFrequencyAdvancedCongruent.size(); i < maxI; i++)
    {
        if (i == 0)
        {
            vectorAccumulationFrequencyAdvancedCongruent.push_back(vectorRegardingFrequencyAdvancedCongruent[i]);
        }
        else
        {
            vectorAccumulationFrequencyAdvancedCongruent.push_back(vectorRegardingFrequencyAdvancedCongruent[i] + vectorAccumulationFrequencyAdvancedCongruent[i - 1]);
        }
    }
}

// Вычисление математического ожидания
void CoreGenerateValueProbabilityTheory::calculateMathematicalExpectation()
{
    // Обнуление математического ожидания
    mathematicalExpectationAdditive = 0;
    mathematicalExpectationCongruent = 0;
    mathematicalExpectationAdvancedCongruent = 0;

    // Вычисление математического ожидания
    for (size_t i = 0; i < (size_t)countGenerateNumber; i++)
    {
        mathematicalExpectationAdditive += vectorValueGenerateAdditive[i];
        mathematicalExpectationCongruent += vectorValueGenerateCongruent[i];
        mathematicalExpectationAdvancedCongruent += vectorValueGenerateAdvancedCongruent[i];
    }

    mathematicalExpectationAdditive /= countGenerateNumber;
    mathematicalExpectationCongruent /= countGenerateNumber;
    mathematicalExpectationAdvancedCongruent /= countGenerateNumber;
}

// Вычисление дисперсии
void CoreGenerateValueProbabilityTheory::calculateDispersion()
{
    // Обнуление дисперсии
     dispersionAdditive = 0;
     dispersionCongruent = 0;
     dispersionAdvancedCongruent = 0;

     for (size_t i = 0; i < (size_t)countGenerateNumber; i++)
        dispersionAdditive += (vectorValueGenerateAdditive[i] - mathematicalExpectationAdditive)
                * (vectorValueGenerateAdditive[i] - mathematicalExpectationAdditive);

     dispersionAdditive /= countGenerateNumber - 1;

     for (size_t i = 0; i < (size_t)countGenerateNumber; i++)
        dispersionCongruent += (vectorValueGenerateCongruent[i] - mathematicalExpectationCongruent)
                * (vectorValueGenerateCongruent[i] - mathematicalExpectationCongruent);

     dispersionCongruent /= countGenerateNumber - 1;

     for (size_t i = 0; i < (size_t)countGenerateNumber; i++)
        dispersionAdvancedCongruent += (vectorValueGenerateAdvancedCongruent[i] - mathematicalExpectationAdvancedCongruent)
                * (vectorValueGenerateAdvancedCongruent[i] - mathematicalExpectationAdvancedCongruent);

     dispersionAdvancedCongruent /= countGenerateNumber - 1;
}

// Вычисление начальных и центральных моментов
void CoreGenerateValueProbabilityTheory::calculateMoment()
{
    /*
     * Начальные моменты
    */
    // Выделение памяти и обнуление
    vectorBeginMomentAdditive.assign(maxPowerBeginMoment, 0);
    vectorBeginMomentCongruent.assign(maxPowerBeginMoment, 0);
    vectorBeginMomentAdvancedCongruent.assign(maxPowerBeginMoment, 0);

    // Первая степень начального момента (она равна математическому ожиданию)
    vectorBeginMomentAdditive[0] = mathematicalExpectationAdditive;
    vectorBeginMomentCongruent[0] = mathematicalExpectationCongruent;
    vectorBeginMomentAdvancedCongruent[0] = mathematicalExpectationAdvancedCongruent;

    // Все остальные степени начальных моментов

    // Вероятности
    std::vector<double> vectorProbabilityAdditive(vectorFrequencyAdditive.size()),
            vectorProbabilityCongruent(vectorFrequencyCongruent.size()),
            vectorProbabilityAdvancedCongruent(vectorFrequencyAdvancedCongruent.size());

    for (size_t i = 0; i < vectorFrequencyAdditive.size(); i++)
        vectorProbabilityAdditive[i] = vectorFrequencyAdditive[i] / countGenerateNumber;

    for (size_t i = 0; i < vectorFrequencyCongruent.size(); i++)
        vectorProbabilityCongruent[i] = vectorFrequencyCongruent[i] / countGenerateNumber;

    for (size_t i = 0; i < vectorFrequencyAdvancedCongruent.size(); i++)
        vectorProbabilityAdvancedCongruent[i] = vectorFrequencyAdvancedCongruent[i] / countGenerateNumber;

    // Начнём считать остальные степени начальных моментов, если они конечно есть
    for (size_t i = 2; i <= maxPowerBeginMoment; i++)
    {
        for (size_t j = 0, jBorder = 1; j < vectorProbabilityAdditive.size(); j++, jBorder++)
            for (size_t k = 0; k < (size_t)countGenerateNumber; k++)
                if (vectorValueGenerateAdditive[k] >= vectorBorderRangeAdditive[jBorder - 1]
                    && vectorValueGenerateAdditive[k] < vectorBorderRangeAdditive[jBorder])
                    vectorBeginMomentAdditive[i - 1] += vectorProbabilityAdditive[j]
                            * pow(vectorValueGenerateAdditive[k], i);

        for (size_t j = 0, jBorder = 1; j < vectorProbabilityCongruent.size(); j++, jBorder++)
            for (size_t k = 0; k < (size_t)countGenerateNumber; k++)
                if (vectorValueGenerateCongruent[k] >= vectorBorderRangeCongruent[jBorder - 1]
                    && vectorValueGenerateCongruent[k] < vectorBorderRangeCongruent[jBorder])
                    vectorBeginMomentCongruent[i - 1] += vectorProbabilityCongruent[j]
                            * pow(vectorValueGenerateCongruent[k], i);

        for (size_t j = 0, jBorder = 1; j < vectorProbabilityAdvancedCongruent.size(); j++, jBorder++)
            for (size_t k = 0; k < (size_t)countGenerateNumber; k++)
                if (vectorValueGenerateAdvancedCongruent[k] >= vectorBorderRangeAdvancedCongruent[jBorder - 1]
                    && vectorValueGenerateAdvancedCongruent[k] < vectorBorderRangeAdvancedCongruent[jBorder])
                    vectorBeginMomentAdvancedCongruent[i - 1] += vectorProbabilityAdvancedCongruent[j]
                            * pow(vectorValueGenerateAdvancedCongruent[k], i);
    }

    /*
     * Центральные моменты
    */
    // Выделение памяти и обнуление
    vectorCentralMomentAdditive.assign(maxPowerCentralMoment, 0);
    vectorCentralMomentCongruent.assign(maxPowerCentralMoment, 0);
    vectorCentralMomentAdvancedCongruent.assign(maxPowerCentralMoment, 0);

    // Центральные моменты второй степени
    vectorCentralMomentAdditive[1] = dispersionAdditive;
    vectorCentralMomentCongruent[1] = dispersionCongruent;
    vectorCentralMomentAdvancedCongruent[1] = dispersionAdvancedCongruent;

    // Вычисление остальных центральных моментов, если они есть
    for (size_t i = 3; i <= maxPowerCentralMoment; i++)
    {
        for (size_t j = 0, jBorder = 1; j < vectorProbabilityAdditive.size(); j++, jBorder++)
            for (size_t k = 0; k < (size_t)countGenerateNumber; k++)
                if (vectorValueGenerateAdditive[k] >= vectorBorderRangeAdditive[jBorder - 1]
                    && vectorValueGenerateAdditive[k] < vectorBorderRangeAdditive[jBorder])
                    vectorCentralMomentAdditive[i - 1] += vectorProbabilityAdditive[j]
                            * pow(vectorValueGenerateAdditive[k] - mathematicalExpectationAdditive, i);

        for (size_t j = 0, jBorder = 1; j < vectorProbabilityCongruent.size(); j++, jBorder++)
            for (size_t k = 0; k < (size_t)countGenerateNumber; k++)
                if (vectorValueGenerateCongruent[k] >= vectorBorderRangeCongruent[jBorder - 1]
                    && vectorValueGenerateCongruent[k] < vectorBorderRangeCongruent[jBorder])
                    vectorBeginMomentCongruent[i - 1] += vectorProbabilityCongruent[j]
                            * pow(vectorValueGenerateCongruent[k] - mathematicalExpectationCongruent, i);

        for (size_t j = 0, jBorder = 1; j < vectorProbabilityAdvancedCongruent.size(); j++, jBorder++)
            for (size_t k = 0; k < (size_t)countGenerateNumber; k++)
                if (vectorValueGenerateAdvancedCongruent[k] >= vectorBorderRangeAdvancedCongruent[jBorder - 1]
                    && vectorValueGenerateAdvancedCongruent[k] < vectorBorderRangeAdvancedCongruent[jBorder])
                    vectorBeginMomentAdvancedCongruent[i - 1] += vectorProbabilityAdvancedCongruent[j]
                            * pow(vectorValueGenerateAdvancedCongruent[k] - mathematicalExpectationAdvancedCongruent, i);
    }
}

// Операция mod
double CoreGenerateValueProbabilityTheory::mod(double x, double a)
{
    return (x - a *static_cast<int>(x / a));
}
