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
    show_category_form = new ShowCategoryForm(index, this);
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
    else
    {
        QMessageBox::critical(this, "Помилка!", "Не вдалось виконати запит!\n"
                              "Будь ласка, оберіть елемент перед тим, як видалити його.");
    }
}

void Categories::change_index(const QModelIndex index)
{
    this->index = index;
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

    if (query.exec("INSERT INTO Categories (category_name) VALUES (\"" + name + "\");"))
    {
        model->select();
        add_category_form->close();
    }
    else
    {
        QMessageBox::critical(add_category_form, "Помилка!", "Не вдалось виконати запит!\n"
                              "Повідомлення БД: " + query.lastError().databaseText() +
                              "\nПовідомлення драйвера: " + query.lastError().driverText());
    }
}

void Categories::edit_category(QString default_name, QString name)
{
    qDebug() << "Editing";
    QSqlQuery query(model->database());

    if (query.exec("UPDATE Categories SET "
                   "category_name = \"" + name +
                   "\" WHERE category_name = \"" + default_name + "\""))
    {
        model->select();
        show_category_form->close();
    }
    else
    {
        QMessageBox::critical(show_category_form, "Помилка!", "Не вдалось виконати запит!\n"
                              "Повідомлення БД: " + query.lastError().databaseText() +
                              "\nПовідомлення драйвера: " + query.lastError().driverText());
    }
}

void Categories::open_categories()
{
    categories_form = new CategoriesForm(model, this);
    categories_form->setModal(true);
    categories_form->show();
}
