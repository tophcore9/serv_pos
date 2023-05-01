#include "clients.h"
#include <QDebug>

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

void Clients::add_client()
{
    qDebug() << "Signal";
}

Clients::~Clients()
{
    delete model;
}
