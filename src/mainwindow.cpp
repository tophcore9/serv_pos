#include "mainwindow.h"
#include <QSqlError>
#include "clients.h"
#include "orders.h"
#include "dishes.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // БАЗОВІ НАЛАШТУВАННЯ
    this->setWindowTitle("ServPOS");
    this->setFixedSize(1200, 700);

    // Зміна кольору вікна
    QPalette pal = this->palette();
    pal.setColor(QPalette::Background, Qt::gray);
    this->setPalette(pal);










    // ВІДЖЕТИ
    // Додавання віджетів
    l_order = new QLabel("Замовлення");
    order_list_view = new QListView;
    add_order_btn = new QPushButton("Додати");
    delete_order_btn = new QPushButton("Видалити");

    l_dishes = new QLabel("Страви");
    dishes_list_view = new QListView;
    add_dish_btn = new QPushButton("Додати");
    delete_dish_btn = new QPushButton("Видалити");

    l_clients = new QLabel("Клієнти");
    client_list_view = new QListView;
    add_client_btn = new QPushButton("Додати");
    delete_client_btn = new QPushButton("Видалити");

    l_other = new QLabel("Інше");
    open_categories_btn = new QPushButton("Категорії");
    open_menus_btn = new QPushButton("Меню");
    open_statistics_btn = new QPushButton("Статистика");


    // Налаштування віджетів
    l_order->setAlignment(Qt::AlignHCenter);

    l_dishes->setAlignment(Qt::AlignHCenter);
    dishes_list_view->setMinimumWidth(550);
    l_dishes->setMinimumWidth(550);

    l_clients->setAlignment(Qt::AlignHCenter);

    l_other->setAlignment(Qt::AlignCenter);
    l_other->setMinimumWidth(150);








    // МАКЕТИ І КОМПОНОВКА
    // Налаштування макетів
    main_layout = new QHBoxLayout;
    orders_layout = new QVBoxLayout;
    dishes_layout = new QVBoxLayout;
    clients_layout = new QVBoxLayout;
    other_functions_layout = new QVBoxLayout();
    other_functions_layout->setAlignment(Qt::AlignTop);

    central_widget = new QWidget;
    central_widget->setLayout(main_layout);
    this->setCentralWidget(central_widget);


    // Компоновка макетів
    main_layout->addLayout(orders_layout);
    main_layout->addLayout(dishes_layout);
    main_layout->addLayout(clients_layout);
    main_layout->addLayout(other_functions_layout);


    // Компоновка віджетів
    orders_layout->addWidget(l_order);
    orders_layout->addWidget(order_list_view);
    orders_layout->addWidget(add_order_btn);
    orders_layout->addWidget(delete_order_btn);

    dishes_layout->addWidget(l_dishes);
    dishes_layout->addWidget(dishes_list_view);
    dishes_layout->addWidget(add_dish_btn);
    dishes_layout->addWidget(delete_dish_btn);

    clients_layout->addWidget(l_clients);
    clients_layout->addWidget(client_list_view);
    clients_layout->addWidget(add_client_btn);
    clients_layout->addWidget(delete_client_btn);

    other_functions_layout->addWidget(l_other);
    other_functions_layout->addWidget(open_categories_btn);
    other_functions_layout->addWidget(open_menus_btn);
    other_functions_layout->addWidget(open_statistics_btn);







    // ПІДКЛЮЧЕННЯ К БД
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../database/main.db");

    if (db.open())
    {
        // ГОЛОВНА ЧАСТИНА ПРОГРАМИ
        statusBar()->showMessage("Успішне підключення до БД " + db.databaseName());

        // Ініціалізація класів
        orders = new Orders(db, this);
        dishes = new Dishes(db, this);
        clients = new Clients(db, dishes->get_model(), this);

        // Задання моделей таблицям
        order_list_view->setModel(orders->get_model());
        order_list_view->setModelColumn(1);

        dishes_list_view->setModel(dishes->get_model());
        dishes_list_view->setModelColumn(1);

        client_list_view->setModel(clients->get_model());
        client_list_view->setModelColumn(1);
    }
    else
    {
        // ОБРОБКА ПОМИЛОК
        statusBar()->showMessage("Помилка: " + db.lastError().text());
    }





    // СИГНАЛИ ТА СЛОТИ
    connect(add_client_btn, &QPushButton::clicked, clients, &Clients::add_client);
    connect(add_dish_btn, &QPushButton::clicked, dishes, &Dishes::add_dish);
    connect(add_order_btn, &QPushButton::clicked, orders, &Orders::add_order);
}

MainWindow::~MainWindow()
{
    delete clients;
    delete orders;
    delete dishes;

    delete main_layout;
// 	  При розкоментуванні цих строк відбувається подвійне звільнення пам'яті
//    delete orders_layout;
//    delete dishes_layout;
//    delete clients_layout;
//    delete other_functions_layout;
//    delete central_widget;

    delete l_order;
    delete order_list_view;
    delete add_order_btn;
    delete delete_order_btn;

    delete l_dishes;
    delete dishes_list_view;
    delete add_dish_btn;
    delete delete_dish_btn;

    delete l_clients;
    delete client_list_view;
    delete add_client_btn;
    delete delete_client_btn;

    delete l_other;
    delete open_categories_btn;
    delete open_menus_btn;
    delete open_statistics_btn;
}
