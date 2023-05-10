#include "clients.h"

Clients::Clients(QSqlDatabase &db, QSqlTableModel *dishes_model, QWidget *parent) : QWidget(parent)
{
    this->dishes_model = dishes_model;
    this->parent = parent;
    model = new QSqlTableModel(parent, db);
    model->setTable("Clients");
    model->select();
}

QSqlTableModel *Clients::get_model()
{
    return model;
}

void Clients::change_index(const QModelIndex index)
{
    this->index = index;
}

void Clients::open_show_client_form()
{
    show_client_form = new ShowClientForm(index, dishes_model, this);
    show_client_form->setModal(true);
    show_client_form->show();
}

void Clients::open_add_client_form()
{
    add_client_form = new AddClientForm(dishes_model, this);
    add_client_form->setModal(true);
    add_client_form->show();
}

void Clients::add_client(QString name, QString phone, QString date, QString favourite)
{
    QSqlQuery query(model->database());
    int favourite_dish;

    // Обробка індексації
    query.exec("SELECT * FROM Dishes;");

    while (query.next())
    {
        if (query.value("dish_name") == favourite)
        {
            favourite_dish = query.value("dish_id").toInt();
            break;
        }
    }

    // Виконання запиту і обробка помилок
    if (query.exec("INSERT INTO Clients (client_name, client_phone, client_registration_date, client_favourite_dish) VALUES(\"" +
               name + "\", \"" + phone + "\", \"" + date + "\", " + QString::number(favourite_dish) + ");"))
    {
        model->select();
        add_client_form->close();
    }
    else
    {
        QMessageBox::critical(add_client_form, "Помилка!", "Не вдалось виконати запит!\n"
                              "Повідомлення БД: " + query.lastError().databaseText() +
                              "\nПовідомлення драйвера: " + query.lastError().driverText());
    }
}

void Clients::remove_client(int index)
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
