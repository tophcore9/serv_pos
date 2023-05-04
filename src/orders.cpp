#include "orders.h"

Orders::Orders(QSqlDatabase &db, QSqlTableModel *clients_model, QWidget *parent) : QWidget(parent)
{
    this->parent = parent;
    this->clients_model = clients_model;
    model = new QSqlTableModel(parent, db);
    model->setTable("Orders");
    model->select();
}

QSqlTableModel *Orders::get_model()
{
    return model;
}

void Orders::remove_order(int index)
{
    if (model->rowCount() > index)
    {
        model->removeRow(index);
        model->select();
    }
    else qDebug() << "Incorect index";
}

void Orders::add_order()
{
    add_order_form = new AddOrderForm(clients_model, this);
    add_order_form->setModal(true);
    add_order_form->show();
}
