#include "orders.h"

Orders::Orders(QSqlDatabase &db, QObject *parent) : QObject(parent)
{
    this->db = db;
    model = new QSqlTableModel(parent, this->db);
    model->setTable("Orders");
    model->select();
}

QSqlTableModel *Orders::get_model()
{
    return model;
}

Orders::~Orders()
{
    delete model;
}
