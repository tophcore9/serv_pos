#include "mainwindow.h"
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // БАЗОВІ НАЛАШТУВАННЯ
    this->setWindowTitle("ServPOS");
    this->setFixedSize(1000, 600);



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




    // МАКЕТИ
    // Налаштування макетів
    QVBoxLayout *main_layout = new QVBoxLayout;
    QHBoxLayout *title_layout = new QHBoxLayout;
    QHBoxLayout *view_layout = new QHBoxLayout;
    QGridLayout *button_layout = new QGridLayout;

    QWidget *central_widget = new QWidget;
    central_widget->setLayout(main_layout);
    this->setCentralWidget(central_widget);


    // Компоновка макетів
    main_layout->addLayout(title_layout);
    main_layout->addLayout(view_layout);
    main_layout->addLayout(button_layout);


    // Компоновка віджетів
    title_layout->addWidget(l_order);
    title_layout->addWidget(l_dishes);
    title_layout->addWidget(l_clients);

    view_layout->addWidget(order_list_view);
    view_layout->addWidget(dishes_list_view);
    view_layout->addWidget(client_list_view);





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
        dishes_list_view->setModel(dishes->get_model());
        client_list_view->setModel(clients->get_model());

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
