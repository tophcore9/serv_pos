#include "mainwindow.h"
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // БАЗОВІ НАЛАШТУВАННЯ
    this->setWindowTitle("ServPOS");
    this->setFixedSize(1000, 600);

    // Зміна кольору вікна
    QPalette pal = this->palette();
    pal.setColor(QPalette::Background, Qt::gray);
    this->setPalette(pal);






    // ВІДЖЕТИ
    // Додавання віджетів
    client_list_view = new QListView;
    order_list_view = new QListView;
    dishes_list_view = new QListView;

    QLabel *l_order = new QLabel("Замовлення");
    QLabel *l_dishes = new QLabel("Страви");
    QLabel *l_clients = new QLabel("Клієнти");


    // Налаштування віджетів
    l_order->setAlignment(Qt::AlignHCenter);
    l_dishes->setAlignment(Qt::AlignHCenter);
    l_clients->setAlignment(Qt::AlignHCenter);

    dishes_list_view->setMinimumWidth(550);
    l_dishes->setMinimumWidth(550);





    // МАКЕТИ
    // Налаштування макетів
    QHBoxLayout *main_layout = new QHBoxLayout;
    QVBoxLayout *order_layout = new QVBoxLayout;
    QVBoxLayout *dish_layout = new QVBoxLayout;
    QVBoxLayout *client_layout = new QVBoxLayout;

    QWidget *central_widget = new QWidget;
    central_widget->setLayout(main_layout);
    this->setCentralWidget(central_widget);


    // Компоновка макетів
    main_layout->addLayout(order_layout);
    main_layout->addLayout(dish_layout);
    main_layout->addLayout(client_layout);


    // Компоновка віджетів
    order_layout->addWidget(l_order);
    order_layout->addWidget(order_list_view);

    dish_layout->addWidget(l_dishes);
    dish_layout->addWidget(dishes_list_view);


    client_layout->addWidget(l_clients);
    client_layout->addWidget(client_list_view);




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
        clients = new Clients(db, this);

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

}

MainWindow::~MainWindow()
{

}
