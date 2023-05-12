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
        QMessageBox::critical(add_client_form, tr("Помилка!"), tr("Не вдалось виконати запит!\n") +
                              tr("Повідомлення БД: ") + query.lastError().databaseText() +
                              tr("\nПовідомлення драйвера: ") + query.lastError().driverText());
    }
}

void Clients::edit_client(QString default_phone, QString name, QString phone, QString date, QString favourite)
{
    qDebug() << default_phone << endl << name << endl << phone << endl << date << endl << favourite;

    QSqlQuery query(model->database());
    QString favourite_dish;

    // Обробка індексації
    query.exec("SELECT * FROM Dishes;");

    while (query.next())
    {
        if (query.value("dish_name") == favourite)
        {
            favourite_dish = query.value("dish_id").toString();
            break;
        }
    }

    // Виконання запиту і обробка помилок
    if (query.exec("UPDATE Clients SET "
                   "client_name = \"" + name + "\", "
                   "client_phone = \"" + phone + "\", "
                   "client_favourite_dish = " + favourite_dish + ", "
                   "client_registration_date = \"" + date + "\" "
                   "WHERE client_phone = \"" + default_phone + "\""))
    {
        model->select();
        show_client_form->close();
    }
    else
    {
        QMessageBox::critical(show_client_form, tr("Помилка!"), tr("Не вдалось виконати запит!\n") +
                              tr("Повідомлення БД: ") + query.lastError().databaseText() +
                              tr("\nПовідомлення драйвера: ") + query.lastError().driverText());
    }
}

void Clients::change_sort(int sort_index)
{
    switch (sort_index) {
    case 0:
        model->setSort(0, Qt::AscendingOrder);
        break;
    case 1:
        model->setSort(1, Qt::AscendingOrder);
        break;
    case 2:
        model->setSort(3, Qt::AscendingOrder);
        break;
    case 3:
        model->setSort(4, Qt::AscendingOrder);
        break;
    }
    model->select();
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
        QMessageBox::critical(this, tr("Помилка!"), tr("Не вдалось виконати запит!\n") +
                              tr("Будь ласка, оберіть елемент перед тим, як видалити його."));
    }
}
