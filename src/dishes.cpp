#include "dishes.h"

Dishes::Dishes(QSqlDatabase &db, QSqlTableModel *categories_model, QWidget *parent) : QWidget(parent)
{
    this->db = db;
    this->categories_model = categories_model;
    this->parent = parent;
    model = new QSqlTableModel(parent, this->db);
    model->setTable("Dishes");
    model->select();
}

QSqlTableModel *Dishes::get_model()
{
    return model;
}

void Dishes::remove_dish(int index)
{
    if (model->rowCount() > index)
    {
        model->removeRow(index);
        model->select();
    }
    else qDebug() << "Incorect index";
}

void Dishes::add_dish(QString name, double weight, double price, int category, int estimated_time, QString url)
{
    QSqlQuery query(db);
    //query.exec();
    qDebug() << "Adding";
}

void Dishes::open_add_dish_form()
{
    add_dish_form = new AddDishForm(categories_model, this);
    add_dish_form->setModal(true);
    add_dish_form->show();
}
