#include "clients.h"

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
    add_client_form = new AddClientForm(dishes_model, parent);
    add_client_form->setModal(true);
    add_client_form->show();
}

Clients::~Clients()
{

}
