#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QChart>
#include <QChartView>
#include <QLineSeries>

#include "src/qtchartium/chartiumchart.h"
#include "src/qtchartium/chartiumview.h"
#include "src/qtchartium/charts/linechart/chartiumlineseries.h"



MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createQtChart();
    qCritical() << "";
    qCritical() << "##########################################################################";
    qCritical() << "";
    createChartiumChart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createChartiumChart()
{
    ChartiumView* view = new ChartiumView(this);

    ChartiumLineSeries* series = new ChartiumLineSeries();

    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);
    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

    ChartiumChart* chart = new ChartiumChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Simple Line Chart");

    view->setChart(chart);
    view->setRenderHint(QPainter::Antialiasing);

    ui->chartiumLayout->addWidget(view);
}

void MainWindow::createQtChart()
{
    QChartView* view = new QChartView(this);

    QLineSeries* series = new QLineSeries();

    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);
    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

    QChart* chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Simple Line Chart");

    view->setChart(chart);
    view->setRenderHint(QPainter::Antialiasing);

    ui->qtChartsLayout->addWidget(view);
}
