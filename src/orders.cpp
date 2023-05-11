#include "orders.h"

Orders::Orders(QSqlDatabase &db, QSqlTableModel *clients_model, QSqlTableModel *dishes_model, QWidget *parent) : QWidget(parent)
{
    this->dishes_model = dishes_model;
    this->parent = parent;
    this->clients_model = clients_model;
    model = new QSqlTableModel(parent, db);
    model->setTable("Orders");
    model->select();

    order_items = new OrderItems(db, this);
}

QSqlTableModel *Orders::get_model()
{
    return model;
}

void Orders::change_index(const QModelIndex index)
{
    this->index = index;
}

void Orders::open_show_order_form()
{
    show_order_form = new ShowOrderForm(index, clients_model, this);
    show_order_form->setModal(true);
    show_order_form->show();
}

void Orders::remove_order(int index)
{
    QVariant order_id = model->data(model->index(index, 0));
    order_items->remove_order_items(order_id.toInt());

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

void Orders::add_order(QString name, QString client, double total_price, int total_time, QString date, std::vector<QString> dishes)
{
    int client_id;

    // Обробка індексації
    QSqlQuery query(model->database());
    query.prepare("SELECT * FROM Clients;");
    query.exec();

    while (query.next())
    {
        if (query.value("client_name") == client)
        {
            client_id = query.value("client_id").toInt();
            break;
        }
    }

    if (query.exec("INSERT INTO Orders (order_name, client_id, order_price, order_estimated_time, order_date) VALUES (\"" + name + "\", " +
                        QString::number(client_id) + ", " + QString::number(total_price) + ", " + QString::number(total_time) + ", \"" + date + "\");"))
    {
        model->select();
        add_order_form->close();
    }
    else
    {
        QMessageBox::critical(add_order_form, "Помилка!", "Не вдалось виконати запит!\n"
                              "Повідомлення БД: " + query.lastError().databaseText() +
                              "\nПовідомлення драйвера: " + query.lastError().driverText());
    }

    for (int i = 0; i < dishes.size(); ++i)
        order_items->add_order_item(name, dishes[i]);
}

void Orders::edit_order(QString default_name, QString name, QString client, double total_price, int total_time, QString date, std::vector<QString> dishes)
{
    qDebug() << "Editing";
//    int client_id;

//    // Обробка індексації
//    QSqlQuery query(model->database());
//    query.prepare("SELECT * FROM Clients;");
//    query.exec();

//    while (query.next())
//    {
//        if (query.value("client_name") == client)
//        {
//            client_id = query.value("client_id").toInt();
//            break;
//        }
//    }

//    if (query.exec("INSERT INTO Orders (order_name, client_id, order_price, order_estimated_time, order_date) VALUES (\"" + name + "\", " +
//                        QString::number(client_id) + ", " + QString::number(total_price) + ", " + QString::number(total_time) + ", \"" + date + "\");"))
//    {
//        model->select();
//        add_order_form->close();
//    }
//    else
//    {
//        QMessageBox::critical(add_order_form, "Помилка!", "Не вдалось виконати запит!\n"
//                              "Повідомлення БД: " + query.lastError().databaseText() +
//                              "\nПовідомлення драйвера: " + query.lastError().driverText());
//    }

//    for (int i = 0; i < dishes.size(); ++i)
//        order_items->add_order_item(name, dishes[i]);

}

void Orders::open_add_order_form()
{
    add_order_form = new AddOrderForm(clients_model, dishes_model, this);
    add_order_form->setModal(true);
    add_order_form->show();
}
