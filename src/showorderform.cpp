#include "showorderform.h"

ShowOrderForm::ShowOrderForm(QModelIndex order_index, QSqlTableModel *clients_model, QWidget *parent) : QDialog(parent)
{
    /// БАЗОВІ НАЛАШТУВАННЯ
    this->setFixedWidth(400);
    this->setWindowTitle(tr("Перегляд замовлення"));

    QString order_id, order_name, client_name, client_phone, order_price, order_estimated_time, order_date;

    QSqlQuery query(clients_model->database());
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


    /// ВІДЖЕТИ
    // Додавання віджетів
    l_name = new QLabel(tr("Ідентифікатор:"));
    name_edit = new QLineEdit(order_name);

    l_client = new QLabel(tr("Клієнт:"));
    client_select = new QComboBox;

    l_price = new QLabel(tr("Вартість:"));
    price_edit = new QLineEdit("0");
    price_l = new QLabel(tr("грн."));

    l_estimated_time = new QLabel(tr("Очікуваний час приготування:"));
    estimated_time_edit = new QLineEdit("0");
    estimated_time_l = new QLabel(tr("хв."));

    l_date = new QLabel(tr("Дата:"));
    date_edit = new QLineEdit(order_date);

    l_dishes = new QLabel(tr("Страви:"));
    add_dish_btn = new QPushButton("+");

    accept_btn = new QPushButton(tr("Підтвердити"));
    cancel_btn = new QPushButton(tr("Скасувати"));

    // Налаштування віджетів
    // Розсташування лейблів біля полей
    l_name->setAlignment(Qt::AlignRight);
    l_client->setAlignment(Qt::AlignRight);
    l_price->setAlignment(Qt::AlignRight);
    l_estimated_time->setAlignment(Qt::AlignRight);
    l_date->setAlignment(Qt::AlignRight);

    l_dishes->setAlignment(Qt::AlignRight);
    add_dish_btn->setFixedSize(25, 25);

    // Встановлення статичного розміру полей вводу
    name_edit->setMaximumWidth(200);
    client_select->setMaximumWidth(200);
    price_edit->setMaximumWidth(200);
    estimated_time_edit->setMaximumWidth(200);
    date_edit->setMaximumWidth(200);

    name_edit->setEnabled(false);
    estimated_time_edit->setEnabled(false);
    price_edit->setEnabled(false);

    client_select->setModel(clients_model);
    client_select->setModelColumn(2);
    client_select->setCurrentText(client_phone);


    /// МАКЕТИ І КОМПОНОВКА
    // Додавання і налаштування макетів
    main_layout = new QVBoxLayout;
    info_layout = new QGridLayout;
    buttons_layout = new QHBoxLayout;

    setLayout(main_layout);
    buttons_layout->setAlignment(Qt::AlignBottom);

    // Компоновка макетів
    main_layout->addLayout(info_layout);
    main_layout->addLayout(buttons_layout);

    // Компоновка віджетів
    info_layout->addWidget(l_name, 0, 0);
    info_layout->addWidget(name_edit, 0, 1);

    info_layout->addWidget(l_client, 1, 0);
    info_layout->addWidget(client_select, 1, 1);

    info_layout->addWidget(l_price, 2, 0);
    info_layout->addWidget(price_edit, 2, 1);
    info_layout->addWidget(price_l, 2, 2);

    info_layout->addWidget(l_estimated_time, 3, 0);
    info_layout->addWidget(estimated_time_edit, 3, 1);
    info_layout->addWidget(estimated_time_l, 3, 2);

    info_layout->addWidget(l_date, 4, 0);
    info_layout->addWidget(date_edit, 4, 1);

    info_layout->addWidget(l_dishes, 5, 0);
    info_layout->addWidget(add_dish_btn, 5, 1);

    buttons_layout->addWidget(accept_btn);
    buttons_layout->addWidget(cancel_btn);


    /// СИГНАЛИ І СЛОТИ
    connect(accept_btn, SIGNAL(clicked()), this, SLOT(edit_order()));
    connect(this, SIGNAL(edit_order(QString,QString,QString,double,int,QString,std::vector<QString>)),
            parent, SLOT(edit_order(QString,QString,QString,double,int,QString,std::vector<QString>)));

    connect(cancel_btn, SIGNAL(clicked()), this, SLOT(close()));
}

void ShowOrderForm::edit_order()
{
    emit edit_order("", "", "", 0.0, 0, "", {""});
}
