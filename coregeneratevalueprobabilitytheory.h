#ifndef COREGENERATEVALUEPROBABILITYTHEORY_H
#define COREGENERATEVALUEPROBABILITYTHEORY_H

// Необходимые библиотеки
#include <vector>

/**
* Класс для генерации случайных величин по трём алгоритмам:
* 1) Аддитивный алгоритм
* 2) Конгруэнтный алгоритм
* 3) Усовершенствованный конгруэнтный алгоритм
*
* А также обработка этих случайных величин для построения
* гистограмм функции плотности и функции распределения.
* Также показать математическое ожидание и дисперсию.
*/
class CoreGenerateValueProbabilityTheory
{
// Данные
private:

    /*
        Принятые данные
    */

    // Количество генерирцемых чисел
    int countGenerateNumber;

    // Диапозон генерации случайных чисел. begin - a, end - b.
    // Генерируемое число входит в диапозон X принадлежит [begin; end]
    double begin, end;

    // Порядки начальных и центральных моментов
    double maxPowerBeginMoment, maxPowerCentralMoment;

    /*
        Данные для усовершенствованного конгруэнтного
        алгоритма
    */
    int valueA, valueB, valueC, valueD;

    /*
        Вычисленные данные
    */

    // Массивы сгенерированных случайных величин
    std::vector<double> vectorValueGenerateAdditive;
    std::vector<double> vectorValueGenerateCongruent;
    std::vector<double> vectorValueGenerateAdvancedCongruent;

    // Интервалы для гистограмм
    double intervalHistogramAdditive;
    double intervalHistogramCongruent;
    double intervalHistogramAdvancedCongruent;

    // Минимальные и максимальные значения случайных чисел
    double maxAdditive, minAdditive, maxCongruent, minCongruent,
    maxAdvancedCongruent, minAdvancedCongruent;

    // Массивы границ диапозонов
    std::vector<double> vectorBorderRangeAdditive;
    std::vector<double> vectorBorderRangeCongruent;
    std::vector<double> vectorBorderRangeAdvancedCongruent;

    // Массивы частот
    std::vector<double> vectorFrequencyAdditive;
    std::vector<double> vectorFrequencyCongruent;
    std::vector<double> vectorFrequencyAdvancedCongruent;

    // Суммы частот
    double summaFrequencyAdditive;
    double summaFrequencyCongruent;
    double summaFrequencyAdvancedCongruent;

    /*
        Данные для вывода
    */

    // Массивы относительной частоты
    std::vector<double> vectorRegardingFrequencyAdditive;
    std::vector<double> vectorRegardingFrequencyCongruent;
    std::vector<double> vectorRegardingFrequencyAdvancedCongruent;

    // Массивы накопленных частот
    std::vector<double> vectorAccumulationFrequencyAdditive;
    std::vector<double> vectorAccumulationFrequencyCongruent;
    std::vector<double> vectorAccumulationFrequencyAdvancedCongruent;

    // Математическое ожидание
    double mathematicalExpectationAdditive;
    double mathematicalExpectationCongruent;
    double mathematicalExpectationAdvancedCongruent;

    // Дисперсия
    double dispersionAdditive;
    double dispersionCongruent;
    double dispersionAdvancedCongruent;

    // Начальные моменты
    std::vector<double> vectorBeginMomentAdditive;
    std::vector<double> vectorBeginMomentCongruent;
    std::vector<double> vectorBeginMomentAdvancedCongruent;

    // Центральные моменты
    std::vector<double> vectorCentralMomentAdditive;
    std::vector<double> vectorCentralMomentCongruent;
    std::vector<double> vectorCentralMomentAdvancedCongruent;

// Функицонал
public:

    /*
        Конструкторы
    */

    // Конструктор по-умолчанию
    CoreGenerateValueProbabilityTheory();

    /*
        Сеттеры
    */
    // Сеттер величин A,B,C,D для усовершенствованного конгурентного алгоритма
    void setValueABCD(int valueA, int valueB, int valueC, int valueD);

    // Сеттер количества сгенерированных чисел
    void setCountGenerateNumber(int countGenerateNumber);

    // Сеттер начала диапозона для генерации чисел
    void setBegin(double begin);

    // Сеттер конца диапозона для генерации чисел
    void setEnd(double end);

    // Сеттер порядка моментов
    void setBeginAndCentralMomentPower(double maxPowerBeginMoment, double maxPowerCentralMoment);

    /*
        Геттеры
    */
    // Геттер массива относительных частот
    std::vector<double> getVectorRegardingFrequency(int numberAlgoritm) const;

    // Геттер массива накопленных частот
    std::vector<double> getVectorAccumulationFrequency(int numberAlgoritm) const;

    // Геттер математического ожидания
    double getMathematicalExpectation(int numberAlgoritm) const;

    // Геттер дисперсии
    double getDispersion(int numberAlgoritm) const;

    // Геттер начальных моментов
    std::vector<double> getBeginMoment(int numberAlgoritm) const;

    // Геттер центральных моментов
    std::vector<double> getCentralMoment(int numberAlgoritm) const;

    // Геттер вектора случаный сгенерированных величин
    std::vector<double> getVectorValueGenerate(int numberAlgoritm) const;

    /*
        Начало всех вычислений
    */
    void calculateMain();

private:

    // Генерирование чисел
    void generateValueNumber();

    // Вычисление интервалов
    void calculateIntervalHistogram();

    // Вычисление границ диапозонов
    void calculateBorderRange();

    // Вычисление частот
    void calculateFrequency();

    // Вычисление суммы частот
    void calculateSummaFrequency();

    // Вычисление относительных частот
    void calculateRegardingFrequency();

    // Вычисление накопленных частот
    void calculateAccumulationFrequency();

    // Вычисление математического ожидания
    void calculateMathematicalExpectation();

    // Вычисление дисперсии
    void calculateDispersion();

    // Вычисление начальных и центральных моментов
    void calculateMoment();

    // Операция mod
    static double mod(double x, double a);
};

#endif // COREGENERATEVALUEPROBABILITYTHEORY_H
