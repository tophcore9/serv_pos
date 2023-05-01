#include "clients.h"
#include <QDebug>
#include "addclientform.h"

Clients::Clients(QSqlDatabase &db, QObject *parent) : QObject(parent)
{
    this->db = db;
    model = new QSqlTableModel(parent, this->db);
    model->setTable("Clients");
    model->select();
}

QSqlTableModel *Clients::get_model()
{
    return model;
}

void Clients::add_client()
{
    AddClientForm *acf = new AddClientForm(model);
    acf->setModal(true);
    acf->show();
}

Clients::~Clients()
{
    delete model;
}
