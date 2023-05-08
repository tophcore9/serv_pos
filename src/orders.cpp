#include "orders.h"

Orders::Orders(QSqlDatabase &db, QSqlTableModel *clients_model, QSqlTableModel *dishes_model, QWidget *parent) : QWidget(parent)
{
    this->dishes_model = dishes_model;
    this->db = db;
    this->parent = parent;
    this->clients_model = clients_model;
    model = new QSqlTableModel(parent, this->db);
    model->setTable("Orders");
    model->select();

    order_items = new OrderItems(db, this);
}

QSqlTableModel *Orders::get_model()
{
    return model;
}

void Orders::remove_order(int index)
{
    if (model->rowCount() > index)
    {
        model->removeRow(index);
        model->select();
    }
    else qDebug() << "Incorect index";



    //order_items->remove_order_items();
}

void Orders::add_order(QString name, QString client, double total_price, int total_time, QString date, std::vector<QString> dishes)
{
//    for (int i = 0; i < dishes.size(); ++i)
//        qDebug() << dishes[i];
//    qDebug() << "\n";

    int client_id;
    QSqlQuery query(db);

    // Обробка індексації
    query.exec("SELECT * FROM Clients;");

    while (query.next())
    {
        if (query.value("client_name") == client)
        {
            client_id = query.value("client_id").toInt();
            break;
        }
    }

    query.exec("INSERT INTO Orders (order_name, client_id, order_price, order_estimated_time, order_date) VALUES ('" + name + "', " + QString::number(client_id) + ", " +
               QString::number(total_price) + ", " + QString::number(total_time) + ", '" + date + "');");
    model->select();


    for (int i = 0; i < dishes.size(); ++i)
        order_items->add_order_item(name, dishes[i]);

    // Потрібно додати можливість додавання декількох страв
    // ДОДАЙ ОБРОБКУ ПОМИЛОК
}

void Orders::open_add_order_form()
{
    add_order_form = new AddOrderForm(db, clients_model, dishes_model, this);
    add_order_form->setModal(true);
    add_order_form->show();
}
