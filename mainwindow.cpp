#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "coregeneratevalueprobabilitytheory.h"
#include "corelabatwo.h"
#include "corelabafive.h"
#include "dialogaboutautor.h"
#include "qcustomplot.h"

// Конструктор по-умолчанию
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Установка интерфейса
    ui->setupUi(this);

    // Отключение label для второй лабы мат ожидание и дисперсия
    ui->labelMatDispOneAlgoritm->hide();
    ui->labelMatDispTwoAlgoritm->hide();

    // Создание окна об авторе
    dialogAboutAutor = new DialogAboutAutor(this);

    // Наименование столбцов таблиц
    ui->tableWidgetAdditive->setHorizontalHeaderLabels(QStringList() << tr("Относительные частоты") << tr("Накопленные частоты")
                    << tr("Математическое ожидание") << tr("Дисперсия") << tr("Начальные моменты") << tr("Центральные моменты")
                    << tr("Случайные числа"));
    ui->tableWidgetCongruent->setHorizontalHeaderLabels(QStringList() << tr("Относительные частоты") << tr("Накопленные частоты")
                    << tr("Математическое ожидание") << tr("Дисперсия") << tr("Начальные моменты") << tr("Центральные моменты")
                    << tr("Случайные числа"));
    ui->tableWidgetAdvancedCongruent->setHorizontalHeaderLabels(QStringList() << tr("Относительные частоты") << tr("Накопленные частоты")
                    << tr("Математическое ожидание") << tr("Дисперсия") << tr("Начальные моменты") << tr("Центральные моменты")
                    << tr("Случайные числа"));
    ui->tableWidgetOneAlgoritm->setHorizontalHeaderLabels(QStringList() << tr("Относительные частоты") << tr("Накопленные частоты")
                    << tr("Математическое ожидание") << tr("Дисперсия") << tr("Начальные моменты") << tr("Центральные моменты")
                    << tr("Случайные числа"));
    ui->tableWidgetTwoAlgoritm->setHorizontalHeaderLabels(QStringList() << tr("Относительные частоты") << tr("Накопленные частоты")
                    << tr("Математическое ожидание") << tr("Дисперсия") << tr("Начальные моменты") << tr("Центральные моменты")
                    << tr("Случайные числа"));
    ui->tableWidgetExponential->setHorizontalHeaderLabels(QStringList() << tr("Относительные частоты") << tr("Накопленные частоты")
                    << tr("Математическое ожидание") << tr("Дисперсия") << tr("Начальные моменты") << tr("Центральные моменты")
                    << tr("Случайные числа"));

    // Запуск логического ядра первой лабы
    coreLogica = new CoreGenerateValueProbabilityTheory();

    // Запуск логического ядра второй лабы
    coreLogicaTwoLaba = new CoreLabaTwo();

    // Запуск логического ядра для показательного распределения
    coreLogicaFiveLaba = new CoreLabaFive();

    // Передача данных из интерфейса в логику
    updateData();

    // Генерирование данные и отображение
    generateData();
}

// Деструктор
MainWindow::~MainWindow()
{
    delete ui;
    delete dialogAboutAutor;
}

// Обработка данных и построение гистограмм, и таблиц вывода
void MainWindow::treatmentData()
{
    // Очитска графиков
    ui->qcustomplotDistributionAdditive->clearPlottables();
    ui->qcustomplotDistributionCongruent->clearPlottables();
    ui->qcustomplotDistributionAdvancedCongruent->clearPlottables();
    ui->qcustomplotDistributionOneAlgoritm->clearPlottables();
    ui->qcustomplotDistributionTwoAlgoritm->clearPlottables();
    ui->qcustomplotDistributionExponential->clearPlottables();
    ui->qcutomplotDensityeAdditive->clearPlottables();
    ui->qcutomplotDensityeCongruent->clearPlottables();
    ui->qcutomplotDensityeAdvancedCongruent->clearPlottables();
    ui->qcutomplotDensityeOneAlgoritm->clearPlottables();
    ui->qcutomplotDensityeTwoAlgoritm->clearPlottables();
    ui->qcutomplotDensityeExponential->clearPlottables();

    // Массивы относительной частоты
    QVector<double> vectorRegardingFrequencyAdditive =
            QVector<double>::fromStdVector(coreLogica->getVectorRegardingFrequency(1));
    QVector<double> vectorRegardingFrequencyCongruent =
            QVector<double>::fromStdVector(coreLogica->getVectorRegardingFrequency(2));
    QVector<double> vectorRegardingFrequencyAdvancedCongruent =
            QVector<double>::fromStdVector(coreLogica->getVectorRegardingFrequency(3));
    QVector<double> vectorRegardingFrequencyOneAlgoritm =
            QVector<double>::fromStdVector(coreLogicaTwoLaba->getVectorRegardingFrequency(1));
    QVector<double> vectorRegardingFrequencyTwoAlgoritm =
            QVector<double>::fromStdVector(coreLogicaTwoLaba->getVectorRegardingFrequency(2));
    QVector<double> vectorRegardingFrequencyExponential =
            QVector<double>::fromStdVector(coreLogicaFiveLaba->getVectorRegardingFrequency());

    // Массивы накопленных частот
    QVector<double> vectorAccumulationFrequencyAdditive =
            QVector<double>::fromStdVector(coreLogica->getVectorAccumulationFrequency(1));
    QVector<double> vectorAccumulationFrequencyCongruent =
            QVector<double>::fromStdVector(coreLogica->getVectorAccumulationFrequency(2));
    QVector<double> vectorAccumulationFrequencyAdvancedCongruent =
            QVector<double>::fromStdVector(coreLogica->getVectorAccumulationFrequency(3));
    QVector<double> vectorAccumulationFrequencyOneAlgoritm =
            QVector<double>::fromStdVector(coreLogicaTwoLaba->getVectorAccumulationFrequency(1));
    QVector<double> vectorAccumulationFrequencyTwoAlgoritm =
            QVector<double>::fromStdVector(coreLogicaTwoLaba->getVectorAccumulationFrequency(2));
    QVector<double> vectorAccumulationFrequencyExponential =
            QVector<double>::fromStdVector(coreLogicaFiveLaba->getVectorAccumulationFrequency());

    // Определения максимумов
    double maxRegardingFrequencyAdditive(vectorRegardingFrequencyAdditive[0]),
            maxRegardingFrequencyCongruent(vectorRegardingFrequencyCongruent[0]),
            maxRegardingFrequencyAdvancedCongruent(vectorRegardingFrequencyAdvancedCongruent[0]),
            maxAccumulationFrequencyAdditive(vectorAccumulationFrequencyAdditive[0]),
            maxAccumulationFrequencyCongruent(vectorAccumulationFrequencyCongruent[0]),
            maxAccumulationFrequencyAdvancedCongruent(vectorAccumulationFrequencyAdvancedCongruent[0]),
            maxRegardingFrequencyOneAlgoritm(vectorRegardingFrequencyOneAlgoritm[0]),
            maxRegardingFrequencyTwoAlgoritm(vectorRegardingFrequencyTwoAlgoritm[0]),
            maxRegardingFrequencyExponential(vectorRegardingFrequencyExponential[0]),
            maxAccumulationFrequencyOneAlgoritm(vectorAccumulationFrequencyOneAlgoritm[0]),
            maxAccumulationFrequencyTwoAlgoritm(vectorAccumulationFrequencyTwoAlgoritm[0]),
            maxAccumulationFrequencyExponential(vectorAccumulationFrequencyExponential[0]);

    for (size_t i = 0; i < (size_t)vectorRegardingFrequencyAdditive.size(); i++)
        if (maxRegardingFrequencyAdditive < vectorRegardingFrequencyAdditive[i])
            maxRegardingFrequencyAdditive = vectorRegardingFrequencyAdditive[i];

    for (size_t i = 0; i < (size_t)vectorRegardingFrequencyCongruent.size(); i++)
        if (maxRegardingFrequencyCongruent < vectorRegardingFrequencyCongruent[i])
            maxRegardingFrequencyCongruent = vectorRegardingFrequencyCongruent[i];

    for (size_t i = 0; i < (size_t)vectorRegardingFrequencyAdvancedCongruent.size(); i++)
        if (maxRegardingFrequencyAdvancedCongruent < vectorRegardingFrequencyAdvancedCongruent[i])
            maxRegardingFrequencyAdvancedCongruent = vectorRegardingFrequencyAdvancedCongruent[i];

    for (size_t i = 0; i < (size_t)vectorRegardingFrequencyOneAlgoritm.size(); i++)
        if (maxRegardingFrequencyOneAlgoritm < vectorRegardingFrequencyOneAlgoritm[i])
            maxRegardingFrequencyOneAlgoritm = vectorRegardingFrequencyOneAlgoritm[i];

    for (size_t i = 0; i < (size_t)vectorRegardingFrequencyTwoAlgoritm.size(); i++)
        if (maxRegardingFrequencyTwoAlgoritm < vectorRegardingFrequencyTwoAlgoritm[i])
            maxRegardingFrequencyTwoAlgoritm = vectorRegardingFrequencyTwoAlgoritm[i];

    for (size_t i = 0; i < (size_t)vectorRegardingFrequencyExponential.size(); i++)
        if (maxRegardingFrequencyExponential < vectorRegardingFrequencyExponential[i])
            maxRegardingFrequencyExponential = vectorRegardingFrequencyExponential[i];

    for (size_t i = 0; i < (size_t)vectorAccumulationFrequencyAdditive.size(); i++)
        if (maxAccumulationFrequencyAdditive < vectorAccumulationFrequencyAdditive[i])
            maxAccumulationFrequencyAdditive = vectorAccumulationFrequencyAdditive[i];

    for (size_t i = 0; i < (size_t)vectorAccumulationFrequencyCongruent.size(); i++)
        if (maxAccumulationFrequencyCongruent < vectorAccumulationFrequencyCongruent[i])
            maxAccumulationFrequencyCongruent = vectorAccumulationFrequencyCongruent[i];

    for (size_t i = 0; i < (size_t)vectorAccumulationFrequencyAdvancedCongruent.size(); i++)
        if (maxAccumulationFrequencyAdvancedCongruent < vectorAccumulationFrequencyAdvancedCongruent[i])
            maxAccumulationFrequencyAdvancedCongruent = vectorAccumulationFrequencyAdvancedCongruent[i];

    for (size_t i = 0; i < (size_t)vectorAccumulationFrequencyOneAlgoritm.size(); i++)
        if (maxAccumulationFrequencyOneAlgoritm < vectorAccumulationFrequencyOneAlgoritm[i])
            maxAccumulationFrequencyOneAlgoritm = vectorAccumulationFrequencyOneAlgoritm[i];

    for (size_t i = 0; i < (size_t)vectorAccumulationFrequencyTwoAlgoritm.size(); i++)
        if (maxAccumulationFrequencyTwoAlgoritm < vectorAccumulationFrequencyTwoAlgoritm[i])
            maxAccumulationFrequencyTwoAlgoritm = vectorAccumulationFrequencyTwoAlgoritm[i];

    for (size_t i = 0; i < (size_t)vectorAccumulationFrequencyExponential.size(); i++)
        if (maxAccumulationFrequencyExponential < vectorAccumulationFrequencyExponential[i])
            maxAccumulationFrequencyExponential = vectorAccumulationFrequencyExponential[i];

    /*
     * Аддитивный алгоритм
    */
    // Создание пустых гистограммных объектов
    QCPBars *distributionDensityBarsAdditive = new QCPBars(ui->qcutomplotDensityeAdditive->xAxis, ui->qcutomplotDensityeAdditive->yAxis);
    QCPBars *distributionBarsAdditive = new QCPBars(ui->qcustomplotDistributionAdditive->xAxis, ui->qcustomplotDistributionAdditive->yAxis);

    // Сглаживание
    distributionDensityBarsAdditive->setAntialiased(false);
    distributionBarsAdditive->setAntialiased(false);

    distributionDensityBarsAdditive->setStackingGap(1);
    distributionBarsAdditive->setStackingGap(1);

    QVector<double> ticksAdditive;
    QVector<QString> labelsAdditive;

    for (size_t i = 1; i <= (size_t)vectorRegardingFrequencyAdditive.size(); i++)
    {
        ticksAdditive.push_back(i);
        labelsAdditive.push_back(tr("%1").arg(i));
    }

    QSharedPointer<QCPAxisTickerText> textTickerAdditive(new QCPAxisTickerText);
    textTickerAdditive->addTicks(ticksAdditive, labelsAdditive);

    ui->qcutomplotDensityeAdditive->xAxis->setTicker(textTickerAdditive);
    ui->qcutomplotDensityeAdditive->xAxis->setSubTicks(false);
    ui->qcutomplotDensityeAdditive->xAxis->setTickLength(0, 1);
    ui->qcutomplotDensityeAdditive->xAxis->setRange(0,
                                vectorRegardingFrequencyAdditive.size());
    ui->qcutomplotDensityeAdditive->xAxis->setBasePen(QPen(Qt::black));
    ui->qcutomplotDensityeAdditive->xAxis->setTickPen(QPen(Qt::black));
    ui->qcutomplotDensityeAdditive->xAxis->grid()->setVisible(true);
    ui->qcutomplotDensityeAdditive->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->qcutomplotDensityeAdditive->xAxis->setTickLabelColor(Qt::black);
    ui->qcutomplotDensityeAdditive->xAxis->setLabelColor(Qt::black);

    ui->qcustomplotDistributionAdditive->xAxis->setTicker(textTickerAdditive);
    ui->qcustomplotDistributionAdditive->xAxis->setSubTicks(false);
    ui->qcustomplotDistributionAdditive->xAxis->setTickLength(0, 1);
    ui->qcustomplotDistributionAdditive->xAxis->setRange(0,
                                vectorRegardingFrequencyAdditive.size());
    ui->qcustomplotDistributionAdditive->xAxis->setBasePen(QPen(Qt::black));
    ui->qcustomplotDistributionAdditive->xAxis->setTickPen(QPen(Qt::black));
    ui->qcustomplotDistributionAdditive->xAxis->grid()->setVisible(true);
    ui->qcustomplotDistributionAdditive->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->qcustomplotDistributionAdditive->xAxis->setTickLabelColor(Qt::black);
    ui->qcustomplotDistributionAdditive->xAxis->setLabelColor(Qt::black);

    // Подготовка оси Y:
    ui->qcutomplotDensityeAdditive->yAxis->setRange(0, maxRegardingFrequencyAdditive);
    ui->qcutomplotDensityeAdditive->yAxis->setPadding(1);
    ui->qcutomplotDensityeAdditive->yAxis->setBasePen(QPen(Qt::black));
    ui->qcutomplotDensityeAdditive->yAxis->setTickPen(QPen(Qt::black));
    ui->qcutomplotDensityeAdditive->yAxis->setSubTickPen(QPen(Qt::black));
    ui->qcutomplotDensityeAdditive->yAxis->grid()->setSubGridVisible(true);
    ui->qcutomplotDensityeAdditive->yAxis->setTickLabelColor(Qt::black);
    ui->qcutomplotDensityeAdditive->yAxis->setLabelColor(Qt::black);
    ui->qcutomplotDensityeAdditive->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->qcutomplotDensityeAdditive->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    ui->qcustomplotDistributionAdditive->yAxis->setRange(0, maxAccumulationFrequencyAdditive);
    ui->qcustomplotDistributionAdditive->yAxis->setPadding(1);
    ui->qcustomplotDistributionAdditive->yAxis->setBasePen(QPen(Qt::black));
    ui->qcustomplotDistributionAdditive->yAxis->setTickPen(QPen(Qt::black));
    ui->qcustomplotDistributionAdditive->yAxis->setSubTickPen(QPen(Qt::black));
    ui->qcustomplotDistributionAdditive->yAxis->grid()->setSubGridVisible(true);
    ui->qcustomplotDistributionAdditive->yAxis->setTickLabelColor(Qt::black);
    ui->qcustomplotDistributionAdditive->yAxis->setLabelColor(Qt::black);
    ui->qcustomplotDistributionAdditive->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->qcustomplotDistributionAdditive->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Добавление данных:
    QVector<double> distributionDensityDataAdditive, distributionDataAdditive;

    for (size_t i = 0; i < (size_t)vectorRegardingFrequencyAdditive.size(); i++)
    {
        distributionDensityDataAdditive << vectorRegardingFrequencyAdditive[i];
        distributionDataAdditive << vectorAccumulationFrequencyAdditive[i];
    }

    distributionDensityBarsAdditive->setData(ticksAdditive, distributionDensityDataAdditive);
    distributionBarsAdditive->setData(ticksAdditive, distributionDataAdditive);

    // Установка легенды:
    ui->qcutomplotDensityeAdditive->legend->setVisible(false);
    ui->qcutomplotDensityeAdditive->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->qcutomplotDensityeAdditive->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    ui->qcutomplotDensityeAdditive->replot();

    ui->qcustomplotDistributionAdditive->legend->setVisible(false);
    ui->qcustomplotDistributionAdditive->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->qcustomplotDistributionAdditive->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    ui->qcustomplotDistributionAdditive->replot();

    /*
     * Конгруэнтный алгоритм
    */
    // Создание пустых гистограммных объектов
    QCPBars *distributionDensityBarsCongruent = new QCPBars(ui->qcutomplotDensityeCongruent->xAxis, ui->qcutomplotDensityeCongruent->yAxis);
    QCPBars *distributionBarsCongruent = new QCPBars(ui->qcustomplotDistributionCongruent->xAxis, ui->qcustomplotDistributionCongruent->yAxis);

    // Сглаживание
    distributionDensityBarsCongruent->setAntialiased(false);
    distributionBarsCongruent->setAntialiased(false);

    distributionDensityBarsCongruent->setStackingGap(1);
    distributionBarsCongruent->setStackingGap(1);

    // Подготовка оси X:
    QVector<double> ticksCongruent;
    QVector<QString> labelsCongruent;

    for (size_t i = 1; i <= (size_t)vectorRegardingFrequencyCongruent.size(); i++)
    {
        ticksCongruent.push_back(i);
        labelsCongruent.push_back(tr("%1").arg(i));
    }

    QSharedPointer<QCPAxisTickerText> textTickerCongruent(new QCPAxisTickerText);
    textTickerCongruent->addTicks(ticksCongruent, labelsCongruent);

    ui->qcutomplotDensityeCongruent->xAxis->setTicker(textTickerCongruent);
    ui->qcutomplotDensityeCongruent->xAxis->setSubTicks(false);
    ui->qcutomplotDensityeCongruent->xAxis->setTickLength(0, 1);
    ui->qcutomplotDensityeCongruent->xAxis->setRange(0,
                                vectorRegardingFrequencyCongruent.size());
    ui->qcutomplotDensityeCongruent->xAxis->setBasePen(QPen(Qt::black));
    ui->qcutomplotDensityeCongruent->xAxis->setTickPen(QPen(Qt::black));
    ui->qcutomplotDensityeCongruent->xAxis->grid()->setVisible(true);
    ui->qcutomplotDensityeCongruent->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->qcutomplotDensityeCongruent->xAxis->setTickLabelColor(Qt::black);
    ui->qcutomplotDensityeCongruent->xAxis->setLabelColor(Qt::black);

    ui->qcustomplotDistributionCongruent->xAxis->setTicker(textTickerCongruent);
    ui->qcustomplotDistributionCongruent->xAxis->setSubTicks(false);
    ui->qcustomplotDistributionCongruent->xAxis->setTickLength(0, 1);
    ui->qcustomplotDistributionCongruent->xAxis->setRange(0,
                                vectorRegardingFrequencyCongruent.size());
    ui->qcustomplotDistributionCongruent->xAxis->setBasePen(QPen(Qt::black));
    ui->qcustomplotDistributionCongruent->xAxis->setTickPen(QPen(Qt::black));
    ui->qcustomplotDistributionCongruent->xAxis->grid()->setVisible(true);
    ui->qcustomplotDistributionCongruent->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->qcustomplotDistributionCongruent->xAxis->setTickLabelColor(Qt::black);
    ui->qcustomplotDistributionCongruent->xAxis->setLabelColor(Qt::black);

    // Подготовка оси Y:
    ui->qcutomplotDensityeCongruent->yAxis->setRange(0, maxRegardingFrequencyCongruent);
    ui->qcutomplotDensityeCongruent->yAxis->setPadding(1);
    ui->qcutomplotDensityeCongruent->yAxis->setBasePen(QPen(Qt::black));
    ui->qcutomplotDensityeCongruent->yAxis->setTickPen(QPen(Qt::black));
    ui->qcutomplotDensityeCongruent->yAxis->setSubTickPen(QPen(Qt::black));
    ui->qcutomplotDensityeCongruent->yAxis->grid()->setSubGridVisible(true);
    ui->qcutomplotDensityeCongruent->yAxis->setTickLabelColor(Qt::black);
    ui->qcutomplotDensityeCongruent->yAxis->setLabelColor(Qt::black);
    ui->qcutomplotDensityeCongruent->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->qcutomplotDensityeCongruent->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    ui->qcustomplotDistributionCongruent->yAxis->setRange(0, maxAccumulationFrequencyCongruent);
    ui->qcustomplotDistributionCongruent->yAxis->setPadding(1);
    ui->qcustomplotDistributionCongruent->yAxis->setBasePen(QPen(Qt::black));
    ui->qcustomplotDistributionCongruent->yAxis->setTickPen(QPen(Qt::black));
    ui->qcustomplotDistributionCongruent->yAxis->setSubTickPen(QPen(Qt::black));
    ui->qcustomplotDistributionCongruent->yAxis->grid()->setSubGridVisible(true);
    ui->qcustomplotDistributionCongruent->yAxis->setTickLabelColor(Qt::black);
    ui->qcustomplotDistributionCongruent->yAxis->setLabelColor(Qt::black);
    ui->qcustomplotDistributionCongruent->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->qcustomplotDistributionCongruent->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Добавление данных:
    QVector<double> distributionDensityDataCongruent, distributionDataCongruent;

    for (size_t i = 0; i < (size_t)vectorRegardingFrequencyCongruent.size(); i++)
    {
        distributionDensityDataCongruent << vectorRegardingFrequencyCongruent[i];
        distributionDataCongruent << vectorAccumulationFrequencyCongruent[i];
    }

    distributionDensityBarsCongruent->setData(ticksCongruent, distributionDensityDataCongruent);
    distributionBarsCongruent->setData(ticksCongruent, distributionDataCongruent);

    // Установка легенды:
    ui->qcutomplotDensityeCongruent->legend->setVisible(false);
    ui->qcutomplotDensityeCongruent->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->qcutomplotDensityeCongruent->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    ui->qcutomplotDensityeCongruent->replot();

    ui->qcustomplotDistributionCongruent->legend->setVisible(false);
    ui->qcustomplotDistributionCongruent->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->qcustomplotDistributionCongruent->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    ui->qcustomplotDistributionCongruent->replot();

    /*
     * Усовершенствованный конгруэнтный алгоритм
    */
    // Создание пустых гистограммных объектов
    QCPBars *distributionDensityBarsAdvancedCongruent = new QCPBars(ui->qcutomplotDensityeAdvancedCongruent->xAxis, ui->qcutomplotDensityeAdvancedCongruent->yAxis);
    QCPBars *distributionBarsAdvancedCongruent = new QCPBars(ui->qcustomplotDistributionAdvancedCongruent->xAxis, ui->qcustomplotDistributionAdvancedCongruent->yAxis);

    // Сглаживание
    distributionDensityBarsAdvancedCongruent->setAntialiased(false);
    distributionBarsAdvancedCongruent->setAntialiased(false);

    distributionDensityBarsAdvancedCongruent->setStackingGap(1);
    distributionBarsAdvancedCongruent->setStackingGap(1);

    // Подготовка оси X:
    QVector<double> ticksAdvancedCongruent;
    QVector<QString> labelsAdvancedCongruent;

    for (size_t i = 1; i <= (size_t)vectorRegardingFrequencyAdvancedCongruent.size(); i++)
    {
        ticksAdvancedCongruent.push_back(i);
        labelsAdvancedCongruent.push_back(tr("%1").arg(i));
    }

    QSharedPointer<QCPAxisTickerText> textTickerAdvancedCongruent(new QCPAxisTickerText);
    textTickerAdvancedCongruent->addTicks(ticksAdvancedCongruent, labelsAdvancedCongruent);

    ui->qcutomplotDensityeAdvancedCongruent->xAxis->setTicker(textTickerAdvancedCongruent);
    ui->qcutomplotDensityeAdvancedCongruent->xAxis->setSubTicks(false);
    ui->qcutomplotDensityeAdvancedCongruent->xAxis->setTickLength(0, 1);
    ui->qcutomplotDensityeAdvancedCongruent->xAxis->setRange(0,
                                vectorRegardingFrequencyAdvancedCongruent.size());
    ui->qcutomplotDensityeAdvancedCongruent->xAxis->setBasePen(QPen(Qt::black));
    ui->qcutomplotDensityeAdvancedCongruent->xAxis->setTickPen(QPen(Qt::black));
    ui->qcutomplotDensityeAdvancedCongruent->xAxis->grid()->setVisible(true);
    ui->qcutomplotDensityeAdvancedCongruent->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->qcutomplotDensityeAdvancedCongruent->xAxis->setTickLabelColor(Qt::black);
    ui->qcutomplotDensityeAdvancedCongruent->xAxis->setLabelColor(Qt::black);

    ui->qcustomplotDistributionAdvancedCongruent->xAxis->setTicker(textTickerAdvancedCongruent);
    ui->qcustomplotDistributionAdvancedCongruent->xAxis->setSubTicks(false);
    ui->qcustomplotDistributionAdvancedCongruent->xAxis->setTickLength(0, 1);
    ui->qcustomplotDistributionAdvancedCongruent->xAxis->setRange(0,
                                vectorRegardingFrequencyAdvancedCongruent.size());
    ui->qcustomplotDistributionAdvancedCongruent->xAxis->setBasePen(QPen(Qt::black));
    ui->qcustomplotDistributionAdvancedCongruent->xAxis->setTickPen(QPen(Qt::black));
    ui->qcustomplotDistributionAdvancedCongruent->xAxis->grid()->setVisible(true);
    ui->qcustomplotDistributionAdvancedCongruent->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->qcustomplotDistributionAdvancedCongruent->xAxis->setTickLabelColor(Qt::black);
    ui->qcustomplotDistributionAdvancedCongruent->xAxis->setLabelColor(Qt::black);

    // Подготовка оси Y:
    ui->qcutomplotDensityeAdvancedCongruent->yAxis->setRange(0, maxRegardingFrequencyAdvancedCongruent);
    ui->qcutomplotDensityeAdvancedCongruent->yAxis->setPadding(1);
    ui->qcutomplotDensityeAdvancedCongruent->yAxis->setBasePen(QPen(Qt::black));
    ui->qcutomplotDensityeAdvancedCongruent->yAxis->setTickPen(QPen(Qt::black));
    ui->qcutomplotDensityeAdvancedCongruent->yAxis->setSubTickPen(QPen(Qt::black));
    ui->qcutomplotDensityeAdvancedCongruent->yAxis->grid()->setSubGridVisible(true);
    ui->qcutomplotDensityeAdvancedCongruent->yAxis->setTickLabelColor(Qt::black);
    ui->qcutomplotDensityeAdvancedCongruent->yAxis->setLabelColor(Qt::black);
    ui->qcutomplotDensityeAdvancedCongruent->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->qcutomplotDensityeAdvancedCongruent->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    ui->qcustomplotDistributionAdvancedCongruent->yAxis->setRange(0, maxAccumulationFrequencyAdvancedCongruent);
    ui->qcustomplotDistributionAdvancedCongruent->yAxis->setPadding(1);
    ui->qcustomplotDistributionAdvancedCongruent->yAxis->setBasePen(QPen(Qt::black));
    ui->qcustomplotDistributionAdvancedCongruent->yAxis->setTickPen(QPen(Qt::black));
    ui->qcustomplotDistributionAdvancedCongruent->yAxis->setSubTickPen(QPen(Qt::black));
    ui->qcustomplotDistributionAdvancedCongruent->yAxis->grid()->setSubGridVisible(true);
    ui->qcustomplotDistributionAdvancedCongruent->yAxis->setTickLabelColor(Qt::black);
    ui->qcustomplotDistributionAdvancedCongruent->yAxis->setLabelColor(Qt::black);
    ui->qcustomplotDistributionAdvancedCongruent->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->qcustomplotDistributionAdvancedCongruent->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Добавление данных:
    QVector<double> distributionDensityDataAdvancedCongruent, distributionDataAdvancedCongruent;

    for (size_t i = 0; i < (size_t)vectorRegardingFrequencyAdvancedCongruent.size(); i++)
    {
        distributionDensityDataAdvancedCongruent << vectorRegardingFrequencyAdvancedCongruent[i];
        distributionDataAdvancedCongruent << vectorAccumulationFrequencyAdvancedCongruent[i];
    }

    distributionDensityBarsAdvancedCongruent->setData(ticksAdvancedCongruent, distributionDensityDataAdvancedCongruent);
    distributionBarsAdvancedCongruent->setData(ticksAdvancedCongruent, distributionDataAdvancedCongruent);

    // Установка легенды:
    ui->qcutomplotDensityeAdvancedCongruent->legend->setVisible(false);
    ui->qcutomplotDensityeAdvancedCongruent->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->qcutomplotDensityeAdvancedCongruent->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    ui->qcutomplotDensityeAdvancedCongruent->replot();

    ui->qcustomplotDistributionAdvancedCongruent->legend->setVisible(false);
    ui->qcustomplotDistributionAdvancedCongruent->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->qcustomplotDistributionAdvancedCongruent->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    ui->qcustomplotDistributionAdvancedCongruent->replot();

    /*
     * Первый алгоритм
    */
    // Создание пустых гистограммных объектов
    QCPBars *distributionDensityBarsOneAlgoritm = new QCPBars(ui->qcutomplotDensityeOneAlgoritm->xAxis, ui->qcutomplotDensityeOneAlgoritm->yAxis);
    QCPBars *distributionBarsOneAlgoritm = new QCPBars(ui->qcustomplotDistributionOneAlgoritm->xAxis, ui->qcustomplotDistributionOneAlgoritm->yAxis);

    // Сглаживание
    distributionDensityBarsOneAlgoritm->setAntialiased(false);
    distributionBarsOneAlgoritm->setAntialiased(false);

    distributionDensityBarsOneAlgoritm->setStackingGap(1);
    distributionBarsOneAlgoritm->setStackingGap(1);

    QVector<double> ticksOneAlgoritm;
    QVector<QString> labelsOneAlgoritm;

    for (size_t i = 1; i <= (size_t)vectorRegardingFrequencyOneAlgoritm.size(); i++)
    {
        ticksOneAlgoritm.push_back(i);
        labelsOneAlgoritm.push_back(tr("%1").arg(i));
    }

    QSharedPointer<QCPAxisTickerText> textTickerOneAlgoritm(new QCPAxisTickerText);
    textTickerOneAlgoritm->addTicks(ticksOneAlgoritm, labelsOneAlgoritm);

    ui->qcutomplotDensityeOneAlgoritm->xAxis->setTicker(textTickerOneAlgoritm);
    ui->qcutomplotDensityeOneAlgoritm->xAxis->setSubTicks(false);
    ui->qcutomplotDensityeOneAlgoritm->xAxis->setTickLength(0, 1);
    ui->qcutomplotDensityeOneAlgoritm->xAxis->setRange(0,
                                vectorRegardingFrequencyOneAlgoritm.size());
    ui->qcutomplotDensityeOneAlgoritm->xAxis->setBasePen(QPen(Qt::black));
    ui->qcutomplotDensityeOneAlgoritm->xAxis->setTickPen(QPen(Qt::black));
    ui->qcutomplotDensityeOneAlgoritm->xAxis->grid()->setVisible(true);
    ui->qcutomplotDensityeOneAlgoritm->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->qcutomplotDensityeOneAlgoritm->xAxis->setTickLabelColor(Qt::black);
    ui->qcutomplotDensityeOneAlgoritm->xAxis->setLabelColor(Qt::black);

    ui->qcustomplotDistributionOneAlgoritm->xAxis->setTicker(textTickerOneAlgoritm);
    ui->qcustomplotDistributionOneAlgoritm->xAxis->setSubTicks(false);
    ui->qcustomplotDistributionOneAlgoritm->xAxis->setTickLength(0, 1);
    ui->qcustomplotDistributionOneAlgoritm->xAxis->setRange(0,
                                vectorRegardingFrequencyOneAlgoritm.size());
    ui->qcustomplotDistributionOneAlgoritm->xAxis->setBasePen(QPen(Qt::black));
    ui->qcustomplotDistributionOneAlgoritm->xAxis->setTickPen(QPen(Qt::black));
    ui->qcustomplotDistributionOneAlgoritm->xAxis->grid()->setVisible(true);
    ui->qcustomplotDistributionOneAlgoritm->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->qcustomplotDistributionOneAlgoritm->xAxis->setTickLabelColor(Qt::black);
    ui->qcustomplotDistributionOneAlgoritm->xAxis->setLabelColor(Qt::black);

    // Подготовка оси Y:
    ui->qcutomplotDensityeOneAlgoritm->yAxis->setRange(0, maxRegardingFrequencyOneAlgoritm);
    ui->qcutomplotDensityeOneAlgoritm->yAxis->setPadding(1);
    ui->qcutomplotDensityeOneAlgoritm->yAxis->setBasePen(QPen(Qt::black));
    ui->qcutomplotDensityeOneAlgoritm->yAxis->setTickPen(QPen(Qt::black));
    ui->qcutomplotDensityeOneAlgoritm->yAxis->setSubTickPen(QPen(Qt::black));
    ui->qcutomplotDensityeOneAlgoritm->yAxis->grid()->setSubGridVisible(true);
    ui->qcutomplotDensityeOneAlgoritm->yAxis->setTickLabelColor(Qt::black);
    ui->qcutomplotDensityeOneAlgoritm->yAxis->setLabelColor(Qt::black);
    ui->qcutomplotDensityeOneAlgoritm->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->qcutomplotDensityeOneAlgoritm->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    ui->qcustomplotDistributionOneAlgoritm->yAxis->setRange(0, maxAccumulationFrequencyOneAlgoritm);
    ui->qcustomplotDistributionOneAlgoritm->yAxis->setPadding(1);
    ui->qcustomplotDistributionOneAlgoritm->yAxis->setBasePen(QPen(Qt::black));
    ui->qcustomplotDistributionOneAlgoritm->yAxis->setTickPen(QPen(Qt::black));
    ui->qcustomplotDistributionOneAlgoritm->yAxis->setSubTickPen(QPen(Qt::black));
    ui->qcustomplotDistributionOneAlgoritm->yAxis->grid()->setSubGridVisible(true);
    ui->qcustomplotDistributionOneAlgoritm->yAxis->setTickLabelColor(Qt::black);
    ui->qcustomplotDistributionOneAlgoritm->yAxis->setLabelColor(Qt::black);
    ui->qcustomplotDistributionOneAlgoritm->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->qcustomplotDistributionOneAlgoritm->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Добавление данных:
    QVector<double> distributionDensityDataOneAlgoritm, distributionDataOneAlgoritm;

    for (size_t i = 0; i < (size_t)vectorRegardingFrequencyOneAlgoritm.size(); i++)
    {
        distributionDensityDataOneAlgoritm << vectorRegardingFrequencyOneAlgoritm[i];
        distributionDataOneAlgoritm << vectorAccumulationFrequencyOneAlgoritm[i];
    }

    distributionDensityBarsOneAlgoritm->setData(ticksOneAlgoritm, distributionDensityDataOneAlgoritm);
    distributionBarsOneAlgoritm->setData(ticksOneAlgoritm, distributionDataOneAlgoritm);

    // Установка легенды:
    ui->qcutomplotDensityeOneAlgoritm->legend->setVisible(false);
    ui->qcutomplotDensityeOneAlgoritm->axisRect()->insetLayout()->setInsetAlignment( 0, Qt::AlignTop|Qt::AlignHCenter);
    ui->qcutomplotDensityeOneAlgoritm->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    ui->qcutomplotDensityeOneAlgoritm->replot();

    ui->qcustomplotDistributionOneAlgoritm->legend->setVisible(false);
    ui->qcustomplotDistributionOneAlgoritm->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->qcustomplotDistributionOneAlgoritm->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    ui->qcustomplotDistributionOneAlgoritm->replot();

    /*
     * Второй алгоритм
    */
    // Создание пустых гистограммных объектов
    QCPBars *distributionDensityBarsTwoAlgoritm = new QCPBars(ui->qcutomplotDensityeTwoAlgoritm->xAxis, ui->qcutomplotDensityeTwoAlgoritm->yAxis);
    QCPBars *distributionBarsTwoAlgoritm = new QCPBars(ui->qcustomplotDistributionTwoAlgoritm->xAxis, ui->qcustomplotDistributionTwoAlgoritm->yAxis);

    // Сглаживание
    distributionDensityBarsTwoAlgoritm->setAntialiased(false);
    distributionBarsTwoAlgoritm->setAntialiased(false);

    distributionDensityBarsTwoAlgoritm->setStackingGap(1);
    distributionBarsTwoAlgoritm->setStackingGap(1);

    QVector<double> ticksTwoAlgoritm;
    QVector<QString> labelsTwoAlgoritm;

    for (size_t i = 1; i <= (size_t)vectorRegardingFrequencyTwoAlgoritm.size(); i++)
    {
        ticksTwoAlgoritm.push_back(i);
        labelsTwoAlgoritm.push_back(tr("%1").arg(i));
    }

    QSharedPointer<QCPAxisTickerText> textTickerTwoAlgoritm(new QCPAxisTickerText);
    textTickerTwoAlgoritm->addTicks(ticksTwoAlgoritm, labelsTwoAlgoritm);

    ui->qcutomplotDensityeTwoAlgoritm->xAxis->setTicker(textTickerTwoAlgoritm);
    ui->qcutomplotDensityeTwoAlgoritm->xAxis->setSubTicks(false);
    ui->qcutomplotDensityeTwoAlgoritm->xAxis->setTickLength(0, 1);
    ui->qcutomplotDensityeTwoAlgoritm->xAxis->setRange(0,
                                vectorRegardingFrequencyTwoAlgoritm.size());
    ui->qcutomplotDensityeTwoAlgoritm->xAxis->setBasePen(QPen(Qt::black));
    ui->qcutomplotDensityeTwoAlgoritm->xAxis->setTickPen(QPen(Qt::black));
    ui->qcutomplotDensityeTwoAlgoritm->xAxis->grid()->setVisible(true);
    ui->qcutomplotDensityeTwoAlgoritm->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->qcutomplotDensityeTwoAlgoritm->xAxis->setTickLabelColor(Qt::black);
    ui->qcutomplotDensityeTwoAlgoritm->xAxis->setLabelColor(Qt::black);

    ui->qcustomplotDistributionTwoAlgoritm->xAxis->setTicker(textTickerTwoAlgoritm);
    ui->qcustomplotDistributionTwoAlgoritm->xAxis->setSubTicks(false);
    ui->qcustomplotDistributionTwoAlgoritm->xAxis->setTickLength(0, 1);
    ui->qcustomplotDistributionTwoAlgoritm->xAxis->setRange(0,
                                vectorRegardingFrequencyTwoAlgoritm.size());
    ui->qcustomplotDistributionTwoAlgoritm->xAxis->setBasePen(QPen(Qt::black));
    ui->qcustomplotDistributionTwoAlgoritm->xAxis->setTickPen(QPen(Qt::black));
    ui->qcustomplotDistributionTwoAlgoritm->xAxis->grid()->setVisible(true);
    ui->qcustomplotDistributionTwoAlgoritm->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->qcustomplotDistributionTwoAlgoritm->xAxis->setTickLabelColor(Qt::black);
    ui->qcustomplotDistributionTwoAlgoritm->xAxis->setLabelColor(Qt::black);

    // Подготовка оси Y:
    ui->qcutomplotDensityeTwoAlgoritm->yAxis->setRange(0, maxRegardingFrequencyTwoAlgoritm);
    ui->qcutomplotDensityeTwoAlgoritm->yAxis->setPadding(1);
    ui->qcutomplotDensityeTwoAlgoritm->yAxis->setBasePen(QPen(Qt::black));
    ui->qcutomplotDensityeTwoAlgoritm->yAxis->setTickPen(QPen(Qt::black));
    ui->qcutomplotDensityeTwoAlgoritm->yAxis->setSubTickPen(QPen(Qt::black));
    ui->qcutomplotDensityeTwoAlgoritm->yAxis->grid()->setSubGridVisible(true);
    ui->qcutomplotDensityeTwoAlgoritm->yAxis->setTickLabelColor(Qt::black);
    ui->qcutomplotDensityeTwoAlgoritm->yAxis->setLabelColor(Qt::black);
    ui->qcutomplotDensityeTwoAlgoritm->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->qcutomplotDensityeTwoAlgoritm->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    ui->qcustomplotDistributionTwoAlgoritm->yAxis->setRange(0, maxAccumulationFrequencyTwoAlgoritm);
    ui->qcustomplotDistributionTwoAlgoritm->yAxis->setPadding(1);
    ui->qcustomplotDistributionTwoAlgoritm->yAxis->setBasePen(QPen(Qt::black));
    ui->qcustomplotDistributionTwoAlgoritm->yAxis->setTickPen(QPen(Qt::black));
    ui->qcustomplotDistributionTwoAlgoritm->yAxis->setSubTickPen(QPen(Qt::black));
    ui->qcustomplotDistributionTwoAlgoritm->yAxis->grid()->setSubGridVisible(true);
    ui->qcustomplotDistributionTwoAlgoritm->yAxis->setTickLabelColor(Qt::black);
    ui->qcustomplotDistributionTwoAlgoritm->yAxis->setLabelColor(Qt::black);
    ui->qcustomplotDistributionTwoAlgoritm->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->qcustomplotDistributionTwoAlgoritm->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Добавление данных:
    QVector<double> distributionDensityDataTwoAlgoritm, distributionDataTwoAlgoritm;

    for (size_t i = 0; i < (size_t)vectorRegardingFrequencyTwoAlgoritm.size(); i++)
    {
        distributionDensityDataTwoAlgoritm << vectorRegardingFrequencyTwoAlgoritm[i];
        distributionDataTwoAlgoritm << vectorAccumulationFrequencyTwoAlgoritm[i];
    }

    distributionDensityBarsTwoAlgoritm->setData(ticksTwoAlgoritm, distributionDensityDataTwoAlgoritm);
    distributionBarsTwoAlgoritm->setData(ticksTwoAlgoritm, distributionDataTwoAlgoritm);

    // Установка легенды:
    ui->qcutomplotDensityeTwoAlgoritm->legend->setVisible(false);
    ui->qcutomplotDensityeTwoAlgoritm->axisRect()->insetLayout()->setInsetAlignment( 0, Qt::AlignTop|Qt::AlignHCenter);
    ui->qcutomplotDensityeTwoAlgoritm->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    ui->qcutomplotDensityeTwoAlgoritm->replot();

    ui->qcustomplotDistributionTwoAlgoritm->legend->setVisible(false);
    ui->qcustomplotDistributionTwoAlgoritm->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->qcustomplotDistributionTwoAlgoritm->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    ui->qcustomplotDistributionTwoAlgoritm->replot();

    /*
     * Показательное распределение
    */
    // Создание пустых гистограммных объектов
    QCPBars *distributionDensityBarsExponential = new QCPBars(ui->qcutomplotDensityeExponential->xAxis, ui->qcutomplotDensityeExponential->yAxis);
    QCPBars *distributionBarsExponential = new QCPBars(ui->qcustomplotDistributionExponential->xAxis, ui->qcustomplotDistributionExponential->yAxis);

    // Сглаживание
    distributionDensityBarsExponential->setAntialiased(false);
    distributionBarsExponential->setAntialiased(false);

    distributionDensityBarsExponential->setStackingGap(1);
    distributionBarsExponential->setStackingGap(1);

    QVector<double> ticksExponential;
    QVector<QString> labelsExponential;

    for (size_t i = 1; i <= (size_t)vectorRegardingFrequencyExponential.size(); i++)
    {
        ticksExponential.push_back(i);
        labelsExponential.push_back(tr("%1").arg(i));
    }

    QSharedPointer<QCPAxisTickerText> textTickerExponential(new QCPAxisTickerText);
    textTickerExponential->addTicks(ticksExponential, labelsExponential);

    ui->qcutomplotDensityeExponential->xAxis->setTicker(textTickerExponential);
    ui->qcutomplotDensityeExponential->xAxis->setSubTicks(false);
    ui->qcutomplotDensityeExponential->xAxis->setTickLength(0, 1);
    ui->qcutomplotDensityeExponential->xAxis->setRange(0,
                                vectorRegardingFrequencyExponential.size());
    ui->qcutomplotDensityeExponential->xAxis->setBasePen(QPen(Qt::black));
    ui->qcutomplotDensityeExponential->xAxis->setTickPen(QPen(Qt::black));
    ui->qcutomplotDensityeExponential->xAxis->grid()->setVisible(true);
    ui->qcutomplotDensityeExponential->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->qcutomplotDensityeExponential->xAxis->setTickLabelColor(Qt::black);
    ui->qcutomplotDensityeExponential->xAxis->setLabelColor(Qt::black);

    ui->qcustomplotDistributionExponential->xAxis->setTicker(textTickerExponential);
    ui->qcustomplotDistributionExponential->xAxis->setSubTicks(false);
    ui->qcustomplotDistributionExponential->xAxis->setTickLength(0, 1);
    ui->qcustomplotDistributionExponential->xAxis->setRange(0,
                                vectorRegardingFrequencyExponential.size());
    ui->qcustomplotDistributionExponential->xAxis->setBasePen(QPen(Qt::black));
    ui->qcustomplotDistributionExponential->xAxis->setTickPen(QPen(Qt::black));
    ui->qcustomplotDistributionExponential->xAxis->grid()->setVisible(true);
    ui->qcustomplotDistributionExponential->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->qcustomplotDistributionExponential->xAxis->setTickLabelColor(Qt::black);
    ui->qcustomplotDistributionExponential->xAxis->setLabelColor(Qt::black);

    // Подготовка оси Y:
    ui->qcutomplotDensityeExponential->yAxis->setRange(0, maxRegardingFrequencyExponential);
    ui->qcutomplotDensityeExponential->yAxis->setPadding(1);
    ui->qcutomplotDensityeExponential->yAxis->setBasePen(QPen(Qt::black));
    ui->qcutomplotDensityeExponential->yAxis->setTickPen(QPen(Qt::black));
    ui->qcutomplotDensityeExponential->yAxis->setSubTickPen(QPen(Qt::black));
    ui->qcutomplotDensityeExponential->yAxis->grid()->setSubGridVisible(true);
    ui->qcutomplotDensityeExponential->yAxis->setTickLabelColor(Qt::black);
    ui->qcutomplotDensityeExponential->yAxis->setLabelColor(Qt::black);
    ui->qcutomplotDensityeExponential->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->qcutomplotDensityeExponential->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    ui->qcustomplotDistributionExponential->yAxis->setRange(0, maxAccumulationFrequencyExponential);
    ui->qcustomplotDistributionExponential->yAxis->setPadding(1);
    ui->qcustomplotDistributionExponential->yAxis->setBasePen(QPen(Qt::black));
    ui->qcustomplotDistributionExponential->yAxis->setTickPen(QPen(Qt::black));
    ui->qcustomplotDistributionExponential->yAxis->setSubTickPen(QPen(Qt::black));
    ui->qcustomplotDistributionExponential->yAxis->grid()->setSubGridVisible(true);
    ui->qcustomplotDistributionExponential->yAxis->setTickLabelColor(Qt::black);
    ui->qcustomplotDistributionExponential->yAxis->setLabelColor(Qt::black);
    ui->qcustomplotDistributionExponential->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->qcustomplotDistributionExponential->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Добавление данных:
    QVector<double> distributionDensityDataExponential, distributionDataExponential;

    for (size_t i = 0; i < (size_t)vectorRegardingFrequencyExponential.size(); i++)
    {
        distributionDensityDataExponential << vectorRegardingFrequencyExponential[i];
        distributionDataExponential << vectorAccumulationFrequencyExponential[i];
    }

    distributionDensityBarsExponential->setData(ticksExponential, distributionDensityDataExponential);
    distributionBarsExponential->setData(ticksExponential, distributionDataExponential);

    // Установка легенды:
    ui->qcutomplotDensityeExponential->legend->setVisible(false);
    ui->qcutomplotDensityeExponential->axisRect()->insetLayout()->setInsetAlignment( 0, Qt::AlignTop|Qt::AlignHCenter);
    ui->qcutomplotDensityeExponential->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    ui->qcutomplotDensityeExponential->replot();

    ui->qcustomplotDistributionExponential->legend->setVisible(false);
    ui->qcustomplotDistributionExponential->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->qcustomplotDistributionExponential->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    ui->qcustomplotDistributionExponential->replot();

    /*
        Демонстрирование мамтематического ожидания и дисперсии на заглавном экране
    */
    ui->labelMatDispAdditive->setText(tr("<html><head/><body><p align='center'><span style=' font-size:10pt; font-weight:600;'>Математическое ожидание: %1</span></p><p align='center'><span style=' font-size:10pt; font-weight:600;'>Дисперсия: %2</span></p></body></html>")
                                      .arg(coreLogica->getMathematicalExpectation(1)).arg(coreLogica->getDispersion(1)));
    ui->labelMatDispCongruent->setText(tr("<html><head/><body><p align='center'><span style=' font-size:10pt; font-weight:600;'>Математическое ожидание: %1</span></p><p align='center'><span style=' font-size:10pt; font-weight:600;'>Дисперсия: %2</span></p></body></html>")
                                       .arg(coreLogica->getMathematicalExpectation(2)).arg(coreLogica->getDispersion(2)));
    ui->labelMatDispAdvancedCongruent->setText(tr("<html><head/><body><p align='center'><span style=' font-size:10pt; font-weight:600;'>Математическое ожидание: %1</span></p><p align='center'><span style=' font-size:10pt; font-weight:600;'>Дисперсия: %2</span></p></body></html>")
                                               .arg(coreLogica->getMathematicalExpectation(3)).arg(coreLogica->getDispersion(3)));
    ui->labelMatDispOneAlgoritm->setText(tr("<html><head/><body><p align='center'><span style=' font-size:10pt; font-weight:600;'>Математическое ожидание: %1</span></p><p align='center'><span style=' font-size:10pt; font-weight:600;'>Дисперсия: %2</span></p></body></html>")
                                               .arg(coreLogicaTwoLaba->getMathematicalExpectation(1)).arg(coreLogicaTwoLaba->getDispersion(1)));
    ui->labelMatDispTwoAlgoritm->setText(tr("<html><head/><body><p align='center'><span style=' font-size:10pt; font-weight:600;'>Математическое ожидание: %1</span></p><p align='center'><span style=' font-size:10pt; font-weight:600;'>Дисперсия: %2</span></p></body></html>")
                                               .arg(coreLogicaTwoLaba->getMathematicalExpectation(2)).arg(coreLogicaTwoLaba->getDispersion(2)));
    ui->labelMatDispExponential->setText(tr("<html><head/><body><p align='center'><span style=' font-size:10pt; font-weight:600;'>Математическое ожидание: %1</span></p><p align='center'><span style=' font-size:10pt; font-weight:600;'>Дисперсия: %2</span></p></body></html>")
                                               .arg(coreLogicaFiveLaba->getMathematicalExpectation()).arg(coreLogicaFiveLaba->getDispersion()));

    /*
     * Вывод данных в таблицы
    */
    // Предварительная очистка от контента
    ui->tableWidgetAdditive->clearContents();
    ui->tableWidgetCongruent->clearContents();
    ui->tableWidgetAdvancedCongruent->clearContents();
    ui->tableWidgetOneAlgoritm->clearContents();
    ui->tableWidgetTwoAlgoritm->clearContents();
    ui->tableWidgetExponential->clearContents();

    // Получение начальных и центральных моментов
    QVector<double> vectorBeginMomentAdditive = QVector<double>::fromStdVector(coreLogica->getBeginMoment(1));
    QVector<double> vectorBeginMomentCongruent = QVector<double>::fromStdVector(coreLogica->getBeginMoment(2));
    QVector<double> vectorBeginMomentAdvancedCongruent = QVector<double>::fromStdVector(coreLogica->getBeginMoment(3));
    QVector<double> vectorBeginMomentOneAlgoritm = QVector<double>::fromStdVector(coreLogicaTwoLaba->getBeginMoment(1));
    QVector<double> vectorBeginMomentTwoAlgoritm = QVector<double>::fromStdVector(coreLogicaTwoLaba->getBeginMoment(2));
    QVector<double> vectorBeginMomentExponential = QVector<double>::fromStdVector(coreLogicaFiveLaba->getBeginMoment());

    QVector<double> vectorCentralMomentAdditive = QVector<double>::fromStdVector(coreLogica->getCentralMoment(1));
    QVector<double> vectorCentralMomentCongruent = QVector<double>::fromStdVector(coreLogica->getCentralMoment(2));
    QVector<double> vectorCentralMomentAdvancedCongruent = QVector<double>::fromStdVector(coreLogica->getCentralMoment(3));
    QVector<double> vectorCentralMomentOneAlgoritm = QVector<double>::fromStdVector(coreLogicaTwoLaba->getCentralMoment(1));
    QVector<double> vectorCentralMomentTwoAlgoritm = QVector<double>::fromStdVector(coreLogicaTwoLaba->getCentralMoment(2));
    QVector<double> vectorCentralMomentExponential = QVector<double>::fromStdVector(coreLogicaFiveLaba->getCentralMoment());

    // Получение случайных чисел
    QVector<double> vectorValueGenerateAdditive = QVector<double>::fromStdVector(coreLogica->getVectorValueGenerate(1));
    QVector<double> vectorValueGenerateCongruent = QVector<double>::fromStdVector(coreLogica->getVectorValueGenerate(2));
    QVector<double> vectorValueGenerateAdvancedCongruent = QVector<double>::fromStdVector(coreLogica->getVectorValueGenerate(3));
    QVector<double> vectorValueGenerateOneAlgoritm = QVector<double>::fromStdVector(coreLogicaTwoLaba->getVectorValueGenerate(1));
    QVector<double> vectorValueGenerateTwoAlgoritm = QVector<double>::fromStdVector(coreLogicaTwoLaba->getVectorValueGenerate(2));
    QVector<double> vectorValueGenerateExponential = QVector<double>::fromStdVector(coreLogicaFiveLaba->getVectorValueGenerate());

    // Определение максимального количества элементов
    int maxCountRowAdditive = (vectorValueGenerateAdditive.size() > 10) ? (vectorValueGenerateAdditive.size()) : (10);
    int maxCountRowCongruent = (vectorValueGenerateCongruent.size() > 10) ? (vectorValueGenerateCongruent.size()) : (10);
    int maxCountRowAdvancedCongruent = (vectorValueGenerateAdvancedCongruent.size() > 10) ? (vectorValueGenerateAdvancedCongruent.size()) : (10);
    int maxCountRowOneAlgoritm = (vectorValueGenerateOneAlgoritm.size() > 100) ? (vectorValueGenerateOneAlgoritm.size()) : (100);
    int maxCountRowTwoAlgoritm = (vectorValueGenerateTwoAlgoritm.size() > 100) ? (vectorValueGenerateTwoAlgoritm.size()) : (100);
    int maxCountRowExponential = (vectorValueGenerateExponential.size() > 100) ? (vectorValueGenerateExponential.size()) : (100);

    // Установка количества строк у таблиц
    ui->tableWidgetAdditive->setRowCount(maxCountRowAdditive);
    ui->tableWidgetCongruent->setRowCount(maxCountRowCongruent);
    ui->tableWidgetAdvancedCongruent->setRowCount(maxCountRowAdvancedCongruent);
    ui->tableWidgetOneAlgoritm->setRowCount(maxCountRowOneAlgoritm);
    ui->tableWidgetTwoAlgoritm->setRowCount(maxCountRowTwoAlgoritm);
    ui->tableWidgetExponential->setRowCount(maxCountRowExponential);

    /*
     * Заполнение таблиц
    */
    /*
        Для аддитивного алгоритма
    */
    for (size_t i = 0; i < (size_t)vectorRegardingFrequencyAdditive.size(); i++)
    {
        // Относительная частота
        QTableWidgetItem *newItemOne = new QTableWidgetItem(tr("%1")
                        .arg(vectorRegardingFrequencyAdditive[i]));
        ui->tableWidgetAdditive->setItem(i, 0, newItemOne);

        // Накопленная частота
        QTableWidgetItem *newItemTwo = new QTableWidgetItem(tr("%1")
                        .arg(vectorAccumulationFrequencyAdditive[i]));
        ui->tableWidgetAdditive->setItem(i, 1, newItemTwo);
    }

    // Математическое ожидание
    QTableWidgetItem *newItemThree = new QTableWidgetItem(tr("%1")
                    .arg(coreLogica->getMathematicalExpectation(1)));
    ui->tableWidgetAdditive->setItem(0, 2, newItemThree);

    // Дисперсия
    QTableWidgetItem *newItemFour = new QTableWidgetItem(tr("%1")
                    .arg(coreLogica->getDispersion(1)));
    ui->tableWidgetAdditive->setItem(0, 3, newItemFour);

    // Начальные моменты
    for (size_t i = 0; i < (size_t)vectorBeginMomentAdditive.size(); i++)
    {
        QTableWidgetItem *newItemFive = new QTableWidgetItem(tr("%1")
                        .arg(vectorBeginMomentAdditive[i]));
        ui->tableWidgetAdditive->setItem(i, 4, newItemFive);
    }

    // Центральные моменты
    for (size_t i = 0; i < (size_t)vectorCentralMomentAdditive.size(); i++)
    {
        QTableWidgetItem *newItemSix = new QTableWidgetItem(tr("%1")
                        .arg(vectorCentralMomentAdditive[i]));
        ui->tableWidgetAdditive->setItem(i, 5, newItemSix);
    }

    // Случайные числа
    for (size_t i = 0; i < (size_t)vectorValueGenerateAdditive.size(); i++)
    {
        QTableWidgetItem *newItemSeven = new QTableWidgetItem(tr("%1")
                        .arg(vectorValueGenerateAdditive[i]));
        ui->tableWidgetAdditive->setItem(i, 6, newItemSeven);
    }

    /*
        Для конгруэнтного алгоритма
    */
    for (size_t i = 0; i < (size_t)vectorRegardingFrequencyCongruent.size(); i++)
    {
        // Относительная частота
        QTableWidgetItem *newItemOne = new QTableWidgetItem(tr("%1")
                        .arg(vectorRegardingFrequencyCongruent[i]));
        ui->tableWidgetCongruent->setItem(i, 0, newItemOne);

        // Накопленная частота
        QTableWidgetItem *newItemTwo = new QTableWidgetItem(tr("%1")
                        .arg(vectorAccumulationFrequencyCongruent[i]));
        ui->tableWidgetCongruent->setItem(i, 1, newItemTwo);
    }

    // Математическое ожидание
    newItemThree = new QTableWidgetItem(tr("%1")
                    .arg(coreLogica->getMathematicalExpectation(2)));
    ui->tableWidgetCongruent->setItem(0, 2, newItemThree);

    // Дисперсия
    newItemFour = new QTableWidgetItem(tr("%1")
                    .arg(coreLogica->getDispersion(2)));
    ui->tableWidgetCongruent->setItem(0, 3, newItemFour);

    // Начальные моменты
    for (size_t i = 0; i < (size_t)vectorBeginMomentCongruent.size(); i++)
    {
        QTableWidgetItem *newItemFive = new QTableWidgetItem(tr("%1")
                        .arg(vectorBeginMomentCongruent[i]));
        ui->tableWidgetCongruent->setItem(i, 4, newItemFive);
    }

    // Центральные моменты
    for (size_t i = 0; i < (size_t)vectorCentralMomentCongruent.size(); i++)
    {
        QTableWidgetItem *newItemSix = new QTableWidgetItem(tr("%1")
                        .arg(vectorCentralMomentCongruent[i]));
        ui->tableWidgetCongruent->setItem(i, 5, newItemSix);
    }

    // Случайные числа
    for (size_t i = 0; i < (size_t)vectorValueGenerateCongruent.size(); i++)
    {
        QTableWidgetItem *newItemSeven = new QTableWidgetItem(tr("%1")
                        .arg(vectorValueGenerateCongruent[i]));
        ui->tableWidgetCongruent->setItem(i, 6, newItemSeven);
    }

    /*
        Для усовершенствованного конгруэнтного алгоритма
    */
    for (size_t i = 0; i < (size_t)vectorRegardingFrequencyAdvancedCongruent.size(); i++)
    {
        // Относительная частота
        QTableWidgetItem *newItemOne = new QTableWidgetItem(tr("%1")
                        .arg(vectorRegardingFrequencyAdvancedCongruent[i]));
        ui->tableWidgetAdvancedCongruent->setItem(i, 0, newItemOne);

        // Накопленная частота
        QTableWidgetItem *newItemTwo = new QTableWidgetItem(tr("%1")
                        .arg(vectorAccumulationFrequencyAdvancedCongruent[i]));
        ui->tableWidgetAdvancedCongruent->setItem(i, 1, newItemTwo);
    }

    // Математическое ожидание
    newItemThree = new QTableWidgetItem(tr("%1")
                    .arg(coreLogica->getMathematicalExpectation(3)));
    ui->tableWidgetAdvancedCongruent->setItem(0, 2, newItemThree);

    // Дисперсия
    newItemFour = new QTableWidgetItem(tr("%1")
                    .arg(coreLogica->getDispersion(3)));
    ui->tableWidgetAdvancedCongruent->setItem(0, 3, newItemFour);

    // Начальные моменты
    for (size_t i = 0; i < (size_t)vectorBeginMomentAdvancedCongruent.size(); i++)
    {
        QTableWidgetItem *newItemFive = new QTableWidgetItem(tr("%1")
                        .arg(vectorBeginMomentAdvancedCongruent[i]));
        ui->tableWidgetAdvancedCongruent->setItem(i, 4, newItemFive);
    }

    // Центральные моменты
    for (size_t i = 0; i < (size_t)vectorCentralMomentAdvancedCongruent.size(); i++)
    {
        QTableWidgetItem *newItemSix = new QTableWidgetItem(tr("%1")
                        .arg(vectorCentralMomentAdvancedCongruent[i]));
        ui->tableWidgetAdvancedCongruent->setItem(i, 5, newItemSix);
    }

    // Случайные числа
    for (size_t i = 0; i < (size_t)vectorValueGenerateAdvancedCongruent.size(); i++)
    {
        QTableWidgetItem *newItemSeven = new QTableWidgetItem(tr("%1")
                        .arg(vectorValueGenerateAdvancedCongruent[i]));
        ui->tableWidgetAdvancedCongruent->setItem(i, 6, newItemSeven);
    }

    /*
        Для первого алгоритма
    */
    for (size_t i = 0; i < (size_t)vectorRegardingFrequencyOneAlgoritm.size(); i++)
    {
        // Относительная частота
        QTableWidgetItem *newItemOne = new QTableWidgetItem(tr("%1")
                        .arg(vectorRegardingFrequencyOneAlgoritm[i]));
        ui->tableWidgetOneAlgoritm->setItem(i, 0, newItemOne);

        // Накопленная частота
        QTableWidgetItem *newItemTwo = new QTableWidgetItem(tr("%1")
                        .arg(vectorAccumulationFrequencyOneAlgoritm[i]));
        ui->tableWidgetOneAlgoritm->setItem(i, 1, newItemTwo);
    }

    // Математическое ожидание
    newItemThree = new QTableWidgetItem(tr("%1")
                    .arg(coreLogicaTwoLaba->getMathematicalExpectation(1)));
    ui->tableWidgetOneAlgoritm->setItem(0, 2, newItemThree);

    // Дисперсия
    newItemFour = new QTableWidgetItem(tr("%1")
                    .arg(coreLogicaTwoLaba->getDispersion(1)));
    ui->tableWidgetOneAlgoritm->setItem(0, 3, newItemFour);

    // Начальные моменты
    for (size_t i = 0; i < (size_t)vectorBeginMomentOneAlgoritm.size(); i++)
    {
        QTableWidgetItem *newItemFive = new QTableWidgetItem(tr("%1")
                        .arg(vectorBeginMomentOneAlgoritm[i]));
        ui->tableWidgetOneAlgoritm->setItem(i, 4, newItemFive);
    }

    // Центральные моменты
    for (size_t i = 0; i < (size_t)vectorCentralMomentOneAlgoritm.size(); i++)
    {
        QTableWidgetItem *newItemSix = new QTableWidgetItem(tr("%1")
                        .arg(vectorCentralMomentOneAlgoritm[i]));
        ui->tableWidgetOneAlgoritm->setItem(i, 5, newItemSix);
    }

    // Случайные числа
    for (size_t i = 0; i < (size_t)vectorValueGenerateOneAlgoritm.size(); i++)
    {
        QTableWidgetItem *newItemSeven = new QTableWidgetItem(tr("%1")
                        .arg(vectorValueGenerateOneAlgoritm[i]));
        ui->tableWidgetOneAlgoritm->setItem(i, 6, newItemSeven);
    }

    /*
        Для второго алгоритма
    */
    for (size_t i = 0; i < (size_t)vectorRegardingFrequencyTwoAlgoritm.size(); i++)
    {
        // Относительная частота
        QTableWidgetItem *newItemOne = new QTableWidgetItem(tr("%1")
                        .arg(vectorRegardingFrequencyTwoAlgoritm[i]));
        ui->tableWidgetTwoAlgoritm->setItem(i, 0, newItemOne);

        // Накопленная частота
        QTableWidgetItem *newItemTwo = new QTableWidgetItem(tr("%1")
                        .arg(vectorAccumulationFrequencyTwoAlgoritm[i]));
        ui->tableWidgetTwoAlgoritm->setItem(i, 1, newItemTwo);
    }

    // Математическое ожидание
    newItemThree = new QTableWidgetItem(tr("%1")
                    .arg(coreLogicaTwoLaba->getMathematicalExpectation(2)));
    ui->tableWidgetTwoAlgoritm->setItem(0, 2, newItemThree);

    // Дисперсия
    newItemFour = new QTableWidgetItem(tr("%1")
                    .arg(coreLogicaTwoLaba->getDispersion(2)));
    ui->tableWidgetTwoAlgoritm->setItem(0, 3, newItemFour);

    // Начальные моменты
    for (size_t i = 0; i < (size_t)vectorBeginMomentTwoAlgoritm.size(); i++)
    {
        QTableWidgetItem *newItemFive = new QTableWidgetItem(tr("%1")
                        .arg(vectorBeginMomentTwoAlgoritm[i]));
        ui->tableWidgetTwoAlgoritm->setItem(i, 4, newItemFive);
    }

    // Центральные моменты
    for (size_t i = 0; i < (size_t)vectorCentralMomentTwoAlgoritm.size(); i++)
    {
        QTableWidgetItem *newItemSix = new QTableWidgetItem(tr("%1")
                        .arg(vectorCentralMomentTwoAlgoritm[i]));
        ui->tableWidgetTwoAlgoritm->setItem(i, 5, newItemSix);
    }

    // Случайные числа
    for (size_t i = 0; i < (size_t)vectorValueGenerateTwoAlgoritm.size(); i++)
    {
        QTableWidgetItem *newItemSeven = new QTableWidgetItem(tr("%1")
                        .arg(vectorValueGenerateTwoAlgoritm[i]));
        ui->tableWidgetTwoAlgoritm->setItem(i, 6, newItemSeven);
    }

    /*
        Для показательного распределения
    */
    for (size_t i = 0; i < (size_t)vectorRegardingFrequencyExponential.size(); i++)
    {
        // Относительная частота
        QTableWidgetItem *newItemOne = new QTableWidgetItem(tr("%1")
                        .arg(vectorRegardingFrequencyExponential[i]));
        ui->tableWidgetExponential->setItem(i, 0, newItemOne);

        // Накопленная частота
        QTableWidgetItem *newItemTwo = new QTableWidgetItem(tr("%1")
                        .arg(vectorAccumulationFrequencyExponential[i]));
        ui->tableWidgetExponential->setItem(i, 1, newItemTwo);
    }

    // Математическое ожидание
    newItemThree = new QTableWidgetItem(tr("%1")
                    .arg(coreLogicaFiveLaba->getMathematicalExpectation()));
    ui->tableWidgetExponential->setItem(0, 2, newItemThree);

    // Дисперсия
    newItemFour = new QTableWidgetItem(tr("%1")
                    .arg(coreLogicaFiveLaba->getDispersion()));
    ui->tableWidgetExponential->setItem(0, 3, newItemFour);

    // Начальные моменты
    for (size_t i = 0; i < (size_t)vectorBeginMomentExponential.size(); i++)
    {
        QTableWidgetItem *newItemFive = new QTableWidgetItem(tr("%1")
                        .arg(vectorBeginMomentExponential[i]));
        ui->tableWidgetExponential->setItem(i, 4, newItemFive);
    }

    // Центральные моменты
    for (size_t i = 0; i < (size_t)vectorCentralMomentExponential.size(); i++)
    {
        QTableWidgetItem *newItemSix = new QTableWidgetItem(tr("%1")
                        .arg(vectorCentralMomentExponential[i]));
        ui->tableWidgetExponential->setItem(i, 5, newItemSix);
    }

    // Случайные числа
    for (size_t i = 0; i < (size_t)vectorValueGenerateExponential.size(); i++)
    {
        QTableWidgetItem *newItemSeven = new QTableWidgetItem(tr("%1")
                        .arg(vectorValueGenerateExponential[i]));
        ui->tableWidgetExponential->setItem(i, 6, newItemSeven);
    }
}

// Принятие данных и отправка на обработку
void MainWindow::updateData()
{
    /*
     * Загрузка данных
    */

    // Начала отрезка Begin
    coreLogica->setBegin(ui->doubleSpinBoxValueBegin->value());

    // Конец отрезка End
    coreLogica->setEnd(ui->doubleSpinBoxValueEnd->value());

    // Величины для усовершенствованного конгруэнтного алгоритма
    coreLogica->setValueABCD(ui->spinBoxValueA->value(), ui->spinBoxValueB->value(),
                             ui->spinBoxValueC->value(), ui->spinBoxValueD->value());

    // Количество случайных чисел
    coreLogica->setCountGenerateNumber(ui->spinBoxValueN->value());
    coreLogicaTwoLaba->setCountGenerateNumber(ui->spinBoxValueNTwoLaba->value());
    coreLogicaFiveLaba->setCountGenerateNumber(ui->spinBoxValueNFiveLaba->value());

    // Максимальные степени моментов
    coreLogica->setBeginAndCentralMomentPower(ui->spinBoxMaxPowerBeginMoment->value(), ui->spinBoxMaxPowerCentralMoment->value());
    coreLogicaTwoLaba->setBeginAndCentralMomentPower(ui->spinBoxMaxPowerBeginMomentTwoLaba->value(),
                                                     ui->spinBoxMaxPowerCentralMomentTwoLaba->value());
    coreLogicaFiveLaba->setBeginAndCentralMomentPower(ui->spinBoxMaxPowerBeginMomentFiveLaba->value(),
                                                      ui->spinBoxMaxPowerCentralMomentFiveLaba->value());

    // Специальные параметры
    coreLogicaTwoLaba->setSpecBlock(ui->doubleSpinBoxMat->value(), ui->doubleSpinBoxDisp->value());

    // Параметр лямбда для показательного распределения
    coreLogicaFiveLaba->setLambda(ui->doubleSpinBoxLambda->value());
}

// Генерирование
void MainWindow::generateData()
{
    updateData();

    // Запрос на вычисления
    coreLogica->calculateMain();
    coreLogicaTwoLaba->calculateMain();
    coreLogicaFiveLaba->calculateMain();

    // Передача данных из логики в интерфейс для построения
    treatmentData();

    // Уведомление в строке состояния
    ui->statusBar->showMessage(tr("Вычисления законченны"), 2000);
}

// Вызов информации об Qt
void MainWindow::on_action_Qt_triggered()
{
    qApp->aboutQt();
}

// Вызов информации об авторе
void MainWindow::on_action_autor_triggered()
{
    dialogAboutAutor->setVisible(true);
    dialogAboutAutor->show();
}

// Вызов действия генерации чисел
void MainWindow::on_action_generate_triggered()
{
    generateData();
}
