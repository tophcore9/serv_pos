#include "clients.h"

Clients::Clients(QSqlDatabase &db, QSqlTableModel *dishes_model, QWidget *parent) : QWidget(parent)
{
    this->db = db;
    this->dishes_model = dishes_model;
    this->parent = parent;
    model = new QSqlTableModel(parent, this->db);
    model->setTable("Clients");
    model->select();
}

QSqlTableModel *Clients::get_model()
{
    return model;
}

void Clients::open_add_client_form()
{
    add_client_form = new AddClientForm(dishes_model, this);
    add_client_form->setModal(true);
    add_client_form->show();
}

void Clients::add_client(QString name, QString phone, QString date, int favourite)
{
    QSqlQuery query(db);
    //query.exec();
    qDebug() << "Adding";
}

void Clients::remove_client(int index)
{
    if (model->rowCount() > index)
    {
        model->removeRow(index);
        model->select();
    }
    else qDebug() << "Incorect index";
}
