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

void Dishes::remove_dish(int index)
{
    if (model->rowCount() > index)
    {
        model->removeRow(index);
        model->select();
    }
    else qDebug() << "Incorect index";
}

void Dishes::add_dish(QString name, double weight, double price, QString category, int estimated_time, QString url)
{
    int category_id;

    // Обробка індексації
    model->query().exec("SELECT * FROM Categories");

    while (model->query().next())
    {
        if (model->query().value("category_name") == category)
        {
            category_id = model->query().value("category_id").toInt();
            break;
        }
    }

    model->query().exec("INSERT INTO Dishes (dish_name, dish_weight, dish_price, dish_category, dish_estimated_time, dish_photo) VALUES ('" +
               name + "', " + QString::number(weight) + ", " + QString::number(price) + ", " +
               QString::number(category_id) + ", " + QString::number(estimated_time) + ", '" + url + "');");
    model->select();
    // ДОДАЙ ОБРОБКУ ПОМИЛОК
}

void Dishes::open_add_dish_form()
{
    add_dish_form = new AddDishForm(categories_model, this);
    add_dish_form->setModal(true);
    add_dish_form->show();
}
