#include "dishes.h"

Dishes::Dishes(QSqlDatabase &db, QObject *parent) : QObject(parent)
{
    this->db = db;
    model = new QSqlTableModel(parent, this->db);
    model->setTable("Dishes");
    model->select();
}

QSqlTableModel *Dishes::get_model()
{
    return model;
}

Dishes::~Dishes()
{
    delete model;
}
