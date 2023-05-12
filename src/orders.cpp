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
    show_order_form = new ShowOrderForm(index, clients_model, dishes_model, this);
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
        QMessageBox::critical(this, tr("Помилка!"), tr("Не вдалось виконати запит!\n") +
                              tr("Будь ласка, оберіть елемент перед тим, як видалити його."));
    }
}

void Orders::add_order(QString name, QString client, double total_price, int total_time, QString date, std::vector<QString> dishes)
{
    QString client_id;

    // Обробка індексації
    QSqlQuery query(model->database());
    query.exec("SELECT * FROM Clients");

    while (query.next())
    {
        if (query.value("client_name") == client)
        {
            client_id = query.value("client_id").toString();
            break;
        }
    }

    if (query.exec("INSERT INTO Orders (order_name, client_id, order_price, order_estimated_time, order_date) VALUES (\"" + name + "\", " +
                        client_id + ", " + QString::number(total_price) + ", " + QString::number(total_time) + ", \"" + date + "\");"))
    {
        model->select();
        add_order_form->close();
    }
    else
    {
        QMessageBox::critical(add_order_form, tr("Помилка!"), tr("Не вдалось виконати запит!\n") +
                              tr("Повідомлення БД: ") + query.lastError().databaseText() +
                              tr("\nПовідомлення драйвера: ") + query.lastError().driverText());
    }

    for (int i = 0; i < dishes.size(); ++i)
        order_items->add_order_item(name, dishes[i]);
}

void Orders::edit_order(QString order_id, QString name, QString client, double total_price, int total_time, QString date, std::vector<QString> dishes)
{
    QString client_id;

    // Обробка індексації
    QSqlQuery query(model->database());
    query.exec("SELECT * FROM Clients");

    while (query.next())
    {
        if (query.value("client_phone") == client)
        {
            client_id = query.value("client_id").toString();
            break;
        }
    }

    if (query.exec("UPDATE Orders SET "
                   "client_id = " + client_id + ", "
                   "order_price = " + QString::number(total_price) + ", "
                   "order_estimated_time = " + QString::number(total_time) + ", "
                   "order_date = \"" + date + "\" "
                   "WHERE order_id = \"" + order_id + "\""))
    {
        model->select();
        show_order_form->close();
    }
    else
    {
        QMessageBox::critical(show_order_form, "Помилка!", "Не вдалось виконати запит!\n"
                              "Повідомлення БД: " + query.lastError().databaseText() +
                              "\nПовідомлення драйвера: " + query.lastError().driverText());
    }

    order_items->remove_order_items(order_id.toInt());

    for (int i = 0; i < dishes.size(); ++i)
        order_items->add_order_item(name, dishes[i]);
}

void Orders::change_sort(int sort_index)
{
    switch (sort_index) {
    case 0:
        model->setSort(0, Qt::AscendingOrder);
        break;
    case 1:
        model->setSort(1, Qt::AscendingOrder);
        break;
    case 2:
        model->setSort(2, Qt::AscendingOrder);
        break;
    case 3:
        model->setSort(3, Qt::AscendingOrder);
        break;
    case 4:
        model->setSort(4, Qt::AscendingOrder);
        break;
    case 5:
        model->setSort(5, Qt::AscendingOrder);
        break;
    }
    model->select();
}

void Orders::open_add_order_form()
{
    add_order_form = new AddOrderForm(clients_model, dishes_model, this);
    add_order_form->setModal(true);
    add_order_form->show();
}
