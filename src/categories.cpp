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

void Categories::open_show_category_form()
{
    show_category_form = new ShowCategoryForm(this);
    show_category_form->setModal(true);
    show_category_form->show();
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

void Categories::open_add_category_form()
{
    add_category_form = new AddCategoryForm(model, this);
    add_category_form->setModal(true);
    add_category_form->show();
}

void Categories::add_category(QString name)
{
    QSqlQuery query(model->database());
    query.exec("INSERT INTO Categories (category_name) VALUES (\"" + name + "\");");
    model->select();
}

void Categories::open_categories()
{
    categories_form = new CategoriesForm(model, this);
    categories_form->setModal(true);
    categories_form->show();
}
