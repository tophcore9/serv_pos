#include "orderitems.h"

OrderItems::OrderItems(QSqlDatabase &db, QWidget *parent) : ModelBase(db, parent)
{
    model->setTable("OrderItems");
    model->select();
}

void OrderItems::add_order_item(QString order_name, QString dish_name)
{
    QSqlQuery query(model->database());
    int order_id, dish_id;

    if (query.exec("SELECT * FROM Orders"))
    {
        while (query.next())
        {
            if (query.value("order_name") == order_name)
            {
                order_id = query.value("order_id").toInt();
                break;
            }
        }
    }
    else ModelBase::secure_query_exception(query, this);

    if (query.exec("SELECT * FROM Dishes"))
    {
        while (query.next())
        {
            if (query.value("dish_name") == dish_name)
            {
                dish_id = query.value("dish_id").toInt();
                break;
            }
        }
    }
    else ModelBase::secure_query_exception(query, this);

    secure_query("INSERT INTO OrderItems (order_id, dish_id) VALUES (" + QString::number(order_id) + ", " + QString::number(dish_id) + ")");
}

void OrderItems::remove_order_items(int order_id)
{
    secure_query("DELETE FROM OrderItems WHERE order_id = " + QString::number(order_id));
}
