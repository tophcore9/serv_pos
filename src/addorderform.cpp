#include "addorderform.h"

AddOrderForm::AddOrderForm(QSqlTableModel *clients_model, QWidget *parent) : QDialog(parent)
{
    this->parent = parent;
    this->clients_model = clients_model;
    this->setWindowTitle("Додати замовлення");
    this->setFixedSize(350, 500);

    // ВІДЖЕТИ
    l_client = new QLabel("Клієнт:");
    client_select = new QComboBox;

    l_price = new QLabel("Вартість:");
    price_edit = new QLineEdit;
    price_l = new QLabel("грн.");

    l_estimated_time = new QLabel("Очікуваний час приготування:");
    estimated_time_edit = new QLineEdit;
    estimated_time_l = new QLabel("хв.");

    l_date = new QLabel("Дата:");
    date_edit = new QLineEdit(QDate::currentDate().toString(Qt::ISODate));


    accept_btn = new QPushButton("Підтвердити");
    cancel_btn = new QPushButton("Скасувати");


    // Налаштування віджетів
    // Розсташування лейблів біля полей
    l_client->setAlignment(Qt::AlignRight);
    l_price->setAlignment(Qt::AlignRight);
    l_estimated_time->setAlignment(Qt::AlignRight);
    l_date->setAlignment(Qt::AlignRight);

    estimated_time_edit->setEnabled(false);
    price_edit->setEnabled(false);

    client_select->setModel(clients_model);
    client_select->setModelColumn(1);


    // МАКЕТИ ТА КОМПОНОВКА
    // Налаштування макетів
    main_layout = new QVBoxLayout;
    info_layout = new QGridLayout;
    buttons_layout = new QHBoxLayout;
    setLayout(main_layout);

    // Компоновка макетів
    main_layout->addLayout(info_layout);
    main_layout->addLayout(buttons_layout);

    buttons_layout->setAlignment(Qt::AlignBottom);

    // Компоновка віджетів
    info_layout->addWidget(l_client, 0, 0);
    info_layout->addWidget(client_select, 0, 1);
    info_layout->addWidget(l_price, 1, 0);
    info_layout->addWidget(price_edit, 1, 1);
    info_layout->addWidget(price_l, 1, 2);
    info_layout->addWidget(l_estimated_time, 2, 0);
    info_layout->addWidget(estimated_time_edit, 2, 1);
    info_layout->addWidget(estimated_time_l, 2, 2);
    info_layout->addWidget(l_date, 3, 0);
    info_layout->addWidget(date_edit, 3, 1);

    buttons_layout->addWidget(accept_btn);
    buttons_layout->addWidget(cancel_btn);

    // СИГНАЛИ ТА СЛОТИ
    connect(cancel_btn, SIGNAL(clicked()), this, SLOT(close()));
}
