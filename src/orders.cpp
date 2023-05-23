#include "orders.h"

Orders::Orders(QSqlDatabase &db, QSqlTableModel *clients_model, QSqlTableModel *dishes_model, QWidget *parent) : ModelBase(db, parent)
{
    this->clients_model = clients_model;
    this->dishes_model = dishes_model;

    model->setTable("Orders");
    model->select();

    order_items = new OrderItems(db, this);
}

void Orders::open_show_order_form()
{
    show_order_form = new ShowOrderForm(index, clients_model, dishes_model, this);
    show_order_form->setModal(true);
    show_order_form->show();
}

void Orders::add_order(QString name, QString client, double total_price, int total_time, QString date, std::vector<QString> dishes)
{
    QString client_id;
    QSqlQuery query(model->database());

    // Обробка індексації
    if (query.exec("SELECT * FROM Clients"))
    {
        while (query.next())
        {
            if (query.value("client_phone") == client)
            {
                client_id = query.value("client_id").toString();
                break;
            }
        }
    }
    else ModelBase::secure_query_exception(query, this);

    secure_query("INSERT INTO Orders (order_name, client_id, order_price, order_estimated_time, order_date) VALUES (\"" + name + "\", " +
                        client_id + ", " + QString::number(total_price) + ", " + QString::number(total_time) + ", \"" + date + "\")", add_order_form);

    for (int i = 0; i < dishes.size(); ++i)
        order_items->add_order_item(name, dishes[i]);
}

void Orders::edit_order(QString order_id, QString name, QString client, double total_price, int total_time, QString date, std::vector<QString> dishes)
{
    QString client_id;
    QSqlQuery query(model->database());

    // Обробка індексації
    if (query.exec("SELECT * FROM Clients"))
    {
        while (query.next())
        {
            if (query.value("client_phone") == client)
            {
                client_id = query.value("client_id").toString();
                break;
            }
        }
    }
    else ModelBase::secure_query_exception(query, this);

    secure_query("UPDATE Orders SET "
                   "client_id = " + client_id + ", "
                   "order_price = " + QString::number(total_price) + ", "
                   "order_estimated_time = " + QString::number(total_time) + ", "
                   "order_date = \"" + date + "\" "
                   "WHERE order_id = \"" + order_id + "\"", show_order_form);

    order_items->remove_order_items(order_id.toInt());

    for (int i = 0; i < dishes.size(); ++i)
        order_items->add_order_item(name, dishes[i]);
}

void Orders::open_add_order_form()
{
    add_order_form = new AddOrderForm(clients_model, dishes_model, this);
    add_order_form->setModal(true);
    add_order_form->show();
}
