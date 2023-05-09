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

void Dishes::open_show_dish_form()
{
    show_dish_form = new ShowDishForm(this);
    show_dish_form->setModal(true);
    show_dish_form->show();
}

void Dishes::remove_dish(int index)
{
    if (model->rowCount() > index)
    {
        model->removeRow(index);
        model->select();
    }
    else
    {
        QMessageBox::critical(this, "Помилка!", "Не вдалось виконати запит!\n"
                              "Будь ласка, оберіть елемент перед тим, як видалити його.");
    }
}

void Dishes::add_dish(QString name, double weight, double price, QString category, int estimated_time, QString url)
{
    QSqlQuery query(model->database());
    int category_id;

    // Обробка індексації
    query.exec("SELECT * FROM Categories");
    while (query.next())
    {
        if (query.value("category_name") == category)
        {
            category_id = query.value("category_id").toInt();
            break;
        }
    }

    // Виконання запиту і обробка помилок
    if (query.exec("INSERT INTO Dishes (dish_name, dish_weight, dish_price, dish_category, dish_estimated_time, dish_photo) VALUES (\"" +
               name + "\", " + QString::number(weight) + ", " + QString::number(price) + ", " +
               QString::number(category_id) + ", " + QString::number(estimated_time) + ", \"" + url + "\");"))
    {
        model->select();
        add_dish_form->close();
    }
    else
    {
        QMessageBox::critical(add_dish_form, "Помилка!", "Не вдалось виконати запит!\n"
                              "Повідомлення БД: " + query.lastError().databaseText() +
                              "\nПовідомлення драйвера: " + query.lastError().driverText());
    }
}

void Dishes::open_add_dish_form()
{
    add_dish_form = new AddDishForm(categories_model, this);
    add_dish_form->setModal(true);
    add_dish_form->show();
}
