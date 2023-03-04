#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    createChart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createChart()
{
    QChartView *chartView = new QChartView(this);
    QChart *chart = new QChart();
    
    chart->setTitle("简单函数曲线");
    chartView->setChart(chart);
    this->setCentralWidget(chartView);
    
    // 创建折线序列
    QLineSeries *series0 = new QLineSeries();
    QLineSeries *series1 = new QLineSeries();
    
    series0->setName("Sin曲线");
    series1->setName("Cos曲线");
    
    chart->addSeries(series0);
    chart->addSeries(series1);
    
    // 序列添加数值
    float t = 0, y1, y2, intv = 0.1;
    int cnt = 100;
    std::vector<float> tVec;
    tVec.push_back(35.2);
    tVec.push_back(60.2);
    tVec.push_back(25.2);
    tVec.push_back(56.2);
    tVec.push_back(78.2);
    tVec.push_back(89.2);
    tVec.push_back(28.2);
    tVec.push_back(77.2);
    tVec.push_back(79.2);
    tVec.push_back(65.2);
    //for (int i = 0; i < cnt; ++i)
    for(int i = 0; i < tVec.size(); ++i)
    {
        series0->append(i, tVec[i]);
        
//        y1 = qSin(t);
//        series0->append(t, y1);
//        y2 = qSin(t + 20);
//        series1->append(t, y2);
//        t += intv;
    }
    
    // 创建坐标轴
    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(0, tVec.size());
    axisX->setTitleText("time(secs)");
    
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(20, 100);
    axisY->setTitleText("value");
    
    chart->setAxisX(axisX, series0);
    chart->setAxisY(axisY, series0);
//    chart->setAxisX(axisX, series1);
//    chart->setAxisY(axisY, series1);
}
