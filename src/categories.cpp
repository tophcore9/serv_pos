#include "categories.h"

Categories::Categories(QSqlDatabase &db, QWidget *parent) : ModelBase(db, parent)
{
    model->setTable("Categories");
    model->select();
}

void Categories::open_show_category_form()
{
    show_category_form = new ShowCategoryForm(index, this);
    show_category_form->setModal(true);
    show_category_form->show();
}

void Categories::reset_categories_form()
{
    model->setSort(0, Qt::AscendingOrder);
    model->select();
    categories_form->close();
}

void Categories::open_add_category_form()
{
    add_category_form = new AddCategoryForm(model, this);
    add_category_form->setModal(true);
    add_category_form->show();
}

void Categories::add_category(QString name)
{
    secure_query("INSERT INTO Categories (category_name) VALUES (\"" + name + "\")", add_category_form);
}

void Categories::edit_category(QString default_name, QString name)
{
    secure_query("UPDATE Categories SET "
                   "category_name = \"" + name +
                   "\" WHERE category_name = \"" + default_name + "\"", show_category_form);
}

void Categories::open_categories()
{
    categories_form = new CategoriesForm(model, this);
    categories_form->setModal(true);
    categories_form->show();
}
