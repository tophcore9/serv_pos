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

void Menu::change_index(const QModelIndex index)
{
    this->index = index;
}

void Menu::open_show_menu_form()
{
    show_menu_form = new ShowMenuForm(index, dishes_model, this);
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
    else
    {
        QMessageBox::critical(this, tr("Помилка!"), tr("Не вдалось виконати запит!\n") +
                              tr("Будь ласка, оберіть елемент перед тим, як видалити його."));
    }
}

void Menu::add_menu(QString name, std::vector<QString> dishes)
{
    QSqlQuery query(model->database());

    if (query.exec("INSERT INTO Menu (menu_name) VALUES (\"" + name + "\");"))
    {
        model->select();
        add_menu_form->close();
    }
    else
    {
        QMessageBox::critical(add_menu_form, tr("Помилка!"), tr("Не вдалось виконати запит!\n") +
                              tr("Повідомлення БД: ") + query.lastError().databaseText() +
                              tr("\nПовідомлення драйвера: ") + query.lastError().driverText());
    }

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

    if (query.exec("UPDATE Menu SET "
                   "menu_name = \"" + name + "\" "
                   "WHERE menu_id = \"" + menu_id + "\""))
    {
        model->select();
        show_menu_form->close();
    }
    else
    {
        QMessageBox::critical(show_menu_form, "Помилка!", "Не вдалось виконати запит!\n"
                              "Повідомлення БД: " + query.lastError().databaseText() +
                              "\nПовідомлення драйвера: " + query.lastError().driverText());
    }

    menu_items->remove_menu_items(menu_id.toInt());

    for (int i = 0; i < dishes.size(); ++i)
        menu_items->add_menu_item(name, dishes[i]);
}

void Menu::change_sort(int sort_index)
{
    switch (sort_index) {
    case 0:
        model->setSort(0, Qt::AscendingOrder);
        break;
    case 1:
        model->setSort(1, Qt::AscendingOrder);
        break;
    }
    model->select();
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
