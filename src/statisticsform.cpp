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
