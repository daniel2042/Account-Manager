#ifndef ADD_H
#define ADD_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QComboBox>

class QAdd : public QMainWindow
{
    Q_OBJECT
public:
    QAdd();
    QPushButton* add;

    QLabel*      name_label;
    QLineEdit*   name;
    QLabel*      price_label;
    QLineEdit*   price;
    QLabel*      type_label;
    QComboBox*   type;


signals:
    void Finish();

public slots:
    void Add_Pressed();
};

#endif // ADD_H
