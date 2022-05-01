#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Прототип класса для генерации случайных величин по трём алгоритмам
class CoreGenerateValueProbabilityTheory;

// Прототип класса для второй лабораторной
class CoreLabaTwo;

// Прототип класса для показательного распределения в пятой лабораторной
class CoreLabaFive;

// Прототип класса об авторе
class DialogAboutAutor;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

// Открытые методы
public:

    // Конструктор по-умолчанию
    explicit MainWindow(QWidget *parent = 0);

    // Деструктор
    ~MainWindow();

// Закрытые методы
private:

    // Обработка данных и построение гистограмм, и таблиц вывода
    void treatmentData();

// Слоты
private slots:

    // Принятие данных и отправка на обработку
    void updateData();

    // Генерирование
    void generateData();

    void on_action_Qt_triggered();

    void on_action_autor_triggered();

    void on_action_generate_triggered();

private:

    // Интерфейс
    Ui::MainWindow *ui;

    // Диалоговое окно об авторе
    DialogAboutAutor *dialogAboutAutor;

    // Ядро вычислений, то есть наша логика генерации случайных чисел и их обработка
    CoreGenerateValueProbabilityTheory *coreLogica;

    // Ядро логики второй лабораторной
    CoreLabaTwo *coreLogicaTwoLaba;

    // Ядро логики показательного распределения для пятой лабы
    CoreLabaFive *coreLogicaFiveLaba;
};

#endif // MAINWINDOW_H
