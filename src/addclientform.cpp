#include "addclientform.h"

AddClientForm::AddClientForm(QSqlTableModel *model, QDialog *parent) : QDialog(parent)
{
    // БАЗОВІ НАЛАШТУВАННЯ
    this->model = model;
    this->setWindowTitle("Додати клієнта");
    this->setFixedSize(350, 500);


    // ВІДЖЕТИ
    l_name = new QLabel("ПІБ:");
    name_edit = new QLineEdit;

    l_phone = new QLabel("Номер телефону:");
    phone_edit = new QLineEdit;

    l_favourite_dish = new QLabel("Улюблена страва:");
    favourite_dish_edit = new QLineEdit;

    l_registration_date = new QLabel("Дата реєстрації:");
    registration_date_edit = new QLineEdit(QDate::currentDate().toString(Qt::ISODate));


    accept_btn = new QPushButton("Підтвердити");
    cancel_btn = new QPushButton("Скасувати");



    // МАКЕТИ ТА КОМПОНОВКА
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
    info_layout->addWidget(favourite_dish_edit, 2, 1);
    info_layout->addWidget(l_registration_date, 3, 0);
    info_layout->addWidget(registration_date_edit, 3, 1);

    buttons_layout->addWidget(accept_btn);
    buttons_layout->addWidget(cancel_btn);




    // СИГНАЛИ ТА СЛОТИ
    //connect(cancel_btn, &QPushButton::clicked, this, &AddClientForm::close());
    connect(cancel_btn, SIGNAL(clicked()), this, SLOT(close()));
}

AddClientForm::~AddClientForm()
{
    delete l_name;
    delete name_edit;

    delete l_phone;
    delete name_edit;

    delete l_favourite_dish;
    delete favourite_dish_edit;

    delete l_registration_date;
    delete registration_date_edit;

    delete accept_btn;
    delete cancel_btn;
}
