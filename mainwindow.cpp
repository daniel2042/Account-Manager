#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    this->setFixedSize(400,500);

    tab = new QTabWidget(this);
    tab->setGeometry(10,10,380,480);



    add = new QPushButton(this);
    add->setGeometry(20,20,60,20);
    add->setText("Add");

    list = new QTableWidget(this);
    list->setGeometry(20,60,360,420);
    list->setColumnCount(2);
    list->setColumnWidth(0,250);
    list->setColumnWidth(1,108);
    list->setHorizontalHeaderItem(0, new QTableWidgetItem("Nazwa"));
    list->setHorizontalHeaderItem(1, new QTableWidgetItem("Cena" ));

    QWidget widget;


    tab->addTab(add,"Ogol");
    tab->addTab(list,"Add");

    connect(add,SIGNAL(clicked(bool)), this, SLOT(Add()));
}

void MainWindow::Add()
{
    list->insertRow(list->rowCount());
    QTableWidgetItem *newItem = new QTableWidgetItem(QString::number(list->rowCount()));
    list->setItem(list->rowCount()-1,0,newItem);
}

MainWindow::~MainWindow()
{

}
