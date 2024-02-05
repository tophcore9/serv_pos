#include "clients.h"

Clients::Clients(QSqlDatabase &db, QSqlTableModel *dishes_model, QWidget *parent) : ModelBase(db, parent)
{
    this->dishes_model = dishes_model;
    model->setTable("Clients");
    model->select();
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
    if (query.exec("SELECT * FROM Dishes"))
    {
        while (query.next())
        {
            if (query.value("dish_name") == favourite)
            {
                favourite_dish = query.value("dish_id").toInt();
                break;
            }
        }
    }
    else ModelBase::secure_query_exception(query, this);

    secure_query("INSERT INTO Clients (client_name, client_phone, client_registration_date, client_favourite_dish) VALUES(\"" +
               name + "\", \"" + phone + "\", \"" + date + "\", " + QString::number(favourite_dish) + ")", add_client_form);
}

void Clients::edit_client(QString default_phone, QString name, QString phone, QString date, QString favourite)
{
    QSqlQuery query(model->database());
    QString favourite_dish;

    // Обробка індексації
    if (query.exec("SELECT * FROM Dishes"))
    {
        while (query.next())
        {
            if (query.value("dish_name") == favourite)
            {
                favourite_dish = query.value("dish_id").toString();
                break;
            }
        }
    }
    else ModelBase::secure_query_exception(query, this);

    secure_query("UPDATE Clients SET "
                   "client_name = \"" + name + "\", "
                   "client_phone = \"" + phone + "\", "
                   "client_favourite_dish = " + favourite_dish + ", "
                   "client_registration_date = \"" + date + "\" "
                   "WHERE client_phone = \"" + default_phone + "\"", show_client_form);
}
