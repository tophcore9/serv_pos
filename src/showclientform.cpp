#include "showclientform.h"

ShowClientForm::ShowClientForm(QModelIndex client_index, QSqlTableModel *dishes_model, QWidget *parent) : QDialog(parent)
{
    /// БАЗОВІ НАЛАШТУВАННЯ
    this->setFixedSize(350, 500);
    this->setWindowTitle(tr("Перегляд клієнта"));
    past_client_phone = client_index.data(0).toString();


    /// ВІДЖЕТИ
    // Додавання віджетів
    l_name = new QLabel(tr("ПІБ:"));
    name_edit = new QLineEdit;

    l_phone = new QLabel(tr("Номер телефону:"));
    phone_edit = new QLineEdit;

    l_favourite_dish = new QLabel(tr("Улюблена страва:"));
    favourite_dish_select = new QComboBox;

    l_registration_date = new QLabel(tr("Дата реєстрації:"));
    registration_date_edit = new QLineEdit;

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

    QSqlQuery query(dishes_model->database());
    if (query.exec("SELECTs * FROM Clients JOIN Dishes ON Clients.client_favourite_dish = Dishes.dish_id"))
    {
        while (query.next())
        {
            if (query.value("client_phone") == past_client_phone)
            {
                name_edit->setText(query.value("client_name").toString());
                new_client_name = name_edit->text();

                phone_edit->setText(query.value("client_phone").toString());
                new_client_phone = phone_edit->text();
                past_client_phone = phone_edit->text();

                favourite_dish_select->setCurrentText(query.value("dish_name").toString());
                new_client_dish = favourite_dish_select->currentText();

                registration_date_edit->setText(query.value("client_registration_date").toString());
                new_client_date = registration_date_edit->text();
            }
        }
    }
    else ModelBase::secure_query_exception(query, this);


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
    connect(this, SIGNAL(edit_client(QString,QString,QString,QString,QString)), parent, SLOT(edit_client(QString,QString,QString,QString,QString)));

    connect(cancel_btn, SIGNAL(clicked()), this, SLOT(close()));

    connect(name_edit, SIGNAL(textChanged(QString)), this, SLOT(name_changed(QString)));
    connect(phone_edit, SIGNAL(textChanged(QString)), this, SLOT(phone_changed(QString)));
    connect(registration_date_edit, SIGNAL(textChanged(QString)), this, SLOT(date_changed(QString)));
    connect(favourite_dish_select, SIGNAL(currentTextChanged(QString)), this, SLOT(dish_changed(QString)));
}

void ShowClientForm::edit_client()
{
    emit edit_client(past_client_phone, new_client_name, new_client_phone, new_client_date, new_client_dish);
}

void ShowClientForm::name_changed(QString)
{
    new_client_name = name_edit->text();
}

void ShowClientForm::phone_changed(QString)
{
    new_client_phone = phone_edit->text();
}

void ShowClientForm::date_changed(QString)
{
    new_client_date = registration_date_edit->text();
}

void ShowClientForm::dish_changed(QString)
{
    new_client_dish = favourite_dish_select->currentText();
}
