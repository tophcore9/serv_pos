#include "orderitems.h"

OrderItems::OrderItems(QSqlDatabase &db, QWidget *parent) : QWidget(parent)
{
    this->db = db;
    model = new QSqlTableModel(parent, this->db);
    model->setTable("OrderItems");
    model->select();
}

QSqlTableModel *OrderItems::get_model()
{
    return model;
}

void OrderItems::add_order_item(QString client_name, QString order_name)
{

}
