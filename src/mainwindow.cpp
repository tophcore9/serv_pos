#include "mainwindow.h"
#include "clients.h"
#include "orders.h"
#include "dishes.h"

void MainWindow::change_main_window_lang()
{
    l_order->setText(tr("Замовлення"));
    add_order_btn->setText(tr("Додати"));
    delete_order_btn->setText(tr("Видалити"));

    l_dishes->setText(tr("Страви"));
    add_dish_btn->setText(tr("Додати"));
    delete_dish_btn->setText(tr("Видалити"));

    l_clients->setText(tr("Клієнти"));
    add_client_btn->setText(tr("Додати"));
    delete_client_btn->setText(tr("Видалити"));

    l_other->setText(tr("Інше"));
    open_categories_btn->setText(tr("Категорії"));
    open_menu_btn->setText(tr("Меню"));
    open_statistics_btn->setText(tr("Статистика"));
    l_lang_change->setText(tr("Мова:"));

    orders_sort->clear();
    orders_sort->addItem(tr("Сортувати за додаванням"));
    orders_sort->addItem(tr("Сортувати за назвою"));
    orders_sort->addItem(tr("Сортувати за клієнтами"));
    orders_sort->addItem(tr("Сортувати за вартістю"));
    orders_sort->addItem(tr("Сортувати за часом приготування"));
    orders_sort->addItem(tr("Сортувати за датою"));

    dishes_sort->clear();
    dishes_sort->addItem(tr("Сортувати за додаванням"));
    dishes_sort->addItem(tr("Сортувати за назвою"));
    dishes_sort->addItem(tr("Сортувати за вартістю"));
    dishes_sort->addItem(tr("Сортувати за вагою"));
    dishes_sort->addItem(tr("Сортувати за категорією"));
    dishes_sort->addItem(tr("Сортувати за часом приготування"));

    clients_sort->clear();
    clients_sort->addItem(tr("Сортувати за додаванням"));
    clients_sort->addItem(tr("Сортувати за ім'ям"));
    clients_sort->addItem(tr("Сортувати за стравою"));
    clients_sort->addItem(tr("Сортувати за датою"));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    /// БАЗОВІ НАЛАШТУВАННЯ
    this->setWindowTitle("ServPOS");
    this->resize(1200, 700);
    this->setWindowIcon(QIcon("../img/icons/main_icon.png"));

    language = new QTranslator(this);
    language->load("../translations/lang_ua.qm");
    QApplication::installTranslator(language);

    // Зміна кольору вікна
    QPalette pal = this->palette();
    pal.setColor(QPalette::Background, Qt::gray);
    this->setPalette(pal);


    /// ВІДЖЕТИ
    // Додавання віджетів
    l_order = new QLabel(tr("Замовлення"));
    orders_sort = new QComboBox;
    order_list_view = new QListView;
    add_order_btn = new QPushButton(tr("Додати"));
    delete_order_btn = new QPushButton(tr("Видалити"));

    l_dishes = new QLabel(tr("Страви"));
    dishes_sort = new QComboBox;
    dishes_list_view = new QListView;
    add_dish_btn = new QPushButton(tr("Додати"));
    delete_dish_btn = new QPushButton(tr("Видалити"));

    l_clients = new QLabel(tr("Клієнти"));
    clients_sort = new QComboBox;
    client_list_view = new QListView;
    add_client_btn = new QPushButton(tr("Додати"));
    delete_client_btn = new QPushButton(tr("Видалити"));

    l_other = new QLabel(tr("Інше"));
    open_categories_btn = new QPushButton(tr("Категорії"));
    open_menu_btn = new QPushButton(tr("Меню"));
    open_statistics_btn = new QPushButton(tr("Статистика"));
    l_lang_change = new QLabel(tr("Мова:"));
    lang_change = new QComboBox;


    // Налаштування віджетів
    l_order->setAlignment(Qt::AlignHCenter);
    orders_sort->addItem(tr("Сортувати за додаванням"));
    orders_sort->addItem(tr("Сортувати за назвою"));
    orders_sort->addItem(tr("Сортувати за клієнтами"));
    orders_sort->addItem(tr("Сортувати за вартістю"));
    orders_sort->addItem(tr("Сортувати за часом приготування"));
    orders_sort->addItem(tr("Сортувати за датою"));

    l_dishes->setAlignment(Qt::AlignHCenter);
    dishes_sort->addItem(tr("Сортувати за додаванням"));
    dishes_sort->addItem(tr("Сортувати за назвою"));
    dishes_sort->addItem(tr("Сортувати за вартістю"));
    dishes_sort->addItem(tr("Сортувати за вагою"));
    dishes_sort->addItem(tr("Сортувати за категорією"));
    dishes_sort->addItem(tr("Сортувати за часом приготування"));
    dishes_list_view->setMinimumWidth(550);
    l_dishes->setMinimumWidth(550);

    l_clients->setAlignment(Qt::AlignHCenter);
    clients_sort->addItem(tr("Сортувати за додаванням"));
    clients_sort->addItem(tr("Сортувати за ім'ям"));
    clients_sort->addItem(tr("Сортувати за стравою"));
    clients_sort->addItem(tr("Сортувати за датою"));

    l_other->setAlignment(Qt::AlignCenter);
    l_other->setMinimumWidth(150);
    lang_change->addItem("ua_UA");
    lang_change->addItem("en_EN");


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
    orders_layout->addWidget(orders_sort);
    orders_layout->addWidget(order_list_view);
    orders_layout->addWidget(add_order_btn);
    orders_layout->addWidget(delete_order_btn);

    dishes_layout->addWidget(l_dishes);
    dishes_layout->addWidget(dishes_sort);
    dishes_layout->addWidget(dishes_list_view);
    dishes_layout->addWidget(add_dish_btn);
    dishes_layout->addWidget(delete_dish_btn);

    clients_layout->addWidget(l_clients);
    clients_layout->addWidget(clients_sort);
    clients_layout->addWidget(client_list_view);
    clients_layout->addWidget(add_client_btn);
    clients_layout->addWidget(delete_client_btn);

    other_functions_layout->addWidget(l_other);
    other_functions_layout->addWidget(open_categories_btn);
    other_functions_layout->addWidget(open_menu_btn);
    other_functions_layout->addWidget(open_statistics_btn);
    other_functions_layout->addWidget(l_lang_change, 1, Qt::AlignBottom | Qt::AlignCenter);
    other_functions_layout->addWidget(lang_change, 0, Qt::AlignBottom);


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
        client_list_view->setModelColumn(4);
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
    connect(open_statistics_btn, &QPushButton::clicked, this, &MainWindow::open_statistics);

    connect(orders_sort, SIGNAL(currentIndexChanged(int)), orders, SLOT(change_sort(int)));
    connect(dishes_sort, SIGNAL(currentIndexChanged(int)), dishes, SLOT(change_sort(int)));
    connect(clients_sort, SIGNAL(currentIndexChanged(int)), clients, SLOT(change_sort(int)));

    connect(lang_change, &QComboBox::currentTextChanged, this, &MainWindow::change_lang);
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

void MainWindow::open_statistics()
{
    statistics_form = new StatisticsForm(db, this);
    statistics_form->setModal(true);
    statistics_form->show();
}

void MainWindow::change_lang()
{
    if (lang_change->currentText() == "ua_UA")
    {
        QApplication::removeTranslator(language);
        language = new QTranslator(this);
        language->load("../translations/lang_ua.qm");
        QApplication::installTranslator(language);
        change_main_window_lang();
    }
    else if (lang_change->currentText() == "en_EN")
    {
        QApplication::removeTranslator(language);
        language = new QTranslator(this);
        language->load("../translations/lang_en.qm");
        QApplication::installTranslator(language);
        change_main_window_lang();
    }
}

void MainWindow::remove_client_row()
{
    QMessageBox::StandardButton reply = QMessageBox::warning(this, tr("Увага!"), tr("При видаленні клієнта видаляться всі його замовлення, ви впевнені?"),
                                                             QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QSqlQuery query(db);
        QString client_id;

        query.exec("SELECT * FROM Clients");
        while (query.next())
        {
            if (query.value("client_phone").toString() == client_list_view->currentIndex().data(0).toString())
            client_id = query.value("client_id").toString();
        }

        query.exec("SELECT * FROM Orders WHERE client_id = " + client_id);
        while (query.next())
        {
            QSqlQuery query2(db);
            query2.exec("DELETE FROM OrderItems WHERE order_id = " + query.value("order_id").toString());
        }

        query.exec("DELETE FROM Orders WHERE client_id = " + client_id);

        clients->remove_client(current_client);

        orders->get_model()->select();
    }
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
