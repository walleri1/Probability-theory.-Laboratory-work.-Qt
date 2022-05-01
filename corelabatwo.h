#ifndef CORELABATWO_H
#define CORELABATWO_H

// Необходимые библиотеки
#include <vector>

/**
  *
  * Класс для генерации случаных чисел в нормальном распределении
  * и их дальнейшей обработке
*/
class CoreLabaTwo
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

    // Специальные параметры переданные пользователем
    double mathematicalExpectation, dispersion;

    /*
        Вычисленные данные для обоих алгоритмов
    */

    // Массивы сгенерированных случайных величин равномерного распределения
    std::vector<double> vectorValueGenerateEvenlyOne;
    std::vector<double> vectorValueGenerateEvenlyTwo;

    /*
     * Для первого алгоритма
    */

    /*
        Вычисленные данные
    */

    // Математическое ожидание равномерного распределения
    double mathematicalExpectationOneAlgoritmEvenly;

    // Дисперсия равномерного распределения
    double dispersionOneAlgoritmEvenly;

    // Массивы сгенерированных случайных величин нормального распределения
    std::vector<double> vectorValueGenerateOneAlgoritmNormally;

    // Интервалы для гистограмм
    double intervalHistogramOneAlgoritmNormally;

    // Минимальные и максимальные значения случайных чисел
    double maxOneAlgoritmNormally, minOneAlgoritmNormally;

    // Массивы границ диапозонов
    std::vector<double> vectorBorderRangeOneAlgoritmNormally;

    // Массивы частот
    std::vector<double> vectorFrequencyOneAlgoritmNormally;

    // Суммы частот
    double summaFrequencyOneAlgoritmNormally;

    /*
        Данные для вывода
    */

    // Массивы относительной частоты
    std::vector<double> vectorRegardingFrequencyOneAlgoritmNormally;

    // Массивы накопленных частот
    std::vector<double> vectorAccumulationFrequencyOneAlgoritmNormally;

    // Математическое ожидание
    double mathematicalExpectationOneAlgoritmNormally;

    // Дисперсия
    double dispersionOneAlgoritmNormally;

    // Начальные моменты
    std::vector<double> vectorBeginMomentOneAlgoritmNormally;

    // Центральные моменты
    std::vector<double> vectorCentralMomentOneAlgoritmNormally;

    /*
     * Для второго алгоритма
    */

    /*
        Вычисленные данные
    */

    // Математическое ожидание равномерного распределения
    double mathematicalExpectationTwoAlgoritmEvenly;

    // Дисперсия равномерного распределения
    double dispersionTwoAlgoritmEvenly;

    // Массивы сгенерированных случайных величин нормального распределения
    std::vector<double> vectorValueGenerateTwoAlgoritmNormally;

    // Интервалы для гистограмм
    double intervalHistogramTwoAlgoritmNormally;

    // Минимальные и максимальные значения случайных чисел
    double maxTwoAlgoritmNormally, minTwoAlgoritmNormally;

    // Массивы границ диапозонов
    std::vector<double> vectorBorderRangeTwoAlgoritmNormally;

    // Массивы частот
    std::vector<double> vectorFrequencyTwoAlgoritmNormally;

    // Суммы частот
    double summaFrequencyTwoAlgoritmNormally;

    /*
        Данные для вывода
    */

    // Массивы относительной частоты
    std::vector<double> vectorRegardingFrequencyTwoAlgoritmNormally;

    // Массивы накопленных частот
    std::vector<double> vectorAccumulationFrequencyTwoAlgoritmNormally;

    // Математическое ожидание
    double mathematicalExpectationTwoAlgoritmNormally;

    // Дисперсия
    double dispersionTwoAlgoritmNormally;

    // Начальные моменты
    std::vector<double> vectorBeginMomentTwoAlgoritmNormally;

    // Центральные моменты
    std::vector<double> vectorCentralMomentTwoAlgoritmNormally;

// Функционал
public:

    /*
        Конструкторы
    */

    // Конструктор по-умолчанию
    CoreLabaTwo();

    /*
        Сеттеры
    */

    // Сеттер количества сгенерированных чисел
    void setCountGenerateNumber(int countGenerateNumber);

    // Сеттер порядка моментов
    void setBeginAndCentralMomentPower(double maxPowerBeginMoment, double maxPowerCentralMoment);

    // Сеттер математического ожидания и десперсии от специального блока
    void setSpecBlock(double mathematicalExpectation, double dispersion);

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

    // Генерирование чисел равномерного распределения
    void generateValueNumberEvenly();

    // Генерирование чисел нормального распределения
    void generateValueNumberNormally();

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

#endif // CORELABATWO_H
