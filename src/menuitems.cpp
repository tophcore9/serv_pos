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
    int menu_id, dish_id;

    model->query().exec("SELECT * FROM Menu;");
    while (model->query().next())
    {
        if (model->query().value("menu_name") == menu_name)
        {
            menu_id = model->query().value("menu_id").toInt();
            break;
        }
    }

    model->query().exec("SELECT * FROM Dishes;");
    while (model->query().next())
    {
        if (model->query().value("dish_name") == dish_name)
        {
            dish_id = model->query().value("dish_id").toInt();
            break;
        }
    }

    model->query().exec("INSERT INTO MenuItems (menu_id, dish_id) VALUES (" + QString::number(menu_id) + ", " + QString::number(dish_id) + ");");
    model->select();
}

void MenuItems::remove_menu_items(int menu_id)
{
    model->query().exec("DELETE FROM MenuItems WHERE menu_id = " + QString::number(menu_id));
}
