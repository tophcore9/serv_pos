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
    int order_id, dish_id;

    model->query().exec("SELECT * FROM Orders");
    while (model->query().next())
    {
        if (model->query().value("order_name") == order_name)
        {
            order_id = model->query().value("order_id").toInt();
            break;
        }
    }

    model->query().exec("SELECT * FROM Dishes");
    while (model->query().next())
    {
        if (model->query().value("dish_name") == dish_name)
        {
            dish_id = model->query().value("dish_id").toInt();
            break;
        }
    }

    model->query().exec("INSERT INTO OrderItems (order_id, dish_id) VALUES (" + QString::number(order_id) + ", " + QString::number(dish_id) + ");");
    model->select();
}

void OrderItems::remove_order_items(int order_id)
{
    //QSqlQuery query(db);
    model->query().exec("DELETE FROM OrderItems WHERE order_id = " + QString::number(order_id));
}
