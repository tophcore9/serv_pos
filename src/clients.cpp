#include "clients.h"

Clients::Clients(QSqlDatabase &db, QSqlTableModel *dishes_model, QWidget *parent) : QWidget(parent)
{
    this->db = db;
    this->dishes_model = dishes_model;
    this->parent = parent;
    model = new QSqlTableModel(parent, this->db);
    model->setTable("Clients");
    model->select();
}

QSqlTableModel *Clients::get_model()
{
    return model;
}

void Clients::open_add_client_form()
{
    add_client_form = new AddClientForm(dishes_model, this);
    add_client_form->setModal(true);
    add_client_form->show();
}

void Clients::add_client(QString name, QString phone, QString date, QString favourite)
{
    int favourite_dish;
    QSqlQuery query(db);

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

    query.exec("INSERT INTO Clients (client_name, client_phone, client_registration_date, client_favourite_dish) VALUES('" +
               name + "', '" + phone + "', '" + date + "', " + QString::number(favourite_dish) + ");");
    model->select();
    // ДОДАЙ ОБРОБКУ ПОМИЛОК
}

void Clients::remove_client(int index)
{
    if (model->rowCount() > index)
    {
        model->removeRow(index);
        model->select();
    }
    else qDebug() << "Incorect index";
}
