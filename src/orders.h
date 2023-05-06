#ifndef ORDERS_H
#define ORDERS_H

#include <QWidget>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlQuery>
#include "addorderform.h"

class Orders : public QWidget
{
    Q_OBJECT
private:
    QSqlTableModel *model;
    QSqlTableModel *clients_model;
    AddOrderForm *add_order_form;
    QSqlDatabase db;
    QWidget *parent;

public:
    explicit Orders(QSqlDatabase &db, QSqlTableModel *clients_model, QWidget *parent = 0);

    QSqlTableModel* get_model();

signals:

public slots:
    void open_add_order_form();
    void remove_order(int);
    void add_order(QString client_id, double total_price, int total_time, QString date);
};

#endif // ORDERS_H
