#include "menu.h"

Menu::Menu(QSqlDatabase &db, QSqlTableModel *dishes_model, QWidget *parent) : QWidget(parent)
{
    this->dishes_model = dishes_model;
    this->db = db;
    this->parent = parent;
    model = new QSqlTableModel(parent, this->db);
    model->setTable("Menu");
    model->select();

    menu_items = new MenuItems(db, this);
}

QSqlTableModel *Menu::get_model()
{
    return model;
}

void Menu::remove_menu(int index)
{
    if (model->rowCount() > index)
    {
        model->removeRow(index);
        model->select();
    }
    else qDebug() << "Incorect index";
}

void Menu::add_menu(QString name, std::vector<QString> dishes)
{
    for (int i = 0; i < dishes.size(); ++i)
        qDebug() << dishes[i];
    //menu_items->add_menu_item(name);
//    QSqlQuery query(db);
//    qDebug() << query.value("menu_name");
//    query.exec("INSERT INTO Menu (menu_name) VALUES ('" + name + "');");
//    model->select();
    // Також потрібно додати можливість додавання декількох страв
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
