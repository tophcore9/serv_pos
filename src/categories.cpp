#include "categories.h"

Categories::Categories(QSqlDatabase &db, QWidget *parent) : QWidget(parent)
{
    this->parent = parent;
    model = new QSqlTableModel(parent, db);
    model->setTable("Categories");
    model->select();
}

QSqlTableModel *Categories::get_model()
{
    return model;
}

void Categories::remove_category(int index)
{
    if (model->rowCount() > index)
    {
        model->removeRow(index);
        model->select();
    }
    else qDebug() << "Incorect index";
}

void Categories::add_category()
{

}

void Categories::open_categories()
{
    categories_form = new CategoriesForm(model, this);
    categories_form->setModal(true);
    categories_form->show();
}
