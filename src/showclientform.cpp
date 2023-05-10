#include "showclientform.h"

ShowClientForm::ShowClientForm(QModelIndex client_index, QSqlDatabase db, QWidget *parent) : QDialog(parent)
{
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
    QLabel *lb = new QLabel(client_name + "\n" + client_phone + "\n" + client_favourite_dish + "\n" + client_registration_date);
    info_layout->addWidget(lb);
}
