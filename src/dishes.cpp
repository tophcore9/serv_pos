#include "dishes.h"

Dishes::Dishes(QSqlDatabase &db, QSqlTableModel *categories_model, QWidget *parent) : ModelBase(db, parent)
{
    this->categories_model = categories_model;
    model->setTable("Dishes");
    model->select();
}

void Dishes::open_show_dish_form()
{
    show_dish_form = new ShowDishForm(index, categories_model, this);
    show_dish_form->setModal(true);
    show_dish_form->show();
}

void Dishes::add_dish(QString name, int weight, double price, QString category, int estimated_time, QString url)
{
    QSqlQuery query(model->database());
    int category_id;

    // Обробка індексації
    if (query.exec("SELECT * FROM Categories"))
    {
        while (query.next())
        {
            if (query.value("category_name") == category)
            {
                category_id = query.value("category_id").toInt();
                break;
            }
        }
    }
    else ModelBase::secure_query_exception(query, this);

    secure_query("INSERT INTO Dishes (dish_name, dish_weight, dish_price, dish_category, dish_estimated_time, dish_photo) VALUES (\"" +
               name + "\", " + QString::number(weight) + ", " + QString::number(price) + ", " +
               QString::number(category_id) + ", " + QString::number(estimated_time) + ", \"" + url + "\")", add_dish_form);
}

void Dishes::edit_dish(QString default_name, QString name, int weight, double price, QString category, int estimated_time, QString url)
{
    QSqlQuery query(model->database());
    QString category_id;

    // Обробка індексації
    if (query.exec("SELECT * FROM Categories"))
    {
        while (query.next())
        {
            if (query.value("category_name") == category)
            {
                category_id = query.value("category_id").toString();
                break;
            }
        }
    }
    else ModelBase::secure_query_exception(query, this);

    secure_query("UPDATE Dishes SET "
                   "dish_name = \"" + name + "\", "
                   "dish_weight = " + QString::number(weight) + ", "
                   "dish_price = " + QString::number(price) + ", "
                   "dish_estimated_time = " + QString::number(estimated_time) + ", "
                   "dish_category = " + category_id + ", "
                   "dish_photo = \"" + url + "\" "
                   "WHERE dish_name = \"" + default_name + "\"", show_dish_form);
}

void Dishes::open_add_dish_form()
{
    add_dish_form = new AddDishForm(categories_model, this);
    add_dish_form->setModal(true);
    add_dish_form->show();
}
