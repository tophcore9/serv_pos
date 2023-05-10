#include "showclientform.h"

ShowClientForm::ShowClientForm(QModelIndex client_index, QSqlTableModel *dishes_model, QWidget *parent) : QDialog(parent)
{
    /// БАЗОВІ НАЛАШТУВАННЯ
    this->setFixedSize(350, 500);
    this->setWindowTitle("Перегляд клієнта");
    QString client_name, client_phone, client_favourite_dish, client_registration_date;

    QSqlQuery query(dishes_model->database());
    if (query.exec("SELECT * FROM Clients JOIN Dishes ON Clients.client_favourite_dish = Dishes.dish_id"))
    {
        while (query.next())
        {
            if (client_index.data(0).toString() == query.value("client_phone"))
            {
                client_name = query.value("client_name").toString();
                client_phone = query.value("client_phone").toString();
                client_favourite_dish = query.value("dish_name").toString();
                client_registration_date = query.value("client_registration_date").toString();
            }
        }
    }
    else
    {
        // Обробка помилок
        qDebug() << query.lastError().text();
    }


    /// ВІДЖЕТИ
    // Додавання віджетів
    l_name = new QLabel("ПІБ:");
    name_edit = new QLineEdit;

    l_phone = new QLabel("Номер телефону:");
    phone_edit = new QLineEdit;

    l_favourite_dish = new QLabel("Улюблена страва:");
    favourite_dish_select = new QComboBox;

    l_registration_date = new QLabel("Дата реєстрації:");
    registration_date_edit = new QLineEdit(QDate::currentDate().toString(Qt::ISODate));

    accept_btn = new QPushButton("Підтвердити");
    cancel_btn = new QPushButton("Скасувати");

    // Налаштування віджетів
    // Розсташування лейблів біля полей
    l_name->setAlignment(Qt::AlignRight);
    l_phone->setAlignment(Qt::AlignRight);
    l_favourite_dish->setAlignment(Qt::AlignRight);
    l_registration_date->setAlignment(Qt::AlignRight);

    // Встановлення статичного розміру полей вводу
    name_edit->setMaximumWidth(200);
    phone_edit->setMaximumWidth(200);
    favourite_dish_select->setMaximumWidth(200);
    registration_date_edit->setMaximumWidth(200);

    favourite_dish_select->setModel(dishes_model);
    favourite_dish_select->setModelColumn(1);
    favourite_dish_select->setCurrentText(client_favourite_dish);

    name_edit->setText(client_name);
    phone_edit->setText(client_phone);
    registration_date_edit->setText(client_registration_date);


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

    info_layout->addWidget(l_phone, 1, 0);
    info_layout->addWidget(phone_edit, 1, 1);

    info_layout->addWidget(l_favourite_dish, 2, 0);
    info_layout->addWidget(favourite_dish_select, 2, 1);

    info_layout->addWidget(l_registration_date, 3, 0);
    info_layout->addWidget(registration_date_edit, 3, 1);

    buttons_layout->addWidget(accept_btn);
    buttons_layout->addWidget(cancel_btn);


    /// СИГНАЛИ І СЛОТИ
    connect(accept_btn, SIGNAL(clicked()), this, SLOT(edit_client()));
    connect(this, SIGNAL(edit_client(QString,QString,QString,QString)), parent, SLOT(edit_client(QString,QString,QString,QString)));

    connect(cancel_btn, SIGNAL(clicked()), this, SLOT(close()));
}

void ShowClientForm::edit_client()
{
    emit edit_client("", "", "", "");
}
