#include "dishes.h"

Dishes::Dishes(QSqlDatabase &db, QSqlTableModel *categories_model, QWidget *parent) : QWidget(parent)
{
    this->categories_model = categories_model;
    this->parent = parent;
    model = new QSqlTableModel(parent, db);
    model->setTable("Dishes");
    model->select();
}

QSqlTableModel *Dishes::get_model()
{
    return model;
}

void Dishes::add_dish()
{
    add_dish_form = new AddDishForm(categories_model, parent);
    add_dish_form->setModal(true);
    add_dish_form->show();
}

Dishes::~Dishes()
{

}
