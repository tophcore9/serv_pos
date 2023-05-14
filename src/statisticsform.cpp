#include "statisticsform.h"

StatisticsForm::StatisticsForm(QSqlDatabase &db, QWidget *parent) : QDialog(parent)
{
    /// БАЗОВІ НАЛАШТУВАННЯ
    this->setWindowTitle(tr("Статистичні дані"));
    this->setFixedSize(350, 350);


    /// ВІДЖЕТИ
    // Додавання віджетів
    created_orders = new QLabel(tr("Всього створено замовлень: "));
    created_dishes = new QLabel(tr("Всього створено страв: "));
    created_clients = new QLabel(tr("Всього зареєстровано клієнтів: "));
    created_menu = new QLabel(tr("Всього створено меню: "));
    created_categories = new QLabel(tr("Всього створено категорій: "));

    average_price_dish = new QLabel(tr("Середня вартість страви: "));
    average_weight_dish = new QLabel(tr("Середня вага страви: "));
    average_cooking_time_dish = new QLabel(tr("Середній час приготування страви: "));

    average_price_order = new QLabel(tr("Середя вартість замовлення: "));
    average_cooking_time_order = new QLabel(tr("Середній час приготування замовлення: "));

    mvp_dish = new QLabel(tr("Найпопулярніша страва: "));
    mvp_client = new QLabel(tr("Найактивніший клієнт: "));

    exit_btn = new QPushButton(tr("Вийти"));


    // Налаштування віджетів
    exit_btn->setFixedWidth(150);

    QSqlQuery query(db);

    // Обчислення загальної кількості створених записів
    query.exec("SELECT * FROM sqlite_sequence");
    while (query.next())
    {
        if (query.value("name") == "Orders")
            created_orders->setText(created_orders->text() + query.value("seq").toString());
        else if (query.value("name") == "Clients")
            created_clients->setText(created_clients->text() + query.value("seq").toString());
        else if (query.value("name") == "Dishes")
            created_dishes->setText(created_dishes->text() + query.value("seq").toString());
        else if (query.value("name") == "Menu")
            created_menu->setText(created_menu->text() + query.value("seq").toString());
        else if (query.value("name") == "Categories")
            created_categories->setText(created_categories->text() + query.value("seq").toString());
    }

    int count = 0;
    double average_price = 0;
    double average_weight = 0;
    double average_time = 0;

    // Обчислення середніх значень страв
    query.exec("SELECT * FROM Dishes");
    while (query.next())
    {
        ++count;
        average_price += query.value("dish_price").toDouble();
        average_weight += query.value("dish_weight").toDouble();
        average_time += query.value("dish_estimated_time").toDouble();
    }

    average_price /= count;
    average_weight /= count;
    average_time /= count;

    average_price_dish->setText(average_price_dish->text() + QString::number(average_price));
    average_weight_dish->setText(average_weight_dish->text() + QString::number(average_weight));
    average_cooking_time_dish->setText(average_cooking_time_dish->text() + QString::number(average_time));

    count = 0;
    average_price = 0;
    average_time = 0;
    int mvp_count = 0;
    int mvp_id = 0;

    // Обчислення середніх значень замовлень
    query.exec("SELECT * FROM Orders");
    while (query.next())
    {
        ++count;
        average_price += query.value("order_price").toDouble();
        average_time += query.value("order_estimated_time").toDouble();

        // Знаходження найпопулярнішого клієнта ресторану
        int client_id = query.value("client_id").toInt();
        int count = 0;

        QSqlQuery client_found(db);
        client_found.exec("SELECT * FROM Orders");
        while (client_found.next())
        {
            if (client_found.value("client_id").toInt() == client_id)
                ++count;
        }

        if (count > mvp_count)
        {
            mvp_id = client_id;
            mvp_count = count;
        }
    }

    // Перетворення індексу страву на її назву
    query.exec("SELECT * FROM Clients");
    while (query.next())
    {
        if (query.value("client_id").toInt() == mvp_id)
        {
            mvp_client->setText(mvp_client->text() + "\"" + query.value("client_phone").toString() + "\"");
            break;
        }
    }

    average_price /= count;
    average_time /= count;

    average_price_order->setText(average_price_order->text() + QString::number(average_price));
    average_cooking_time_order->setText(average_cooking_time_order->text() + QString::number(average_time));

    mvp_count = 0;
    mvp_id = 0;

    // Знаходження найпопулярнішої страви
    query.exec("SELECT * FROM OrderItems");
    while (query.next())
    {
        int dish_id = query.value("dish_id").toInt();
        int count = 0;

        QSqlQuery dish_found(db);
        dish_found.exec("SELECT * FROM OrderItems");
        while (dish_found.next())
        {
            if (dish_found.value("dish_id").toInt() == dish_id)
                ++count;
        }

        if (count > mvp_count)
        {
            mvp_id = dish_id;
            mvp_count = count;
        }
    }

    // Перетворення індексу страву на її назву
    query.exec("SELECT * FROM Dishes");
    while (query.next())
    {
        if (query.value("dish_id").toInt() == mvp_id)
        {
            mvp_dish->setText(mvp_dish->text() + "\"" + query.value("dish_name").toString() + "\"");
            break;
        }
    }


    /// МАКЕТИ І КОМПОНОВКА
    // Додавання і налаштування макетів
    main_layout = new QVBoxLayout;
    main_layout->setAlignment(Qt::AlignTop);
    this->setLayout(main_layout);

    // Компоновка макетів

    // Компоновка віджетів
    main_layout->addWidget(created_orders);
    main_layout->addWidget(created_dishes);
    main_layout->addWidget(created_clients);
    main_layout->addWidget(created_menu);
    main_layout->addWidget(created_categories);

    main_layout->addWidget(average_price_dish);
    main_layout->addWidget(average_weight_dish);
    main_layout->addWidget(average_cooking_time_dish);
    main_layout->addWidget(average_price_order);
    main_layout->addWidget(average_cooking_time_order);

    main_layout->addWidget(mvp_dish);
    main_layout->addWidget(mvp_client);

    main_layout->addWidget(exit_btn, 1, Qt::AlignBottom | Qt::AlignCenter);

    /// СИГНАЛИ ТА СЛОТИ
    connect(exit_btn, &QPushButton::clicked, this, &StatisticsForm::close);
}
