#include "dishes.h"

Dishes::Dishes(QSqlDatabase &db, QObject *parent) : QObject(parent)
{
    model = new QSqlTableModel(parent, db);
    model->setTable("Dishes");
    model->select();
}

QSqlTableModel *Dishes::get_model()
{
    return model;
}
