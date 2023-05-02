#include "dishes.h"

Dishes::Dishes(QSqlDatabase &db, QWidget *parent) : QWidget(parent)
{
    this->parent = parent;
    this->db = db;
    model = new QSqlTableModel(parent, this->db);
    model->setTable("Dishes");
    model->select();
}

QSqlTableModel *Dishes::get_model()
{
    return model;
}

void Dishes::add_dish()
{

}

Dishes::~Dishes()
{

}
