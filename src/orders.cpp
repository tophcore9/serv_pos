#include "orders.h"

Orders::Orders(QSqlDatabase &db, QObject *parent) : QObject(parent)
{
    model = new QSqlTableModel(parent, db);
    model->setTable("Orders");
    model->select();
}

QSqlTableModel *Orders::get_model()
{
    return model;
}
