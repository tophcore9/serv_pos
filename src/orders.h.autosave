#ifndef ORDERS_H
#define ORDERS_H

#include <QWidget>
#include <QDebug>
#include <QSqlTableModel>
#include "addorderform.h"

class Orders : public QWidget
{
    Q_OBJECT
private:
    QSqlTableModel *model;
    QSqlTableModel *clients_model;
    AddOrderForm *add_order_form;
    QWidget *parent;

public:
    explicit Orders(QSqlDatabase &db, QSqlTableModel *clients_model, QWidget *parent = 0);

    QSqlTableModel* get_model();

signals:

public slots:
    void add_order();
};

#endif // ORDERS_H
