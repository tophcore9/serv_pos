#include "menu.h"

Menu::Menu(QSqlDatabase &db, QSqlTableModel *dishes_model, QWidget *parent) : ModelBase(db, parent)
{
    this->dishes_model = dishes_model;
    model->setTable("Menu");
    model->select();

    menu_items = new MenuItems(db, this);
}

void Menu::open_show_menu_form()
{
    show_menu_form = new ShowMenuForm(index, dishes_model, this);
    show_menu_form->setModal(true);
    show_menu_form->show();
}

void Menu::add_menu(QString name, std::vector<QString> dishes)
{
    secure_query("INSERT INTO Menu (menu_name) VALUES (\"" + name + "\")", add_menu_form);

    for (int i = 0; i < dishes.size(); ++i)
        menu_items->add_menu_item(name, dishes[i]);
}

void Menu::edit_menu(QString default_name, QString name, std::vector<QString> dishes)
{
    QString menu_id;

    QSqlQuery query(model->database());

    if (query.exec("SELECT * FROM Menu"))
    {
        while (query.next())
        {
            if (query.value("menu_name") == name)
            {
                menu_id = query.value("menu_id").toString();
                break;
            }
        }
    }
    else ModelBase::secure_query_exception(query, this);

    secure_query("UPDATE Menu SET "
                   "menu_name = \"" + name + "\" "
                   "WHERE menu_id = \"" + menu_id + "\"", show_menu_form);

    menu_items->remove_menu_items(menu_id.toInt());

    for (int i = 0; i < dishes.size(); ++i)
        menu_items->add_menu_item(name, dishes[i]);
}

void Menu::reset_menu_form()
{
    model->setSort(0, Qt::AscendingOrder);
    model->select();
    menu_form->close();
}

void Menu::open_add_menu_form()
{
    add_menu_form = new AddMenuForm(model, dishes_model, this);
    add_menu_form->setModal(true);
    add_menu_form->show();
}

void Menu::open_menu()
{
    menu_form = new MenuForm(model, this);
    menu_form->setModal(true);
    menu_form->show();
}
