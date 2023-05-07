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
