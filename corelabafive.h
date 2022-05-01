#ifndef CORELABAFIVE_H
#define CORELABAFIVE_H

// Необходимые библиотеки
#include <vector>

/**
  *
  * Класс для генерации случаных чисел в показательном распределении
  * и их дальнейшей обработке
*/

class CoreLabaFive
{
// Данные
private:

    /*
        Принятые данные
    */
    // Количество генерируемых чисел
    int countGenerateNumber;

    // Порядки начальных и центральных моментов
    double maxPowerBeginMoment, maxPowerCentralMoment;

    // Параметр лямбда для показательного распределения
    double lambda;

    /*
        Вычисленные данные
    */

    // Массивы сгенерированных случайных величин равномерного распределения
    std::vector<double> vectorValueGenerateEvenly;

    // Массивы сгенерированных случайных величин нормального распределения
    std::vector<double> vectorValueGenerateExponential;

    // Интервалы для гистограмм
    double intervalHistogramExponential;

    // Минимальные и максимальные значения случайных чисел
    double maxExponential, minExponential;

    // Массивы границ диапозонов
    std::vector<double> vectorBorderRangeExponential;

    // Массивы частот
    std::vector<double> vectorFrequencyExponential;

    // Суммы частот
    double summaFrequencyExponential;

    /*
        Данные для вывода
    */

    // Массивы относительной частоты
    std::vector<double> vectorRegardingFrequencyExponential;

    // Массивы накопленных частот
    std::vector<double> vectorAccumulationFrequencyExponential;

    // Математическое ожидание
    double mathematicalExpectationExponential;

    // Дисперсия
    double dispersionExponential;

    // Начальные моменты
    std::vector<double> vectorBeginMomentExponential;

    // Центральные моменты
    std::vector<double> vectorCentralMomentExponential;

// Функционал
public:

    /*
        Конструкторы
    */

    // Конструктор по-умолчанию
    CoreLabaFive();

    /*
        Сеттеры
    */

    // Сеттер количества сгенерированных чисел
    void setCountGenerateNumber(int countGenerateNumber);

    // Сеттер порядка моментов
    void setBeginAndCentralMomentPower(double maxPowerBeginMoment, double maxPowerCentralMoment);

    // Сеттер параметра лямбды для показательного распределения
    void setLambda(double lambda);

    /*
        Геттеры
    */

    // Геттер массива относительных частот
    std::vector<double> getVectorRegardingFrequency() const;

    // Геттер массива накопленных частот
    std::vector<double> getVectorAccumulationFrequency() const;

    // Геттер математического ожидания
    double getMathematicalExpectation() const;

    // Геттер дисперсии
    double getDispersion() const;

    // Геттер начальных моментов
    std::vector<double> getBeginMoment() const;

    // Геттер центральных моментов
    std::vector<double> getCentralMoment() const;

    // Геттер вектора случаный сгенерированных величин
    std::vector<double> getVectorValueGenerate() const;

    /*
        Начало всех вычислений
    */

    void calculateMain();

private:

    // Генерирование чисел равномерного распределения
    void generateValueNumberEvenly();

    // Генерирование чисел показательного распределения
    void generateValueNumberExponential();

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
};

#endif // CORELABAFIVE_H
