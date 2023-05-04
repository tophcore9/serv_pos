#include "menu.h"

Menu::Menu(QSqlDatabase &db, QWidget *parent) : QWidget(parent)
{
    this->parent = parent;
    model = new QSqlTableModel(parent, db);
    model->setTable("Menu");
    model->select();
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

void Menu::add_menu()
{

}

void Menu::open_menu()
{
    menu_form = new MenuForm(model, this);
    menu_form->setModal(true);
    menu_form->show();
}
