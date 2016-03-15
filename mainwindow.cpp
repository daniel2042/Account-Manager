#include "mainwindow.h"



MainWindow::MainWindow()
{

    value = 0;

    this->setFixedSize(500,600);
    this->setWindowIcon(QIcon("/home/dmajchrz/Konto/icon.png"));

    tab = new QTabWidget(this);
    tab->setGeometry(10,10,480,520);



    add = new QPushButton(this);
    add->setGeometry(220,10,60,30);
    add->setText("Dodaj");

    list = new QTableWidget(this);
    list->setGeometry(10,60,480,500);
    list->setColumnCount(4);
    list->setColumnWidth(0,140);
    list->setColumnWidth(1,100);
    list->setColumnWidth(2,100);
    list->setColumnWidth(3,130);
    list->setHorizontalHeaderItem(0, new QTableWidgetItem("Nazwa"));
    list->setHorizontalHeaderItem(1, new QTableWidgetItem("Cena" ));
    list->setHorizontalHeaderItem(2, new QTableWidgetItem("Typ"  ));
    list->setHorizontalHeaderItem(3, new QTableWidgetItem("Data"  ));
    list->verticalHeader()->setVisible(false);
    list->setEditTriggers(QAbstractItemView::NoEditTriggers);


    cash_label = new QLabel(this);
    cash_label->setGeometry(10,570,100,20);
    cash_label->setText("Stan konta: ");

    Load();
    Calculate();

    cash = new QLabel(this);
    cash->setGeometry(100,570,85,20);
    cash->setText(QString::number(value));

    filter = new QLineEdit(this);
    filter->setGeometry(10,540,480,20);



    outs_pie = new QPieSeries();
    ins_pie = new QPieSeries();


    QChart *outs_chart = new QChart();
    outs_chart->addSeries(outs_pie);
    outs_chart->setTitle("Wydatki");
    outs_chart->legend()->hide();


   QChartView *out_chart_view = new QChartView(outs_chart);
   out_chart_view->setRenderHint(QPainter::Antialiasing);



   QChart *ins_chart = new QChart();
   ins_chart->addSeries(ins_pie);
   ins_chart->setTitle("Przychody");
   ins_chart->legend()->hide();


  QChartView *in_chart_view = new QChartView(ins_chart);
  in_chart_view->setRenderHint(QPainter::Antialiasing);




    Chart_Update();


    Add_Window = new QAdd();

    tab->addTab(list,"Spis");
    tab->addTab(out_chart_view,"Wydatki");
    tab->addTab(in_chart_view,"Przychody");
    connect(add,SIGNAL(clicked(bool)), this, SLOT(Add()));
    connect(Add_Window, SIGNAL(Finish()),this,SLOT(Add_Close()));
    connect(filter, SIGNAL(textEdited(QString)), this, SLOT(Edit(QString)));
}

void MainWindow::Add()
{
    Add_Window->name->setText("");
    Add_Window->price->setText("");
    Add_Window->type->setCurrentIndex(0);
    Add_Window->show();
}

void MainWindow::Load()
{
    QString str;
    int i = 0;
    char tmp[128] = {0};
    QFile file("./spis.bil");
    file.open(QIODevice::ReadOnly);


    for(int i = 0; i < list->rowCount();)
        list->removeRow(i);


    while(!file.atEnd())
    {
        unsigned int index = list->rowCount();

        list->insertRow(index);
        list->setRowHeight(index, 20);


        for(int j = 0; j < 4; j++)
        {
            file.readLine(tmp,128);
            str.fromLocal8Bit(tmp);

            QTableWidgetItem *x  = new QTableWidgetItem(tmp);

            list->setItem(i, j,x);
        }
        i++;
    }
    file.close();










}
void MainWindow::Add_Close()
{

    QDate data = QDate::currentDate();
    Load();
    filter->setText("");
    unsigned int index = list->rowCount();
    list->insertRow(index);
    list->setRowHeight(index, 20);


    QTableWidgetItem *name  = new QTableWidgetItem(Add_Window->name->text() + "\n");
    QTableWidgetItem *price = new QTableWidgetItem(Add_Window->price->text() + "\n");
    QTableWidgetItem *type  = new QTableWidgetItem(Add_Window->type->itemText(Add_Window->type->currentIndex()) + "\n");
    QTableWidgetItem *date  = new QTableWidgetItem(data.toString("dd.MM.yyyy") + "\n");



    list->setItem(index, 0,name);
    list->setItem(index, 1,price);
    list->setItem(index, 2,type);
    list->setItem(index, 3,date);

    Calculate();
    Chart_Update();
    cash->setText(QString::number(value));
    Save();
}

void MainWindow::Chart_Update()
{
    float Jedzenie = 0;
    float Alkohol  = 0;
    float Elektronika = 0;
    float Obiad = 0;
    float Praca = 0;
    float Pociag = 0;
    float MPK = 0;
    float Ksiazki = 0;
    float Kamila = 0;
    float Inne = 0;
    float Wplata = 0;
    float Zwrot = 0;
    float Rodzice = 0;

    int index = 0;

   for(int i = 0; i < list->rowCount(); i++)
    {
         if(list->item(i,2)->text() == "Jedzenie\n")
             Jedzenie += list->item(i,1)->text().toFloat();
         if(list->item(i,2)->text() == "Alkohol\n")
             Alkohol += list->item(i,1)->text().toFloat();
         if(list->item(i,2)->text() == "Elektronika\n")
             Elektronika += list->item(i,1)->text().toFloat();
         if(list->item(i,2)->text() == "Obiad\n")
             Obiad += list->item(i,1)->text().toFloat();
         if(list->item(i,2)->text() == "Praca\n")
             Praca += list->item(i,1)->text().toFloat();
         if(list->item(i,2)->text() == "Inne\n")
             Inne += list->item(i,1)->text().toFloat();
         if(list->item(i,2)->text() == "Pociag\n")
             Pociag += list->item(i,1)->text().toFloat();
         if(list->item(i,2)->text() == "MPK\n")
             MPK += list->item(i,1)->text().toFloat();
         if(list->item(i,2)->text() == "Ksiazki\n")
             Ksiazki += list->item(i,1)->text().toFloat();
         if(list->item(i,2)->text() == "Kamila\n")
             Kamila += list->item(i,1)->text().toFloat();


         if(list->item(i,2)->text() == "Wyplata\n")
             Wplata += list->item(i,1)->text().toFloat();
         if(list->item(i,2)->text() == "Zwrot\n")
             Zwrot += list->item(i,1)->text().toFloat();
         if(list->item(i,2)->text() == "Rodzice\n")
             Rodzice += list->item(i,1)->text().toFloat();


    }


    outs_pie->clear();
    ins_pie ->clear();



    if(Jedzenie > 0)
    {
        outs_pie->append("Jedzenie", Jedzenie);
        outs_pie->slices().at(index)->setLabelVisible();
        outs_pie->slices().at(index)->setBrush(Qt::green);
        index++;
    }
    if(Alkohol > 0)
    {
        outs_pie->append("Alkohol", Alkohol);
        outs_pie->slices().at(index)->setLabelVisible();
        outs_pie->slices().at(index)->setBrush(Qt::cyan);
        index++;
    }
    if(Kamila > 0)
    {
        outs_pie->append("Kamila", Kamila);
        outs_pie->slices().at(index)->setLabelVisible();
        outs_pie->slices().at(index)->setBrush(QColor::fromRgb(0xFF, 0x33, 0x99));
        index++;
    }
    if(Elektronika > 0)
    {
        outs_pie->append("Elektronika", Elektronika);
        outs_pie->slices().at(index)->setLabelVisible();
        outs_pie->slices().at(index)->setBrush(QColor::fromRgb(0xFF, 0x33, 0x33));
        index++;
    }
    if(Obiad > 0)
    {
        outs_pie->append("Obiad", Obiad);
        outs_pie->slices().at(index)->setLabelVisible();
        outs_pie->slices().at(index)->setBrush(Qt::gray);
        index++;
    }
    if(Praca > 0)
    {
        outs_pie->append("Praca", Praca);
        outs_pie->slices().at(index)->setLabelVisible();
        outs_pie->slices().at(index)->setBrush(Qt::yellow);
        index++;
    }
    if(MPK > 0)
    {
        outs_pie->append("MPK", MPK);
        outs_pie->slices().at(index)->setLabelVisible();
        outs_pie->slices().at(index)->setBrush(Qt::darkMagenta);
        index++;
    }
    if(Ksiazki > 0)
    {
        outs_pie->append("Ksiazki", Ksiazki);
        outs_pie->slices().at(index)->setLabelVisible();
        outs_pie->slices().at(index)->setBrush(Qt::darkBlue);
        index++;
    }
    if(Pociag > 0)
    {
        outs_pie->append("Pociag", Pociag);
        outs_pie->slices().at(index)->setLabelVisible();
        outs_pie->slices().at(index)->setBrush(Qt::yellow);
        index++;
    }
    if(Inne > 0)
    {
        outs_pie->append("Inne", Inne);
        outs_pie->slices().at(index)->setLabelVisible();
        outs_pie->slices().at(index)->setBrush(Qt::black);
        index++;
    }

    index = 0;
    if(Wplata > 0)
    {
        ins_pie->append("Wyplata", Wplata);
        ins_pie->slices().at(index)->setLabelVisible();
        ins_pie->slices().at(index)->setBrush(Qt::green);
        index++;
    }
    if(Zwrot > 0)
    {
        ins_pie->append("Zwrot", Zwrot);
        ins_pie->slices().at(index)->setLabelVisible();
        ins_pie->slices().at(index)->setBrush(Qt::cyan);
        index++;
    }
    if(Rodzice > 0)
    {
        ins_pie->append("Rodzice", Rodzice);
        ins_pie->slices().at(index)->setLabelVisible();
        ins_pie->slices().at(index)->setBrush(Qt::red);
        index++;
    }

}
void MainWindow::Calculate()
{

    value = 0;
    for(int i = 0; i < list->rowCount(); i++)
    {
        if(list->item(i,2)->text() == "Wyplata\n" || list->item(i,2)->text() == "Zwrot\n" || list->item(i,2)->text() == "Rodzice\n")
        {
           value += list->item(i,1)->text().toFloat();
        }
        else
        {
           value -= list->item(i,1)->text().toFloat();
        }
    }

}

void MainWindow::Edit(QString str)
{
    QMessageBox m;
    float tmp = 0;

    Load();

    for(int i = 0; i < list->rowCount();)
        if(list->item(i,2)->text().toStdString().find(str.toStdString().c_str()) > 0 && list->item(i,0)->text().toStdString().find(str.toStdString().c_str()) > 0)
        {
            list->removeRow(i);
        }
        else
            i++;
    Calculate();

    if(str.isEmpty() == true)
    {
        cash_label->setText("Stan konta");
    }
    else
        cash_label->setText("Suma");

    for(int i = 0; i < list->rowCount(); i++)
    {
      tmp += list->item(i,1)->text().toFloat();
    }


    cash->setText(QString::number(tmp));
}

void MainWindow::Save()
{
    //Load();
    QFile file("./spis.bil");
    file.open(QIODevice::WriteOnly);

    for(int i = 0; i < list->rowCount(); i++)
    {
        for(int j = 0; j < 4; j++)
        {
            file.write(list->item(i,j)->text().toStdString().c_str());

        }
    }

    file.close();
}
MainWindow::~MainWindow()
{
    Load();
    Save();
}

