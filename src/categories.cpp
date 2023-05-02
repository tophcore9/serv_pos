#include "categories.h"

Categories::Categories(QSqlDatabase &db, QWidget *parent) : QWidget(parent)
{
    this->parent = parent;
    model = new QSqlTableModel(parent, db);
    model->setTable("Categories");
    model->select();
}

QSqlTableModel *Categories::get_model()
{
    return model;
}

void Categories::add_category()
{

}
