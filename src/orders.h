#ifndef ORDERS_H
#define ORDERS_H

#include <QWidget>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlQuery>

#include "addorderform.h"
#include "orderitems.h"
#include "showorderform.h"

class Orders : public QWidget
{
    Q_OBJECT
private:
    QSqlTableModel *model;
    QSqlTableModel *clients_model;
    QSqlTableModel *dishes_model;
    QModelIndex index;

    OrderItems *order_items;
    AddOrderForm *add_order_form;
    ShowOrderForm *show_order_form;

    QWidget *parent;

public:
    explicit Orders(QSqlDatabase &db, QSqlTableModel *clients_model, QSqlTableModel *dishes_model, QWidget *parent = 0);

    QSqlTableModel* get_model();

signals:

public slots:
    void change_index(const QModelIndex index);
    void open_show_order_form();
    void open_add_order_form();
    void remove_order(int);
    void add_order(QString name, QString client, double total_price, int total_time, QString date, std::vector<QString> dishes);
    void edit_order(QString order_id, QString name, QString client, double total_price, int total_time, QString date, std::vector<QString> dishes);
    void change_sort(int sort_index);
};

#endif // ORDERS_H
