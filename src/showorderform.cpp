#include "showorderform.h"

ShowOrderForm::ShowOrderForm(QModelIndex order_index, QSqlDatabase db, QWidget *parent) : QDialog(parent)
{
    this->setFixedSize(500, 400);
    this->setWindowTitle("Перегляд замовлення");
    QString order_id, order_name, client_name, client_phone, order_price, order_estimated_time, order_date;

    accept_btn = new QPushButton("Підтвердити");
    cancel_btn = new QPushButton("Скасувати");

    QSqlQuery query(db);
    if (query.exec("SELECT * FROM Orders JOIN Clients ON Orders.client_id = Clients.client_id"))
    {
        while (query.next())
        {
            if (order_index.data(0).toString() == query.value("order_name"))
            {
                order_id = query.value("order_id").toString();
                order_name = query.value("order_name").toString();
                client_name = query.value("client_name").toString();
                client_phone = query.value("client_phone").toString();
                order_price = query.value("order_price").toString();
                order_estimated_time = query.value("order_estimated_time").toString();
                order_date = query.value("order_date").toString();
            }
        }
    }

    if (query.exec("SELECT * FROM OrderItems JOIN Dishes ON OrderItems.dish_id = Dishes.dish_id"))
    {
        while (query.next())
        {
            if (query.value("order_id") == order_id)
            {
                dishes.push_back(query.value("dish_name").toString());
            }
        }
    }

    /// МАКЕТИ ТА КОМПОНОВКА
    // Налаштування макетів
    main_layout = new QVBoxLayout;
    info_layout = new QGridLayout;
    buttons_layout = new QHBoxLayout;
    setLayout(main_layout);

    // Компоновка макетів
    main_layout->addLayout(info_layout);
    main_layout->addLayout(buttons_layout);

    buttons_layout->setAlignment(Qt::AlignBottom);

    // ТИМЧАСОВЕ
    QString dishs = "";
    for (int i = 0; i < dishes.size(); ++i)
        dishs += dishes[i] + "\n";
    QLabel *lb = new QLabel(order_name + "\n" + client_name + "\n" + client_phone + "\n" + order_price + "\n" + order_estimated_time + "\n" + order_date + "\n" + dishs);

    info_layout->addWidget(lb);
    buttons_layout->addWidget(accept_btn);
    buttons_layout->addWidget(cancel_btn);

    connect(accept_btn, SIGNAL(clicked()), this, SLOT(edit_order()));
    connect(this, SIGNAL(edit_order(QString,QString,double,int,QString,std::vector<QString>)), parent, SLOT(edit_order(QString,QString,double,int,QString,std::vector<QString>)));

    connect(cancel_btn, SIGNAL(clicked()), this, SLOT(close()));
}

void ShowOrderForm::edit_order()
{
    emit edit_order("", "", 0.0, 0, "", {""});
}
