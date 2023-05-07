#include "menuitems.h"

MenuItems::MenuItems(QSqlDatabase &db, QWidget *parent) : QWidget(parent)
{
    this->db = db;
    model = new QSqlTableModel(parent, this->db);
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
    QSqlQuery query(db);

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
            dish_id = query.value("dish_id").toInt();
            break;
        }
    }

    qDebug() << "menu_id: " << QString::number(menu_id) << "\ndish_id: " << QString::number(dish_id);
}
