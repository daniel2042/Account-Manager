#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QTabWidget>
#include <QPieCharts>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QPushButton* add;
    QTableWidget*  list;
    QTabWidget* tab;

public slots:
   void Add();
};

#endif // MAINWINDOW_H
