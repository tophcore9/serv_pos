#include "clients.h"
#include <QDebug>
#include "addclientform.h"

Clients::Clients(QSqlDatabase &db, QWidget *parent) : QWidget(parent)
{
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
    AddClientForm *acf = new AddClientForm(model, parent);
    acf->setModal(true);
    acf->show();
}

Clients::~Clients()
{
    delete model;
}
