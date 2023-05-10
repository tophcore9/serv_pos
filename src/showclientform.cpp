#include "showclientform.h"

ShowClientForm::ShowClientForm(QModelIndex client_index, QSqlDatabase db, QWidget *parent) : QDialog(parent)
{
    this->setFixedSize(500, 400);
    this->setWindowTitle("Перегляд клієнта");
    QString client_name, client_phone, client_favourite_dish, client_registration_date;

    QSqlQuery query(db);
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

    QLabel *lb = new QLabel(client_name + "\n" + client_phone + "\n" + client_favourite_dish + "\n" + client_registration_date);
    accept_btn = new QPushButton("Підтвердити");
    cancel_btn = new QPushButton("Скасувати");

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

    info_layout->addWidget(lb);

    buttons_layout->addWidget(accept_btn);
    buttons_layout->addWidget(cancel_btn);

    connect(accept_btn, SIGNAL(clicked()), this, SLOT(edit_client()));
    connect(this, SIGNAL(edit_client(QString,QString,QString,QString)), parent, SLOT(edit_client(QString,QString,QString,QString)));

    connect(cancel_btn, SIGNAL(clicked()), this, SLOT(close()));
}

void ShowClientForm::edit_client()
{
    emit edit_client("", "", "", "");
}
