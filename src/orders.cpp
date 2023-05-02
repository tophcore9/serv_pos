#include "orders.h"

Orders::Orders(QSqlDatabase &db, QWidget *parent) : QWidget(parent)
{
    this->parent = parent;
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

}
