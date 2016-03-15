#include "add.h"

QAdd::QAdd()
{
    this->setGeometry(600,500,10,10);
    this->setFixedSize(320,150);


    add = new QPushButton(this);
    add->setGeometry(10,110,100,30);
    add->setText("Dodaj");

    name_label = new QLabel(this);
    name_label->setGeometry(15,10,200,20);
    name_label->setText("Nazwa");

    name = new QLineEdit(this);
    name->setGeometry(10,30,300,20);

    price_label = new QLabel(this);
    price_label->setGeometry(15,55,100,20);
    price_label->setText("Cena(zl)");

    price = new QLineEdit(this);
    price->setGeometry(10,75,100,20);

    type_label = new QLabel(this);
    type_label->setGeometry(125,55,185,20);
    type_label->setText("Typ");

    type = new QComboBox(this);
    type->setGeometry(120,75,185,25);
    type->addItem("---");
    type->addItem("Jedzenie");
    type->addItem("Alkohol");
    type->addItem("Elektronika");
    type->addItem("Obiad");
    type->addItem("Praca");
    type->addItem("Ksiazki");
    type->addItem("Pociag");
    type->addItem("MPK");
    type->addItem("Kamila");
    type->addItem("Inne");
    type->addItem("Wyplata");
    type->addItem("Zwrot");
    type->addItem("Rodzice");
    connect(add,SIGNAL(clicked(bool)),this,SLOT(Add_Pressed()));

}

void QAdd::Add_Pressed()
{
    QMessageBox m;
    bool ok;

    if(name->text().isEmpty() || price->text().isEmpty() || type->currentIndex() == 0)
    {

       m.setText("Nie wprowadzono wszystkich parametrow");
       m.exec();
    }
    else
    {
        price->text().toFloat(&ok);
        if(ok == true)
        {
            emit Finish();
            this->hide();
        }
        else
        {
            m.setText("Cena nie jest liczba!");
            m.exec();
        }
    }
}

