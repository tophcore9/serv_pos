#include "menuitems.h"

MenuItems::MenuItems(QSqlDatabase &db, QWidget *parent) : ModelBase(db, parent)
{
    model->setTable("MenuItems");
    model->select();
}

void MenuItems::add_menu_item(QString menu_name, QString dish_name)
{
    QSqlQuery query(model->database());
    int menu_id, dish_id;

    if (query.exec("SELECT * FROM Menu"))
    {
        while (query.next())
        {
            if (query.value("menu_name") == menu_name)
            {
                menu_id = query.value("menu_id").toInt();
                break;
            }
        }
    }
    else ModelBase::secure_query_exception(query, this);

    if (query.exec("SELECT * FROM Dishes"))
    {
        while (query.next())
        {
            if (query.value("dish_name") == dish_name)
            {
                dish_id = query.value("dish_id").toInt();
                break;
            }
        }
    }
    else ModelBase::secure_query_exception(query, this);

    secure_query("INSERT INTO MenuItems (menu_id, dish_id) VALUES (" + QString::number(menu_id) + ", " + QString::number(dish_id) + ")");
}

void MenuItems::remove_menu_items(int menu_id)
{
    secure_query("DELETE FROM MenuItems WHERE menu_id = " + QString::number(menu_id));
}
