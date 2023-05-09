#include "menuitems.h"

MenuItems::MenuItems(QSqlDatabase &db, QWidget *parent) : QWidget(parent)
{
    model = new QSqlTableModel(parent, db);
    model->setTable("MenuItems");
    model->select();
}

QSqlTableModel *MenuItems::get_model()
{
    return model;
}

void MenuItems::add_menu_item(QString menu_name, QString dish_name)
{
    QSqlQuery query(model->database());
    int menu_id, dish_id;

    query.exec("SELECT * FROM Menu;");
    while (query.next())
    {
        if (query.value("menu_name") == menu_name)
        {
            menu_id = query.value("menu_id").toInt();
            break;
        }
    }

    query.exec("SELECT * FROM Dishes;");
    while (query.next())
    {
        if (query.value("dish_name") == dish_name)
        {
            dish_id = model->query().value("dish_id").toInt();
            break;
        }
    }

    if (query.exec("INSERT INTO MenuItems (menu_id, dish_id) VALUES (" + QString::number(menu_id) + ", " + QString::number(dish_id) + ");"))
        model->select();
    else
        QMessageBox::critical(this, "Помилка!", "Не вдалось виконати запит!\n"
                              "Повідомлення БД: " + query.lastError().databaseText() +
                              "\nПовідомлення драйвера: " + query.lastError().driverText());
}

void MenuItems::remove_menu_items(int menu_id)
{
    QSqlQuery query(model->database());
    query.exec("DELETE FROM MenuItems WHERE menu_id = " + QString::number(menu_id));
    model->select();
}
