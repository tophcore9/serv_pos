#include "clients.h"

Clients::Clients(QSqlDatabase &db, QObject *parent) : QObject(parent)
{
    model = new QSqlTableModel(parent, db);
    model->setTable("Clients");
    model->select();
}

QSqlTableModel *Clients::get_model()
{
    return model;
}
