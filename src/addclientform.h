#ifndef ADDCLIENTFORM_H
#define ADDCLIENTFORM_H

#include <QtWidgets>
#include <QSqlTableModel>

#include "dishes.h"

class AddClientForm : public QDialog
{
    Q_OBJECT
private:
    QSqlTableModel *dishes_model;

    /// GUI
    QVBoxLayout *main_layout;
    QGridLayout *info_layout;
    QHBoxLayout *buttons_layout;

    QLabel *l_name;
    QLineEdit *name_edit;

    QLabel *l_phone;
    QLineEdit *phone_edit;

    QLabel *l_favourite_dish;
    QComboBox *favourite_dish_select;

    QLabel *l_registration_date;
    QLineEdit *registration_date_edit;

    QPushButton *accept_btn;
    QPushButton *cancel_btn;

public:
    explicit AddClientForm(QSqlTableModel *dishes_model, QWidget *parent = 0);

signals:
    void add_client(QString name, QString phone, QString date, QString favourite);

public slots:
    void add_client();
};

#endif // ADDCLIENTFORM_H
