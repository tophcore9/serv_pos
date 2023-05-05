#include "orders.h"

Orders::Orders(QSqlDatabase &db, QSqlTableModel *clients_model, QWidget *parent) : QWidget(parent)
{
    this->db = db;
    this->parent = parent;
    this->clients_model = clients_model;
    model = new QSqlTableModel(parent, this->db);
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

void Orders::add_order(int client_id, double total_price, int total_time, QString date)
{
    QSqlQuery query(db);
    query.exec("INSERT INTO Orders (client_id, order_price, order_estimated_time, order_date) VALUES (" + QString::number(client_id) + ", " +
               QString::number(total_price) + ", " + QString::number(total_time) + ", '" + date + "');");
    model->select();
    // Потрібно додати можливість додавання декількох страв
}

void Orders::open_add_order_form()
{
    add_order_form = new AddOrderForm(clients_model, this);
    add_order_form->setModal(true);
    add_order_form->show();
}
