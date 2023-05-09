#include "menu.h"

Menu::Menu(QSqlDatabase &db, QSqlTableModel *dishes_model, QWidget *parent) : QWidget(parent)
{
    this->dishes_model = dishes_model;
    this->parent = parent;
    model = new QSqlTableModel(parent, db);
    model->setTable("Menu");
    model->select();

    menu_items = new MenuItems(db, this);
}

QSqlTableModel *Menu::get_model()
{
    return model;
}

void Menu::open_show_menu_form()
{
    show_menu_form = new ShowMenuForm(this);
    show_menu_form->setModal(true);
    show_menu_form->show();
}

void Menu::remove_menu(int index)
{
    QVariant menu_id = model->data(model->index(index, 0));
    menu_items->remove_menu_items(menu_id.toInt());

    if (model->rowCount() > index)
    {
        model->removeRow(index);
        model->select();
    }
    else qDebug() << "Incorect index";
}

void Menu::add_menu(QString name, std::vector<QString> dishes)
{
    QSqlQuery query(model->database());
    query.exec("INSERT INTO Menu (menu_name) VALUES (\"" + name + "\");");
    model->select();

    for (int i = 0; i < dishes.size(); ++i)
        menu_items->add_menu_item(name, dishes[i]);
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
