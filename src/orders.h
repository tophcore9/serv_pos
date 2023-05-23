#ifndef ORDERS_H
#define ORDERS_H

#include <QWidget>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlQuery>

#include "addorderform.h"
#include "orderitems.h"
#include "showorderform.h"
#include "modelbase.h"

class Orders : public ModelBase
{
    Q_OBJECT
private:
    QSqlTableModel *clients_model;
    QSqlTableModel *dishes_model;

    OrderItems *order_items;
    AddOrderForm *add_order_form;
    ShowOrderForm *show_order_form;

public:
    explicit Orders(QSqlDatabase &db, QSqlTableModel *clients_model, QSqlTableModel *dishes_model, QWidget *parent = 0);

public slots:
    void open_show_order_form();
    void open_add_order_form();
    void add_order(QString name, QString client, double total_price, int total_time, QString date, std::vector<QString> dishes);
    void edit_order(QString order_id, QString name, QString client, double total_price, int total_time, QString date, std::vector<QString> dishes);

    void remove(int index) override
    {
        QVariant order_id = model->data(model->index(index, 0));
        order_items->remove_order_items(order_id.toInt());

        ModelBase::remove(index);
    }
};

#endif // ORDERS_H
