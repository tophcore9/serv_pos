#ifndef ADDORDERFORM_H
#define ADDORDERFORM_H

#include <QtWidgets>
#include <QSqlTableModel>
#include "clients.h"

class AddOrderForm : public QDialog
{
    Q_OBJECT

private:
    //QSqlTableModel *model;
    QSqlTableModel *clients_model;
    //QWidget *parent;

    // GUI
    QVBoxLayout *main_layout;
    QGridLayout *info_layout;
    QHBoxLayout *buttons_layout;

    QLabel *l_client;
    QComboBox *client_select;

    QLabel *l_price;
    QLineEdit *price_edit;
    QLabel *price_l;

    QLabel *l_estimated_time;
    QLineEdit *estimated_time_edit;
    QLabel *estimated_time_l;

    QLabel *l_date;
    QLineEdit *date_edit;

    QPushButton *accept_btn;
    QPushButton *cancel_btn;

public:
    explicit AddOrderForm(QSqlTableModel *clients_model, QWidget *parent = 0);

signals:

public slots:
};

#endif // ADDORDERFORM_H
