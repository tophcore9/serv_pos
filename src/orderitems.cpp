#include "orderitems.h"

OrderItems::OrderItems(QSqlDatabase &db, QWidget *parent) : QWidget(parent)
{
    model = new QSqlTableModel(parent, db);
    model->setTable("OrderItems");
    model->select();
}

QSqlTableModel *OrderItems::get_model()
{
    return model;
}

void OrderItems::add_order_item(QString order_name, QString dish_name)
{
    QSqlQuery query(model->database());
    int order_id, dish_id;

    query.exec("SELECT * FROM Orders");
    while (query.next())
    {
        if (query.value("order_name") == order_name)
        {
            order_id = query.value("order_id").toInt();
            break;
        }
    }

    query.exec("SELECT * FROM Dishes");
    while (query.next())
    {
        if (query.value("dish_name") == dish_name)
        {
            dish_id = query.value("dish_id").toInt();
            break;
        }
    }

    if (query.exec("INSERT INTO OrderItems (order_id, dish_id) VALUES (" + QString::number(order_id) + ", " + QString::number(dish_id) + ");"))
        model->select();
    else
        QMessageBox::critical(this, "Помилка!", "Не вдалось виконати запит!\n"
                              "Повідомлення БД: " + query.lastError().databaseText() +
                              "\nПовідомлення драйвера: " + query.lastError().driverText());
}

void OrderItems::remove_order_items(int order_id)
{
    QSqlQuery query(model->database());

    if (query.exec("DELETE FROM OrderItems WHERE order_id = " + QString::number(order_id)))
        model->select();
    else
        QMessageBox::critical(this, "Помилка!", "Не вдалось виконати запит!\n"
                              "Повідомлення БД: " + query.lastError().databaseText() +
                              "\nПовідомлення драйвера: " + query.lastError().driverText());
}
