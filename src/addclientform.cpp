#include "addclientform.h"

AddClientForm::AddClientForm(QSqlTableModel *dishes_model, QWidget *parent) : QDialog(parent)
{
    /// БАЗОВІ НАЛАШТУВАННЯ
    //this->parent = parent;
    this->dishes_model = dishes_model;
    this->setWindowTitle(tr("Додати клієнта"));
    this->setFixedSize(350, 500);


    /// ВІДЖЕТИ
    l_name = new QLabel(tr("ПІБ:"));
    name_edit = new QLineEdit;

    l_phone = new QLabel(tr("Номер телефону:"));
    phone_edit = new QLineEdit;

    l_favourite_dish = new QLabel(tr("Улюблена страва:"));
    favourite_dish_select = new QComboBox;

    l_registration_date = new QLabel(tr("Дата реєстрації:"));
    registration_date_edit = new QLineEdit(QDate::currentDate().toString(Qt::ISODate));


    accept_btn = new QPushButton(tr("Підтвердити"));
    cancel_btn = new QPushButton(tr("Скасувати"));


    // Налаштування віджетів
    // Розсташування лейблів біля полей
    l_name->setAlignment(Qt::AlignRight);
    l_phone->setAlignment(Qt::AlignRight);
    l_favourite_dish->setAlignment(Qt::AlignRight);
    l_registration_date->setAlignment(Qt::AlignRight);

    // Встановлення статичного розміру полей вводу
    name_edit->setMaximumWidth(200);

    phone_edit->setMaximumWidth(200);
    phone_edit->setInputMask("(+380) 00-000-00-00");

    favourite_dish_select->setMaximumWidth(200);

    registration_date_edit->setMaximumWidth(200);
    registration_date_edit->setInputMask("0000-00-00");

    favourite_dish_select->setModel(dishes_model);
    favourite_dish_select->setModelColumn(1);


    /// МАКЕТИ ТА КОМПОНОВКА
    // Налаштування макетів
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


    /// СИГНАЛИ ТА СЛОТИ
    connect(cancel_btn, SIGNAL(clicked()), this, SLOT(close()));

    connect(accept_btn, SIGNAL(clicked()), this, SLOT(add_client()));
    connect(this, SIGNAL(add_client(QString,QString,QString,QString)), parent, SLOT(add_client(QString,QString,QString,QString)));
}

void AddClientForm::add_client()
{
    emit add_client(name_edit->text(), phone_edit->text(), registration_date_edit->text(), favourite_dish_select->currentText());
}
