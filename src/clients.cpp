#include "clients.h"
#include <QDebug>

Clients::Clients(QSqlDatabase &db, QSqlTableModel *dishes_model, QWidget *parent) : QWidget(parent)
{
    this->dishes_model = dishes_model;
    this->parent = parent;
    model = new QSqlTableModel(parent, db);
    model->setTable("Clients");
    model->select();
}

QSqlTableModel *Clients::get_model()
{
    return model;
}

void Clients::add_client()
{
    adc = new AddClientForm(dishes_model, parent);
    adc->setModal(true);
    adc->show();
}

Clients::~Clients()
{

}
