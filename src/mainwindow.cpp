#include "mainwindow.h"
#include <QSqlError>
#include "clients.h"
#include "orders.h"
#include "dishes.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    /// БАЗОВІ НАЛАШТУВАННЯ
    this->setWindowTitle("ServPOS");
    this->setFixedSize(1200, 700);
    this->setWindowIcon(QIcon("../img/icons/main_icon.png"));

    language.load("../translations/lang_en.qm");
    qApp->installTranslator(&language);

    // Зміна кольору вікна
    QPalette pal = this->palette();
    pal.setColor(QPalette::Background, Qt::gray);
    this->setPalette(pal);


    /// ВІДЖЕТИ
    // Додавання віджетів
    l_order = new QLabel(tr("Замовлення"));
    order_list_view = new QListView;
    add_order_btn = new QPushButton(tr("Додати"));
    delete_order_btn = new QPushButton(tr("Видалити"));

    l_dishes = new QLabel(tr("Страви"));
    dishes_list_view = new QListView;
    add_dish_btn = new QPushButton(tr("Додати"));
    delete_dish_btn = new QPushButton(tr("Видалити"));

    l_clients = new QLabel(tr("Клієнти"));
    client_list_view = new QListView;
    add_client_btn = new QPushButton(tr("Додати"));
    delete_client_btn = new QPushButton(tr("Видалити"));

    l_other = new QLabel(tr("Інше"));
    open_categories_btn = new QPushButton(tr("Категорії"));
    open_menu_btn = new QPushButton(tr("Меню"));
    open_statistics_btn = new QPushButton(tr("Статистика"));


    // Налаштування віджетів
    l_order->setAlignment(Qt::AlignHCenter);

    l_dishes->setAlignment(Qt::AlignHCenter);
    dishes_list_view->setMinimumWidth(550);
    l_dishes->setMinimumWidth(550);

    l_clients->setAlignment(Qt::AlignHCenter);

    l_other->setAlignment(Qt::AlignCenter);
    l_other->setMinimumWidth(150);


    /// МАКЕТИ І КОМПОНОВКА
    // Додавання і налаштування макетів
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
    other_functions_layout->addWidget(open_menu_btn);
    other_functions_layout->addWidget(open_statistics_btn);


    /// ПІДКЛЮЧЕННЯ К БД
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../database/main.db");

    if (db.open())
    {
        /// ГОЛОВНА ЧАСТИНА ПРОГРАМИ
        // Ініціалізація класів
        categories = new Categories(db, this);
        dishes = new Dishes(db, categories->get_model(), this);
        menu = new Menu(db, dishes->get_model(), this);
        clients = new Clients(db, dishes->get_model(), this);
        orders = new Orders(db, clients->get_model(), dishes->get_model(), this);

        // Задання моделей таблицям
        order_list_view->setModel(orders->get_model());
        order_list_view->setModelColumn(1);

        dishes_list_view->setModel(dishes->get_model());
        dishes_list_view->setModelColumn(1);

        client_list_view->setModel(clients->get_model());
        client_list_view->setModelColumn(2);
    }
    else
    {
        /// ОБРОБКА ПОМИЛОК
        QMessageBox::critical(this, tr("Помилка!"), tr("Не вдалось підключитись до бази даних!\n") +
                              tr("Повідомлення БД: ") + db.lastError().databaseText() +
                              tr("\nПовідомлення драйвера: ") + db.lastError().driverText());
        this->close();
    }





    /// СИГНАЛИ ТА СЛОТИ
    connect(client_list_view, &QListView::doubleClicked, clients, &Clients::open_show_client_form);
    connect(order_list_view, &QListView::doubleClicked, orders, &Orders::open_show_order_form);
    connect(dishes_list_view, &QListView::doubleClicked, dishes, &Dishes::open_show_dish_form);

    connect(this, SIGNAL(send_client_index(QModelIndex)), clients, SLOT(change_index(QModelIndex)));
    connect(this, SIGNAL(send_dish_index(QModelIndex)), dishes, SLOT(change_index(QModelIndex)));
    connect(this, SIGNAL(send_order_index(QModelIndex)), orders, SLOT(change_index(QModelIndex)));

    connect(add_client_btn, &QPushButton::clicked, clients, &Clients::open_add_client_form);
    connect(add_dish_btn, &QPushButton::clicked, dishes, &Dishes::open_add_dish_form);
    connect(add_order_btn, &QPushButton::clicked, orders, &Orders::open_add_order_form);

    connect(delete_client_btn, &QPushButton::clicked, this, &MainWindow::remove_client_row);
    connect(delete_dish_btn, &QPushButton::clicked, this, &MainWindow::remove_dish_row);
    connect(delete_order_btn, &QPushButton::clicked, this, &MainWindow::remove_order_row);

    connect(client_list_view, &QListView::clicked, this, &MainWindow::change_client_row);
    connect(dishes_list_view, &QListView::clicked, this, &MainWindow::change_dish_row);
    connect(order_list_view, &QListView::clicked, this, &MainWindow::change_order_row);

    connect(open_categories_btn, &QPushButton::clicked, categories, &Categories::open_categories);
    connect(open_menu_btn, &QPushButton::clicked, menu, &Menu::open_menu);
}

void MainWindow::change_dish_row(const QModelIndex index)
{
    current_dish = index.row();
    send_dish_index(index);
}

void MainWindow::change_order_row(const QModelIndex index)
{
    current_order = index.row();
    send_order_index(index);
}

void MainWindow::remove_client_row()
{
    clients->remove_client(current_client);
}

void MainWindow::remove_dish_row()
{
    dishes->remove_dish(current_dish);
}

void MainWindow::remove_order_row()
{
    orders->remove_order(current_order);
}

void MainWindow::change_client_row(const QModelIndex index)
{
    current_client = index.row();
    send_client_index(index);
}
