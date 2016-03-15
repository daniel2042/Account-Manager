#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QTabWidget>
#include <QHeaderView>
#include <QDate>
#include <QLabel>
#include <QFile>
#include <QLineEdit>
#include <QColor>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QAbstractItemModel>
#include <QSortFilterProxyModel>
#include "add.h"

using namespace QtCharts;
QT_CHARTS_USE_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

    QPushButton* add;
    QTableWidget*  list;
    QTabWidget* tab;
    QLabel* cash_label;
    QLabel* cash;
    QLineEdit* filter;
    QAbstractItemModel* model;
    float value;

    QAdd* Add_Window;
    QPieSeries* outs_pie;
    QPieSeries* ins_pie;
    void Calculate();
    void Load();
    void Chart_Update();
    void Save();

public slots:
   void Add();
   void Add_Close();
   void Edit(QString);
};

#endif // MAINWINDOW_H
