#include "addorderform.h"

AddOrderForm::AddOrderForm(QSqlTableModel *clients_model, QSqlTableModel *dishes_model, QWidget *parent) : QDialog(parent)
{
    /// БАЗОВІ НАЛАШТУВАННЯ
    //this->parent = parent;
    this->dishes_model = dishes_model;
    this->clients_model = clients_model;
    this->setWindowTitle("Додати замовлення");
    this->setFixedWidth(350);
    dish_grid_index = 6;
    current_dish_item = 0;


    /// ВІДЖЕТИ
    l_name = new QLabel("Ідентифікатор:");
    name_edit = new QLineEdit("Замовлення#");

    l_client = new QLabel("Клієнт:");
    client_select = new QComboBox;

    l_price = new QLabel("Вартість:");
    price_edit = new QLineEdit("0");
    price_l = new QLabel("грн.");

    l_estimated_time = new QLabel("Очікуваний час приготування:");
    estimated_time_edit = new QLineEdit("0");
    estimated_time_l = new QLabel("хв.");

    l_date = new QLabel("Дата:");
    date_edit = new QLineEdit(QDate::currentDate().toString(Qt::ISODate));

    l_dishes = new QLabel("Страви:");
    add_dish_btn = new QPushButton("+");


    accept_btn = new QPushButton("Підтвердити");
    cancel_btn = new QPushButton("Скасувати");


    // Налаштування віджетів
    // Розсташування лейблів біля полей
    l_name->setAlignment(Qt::AlignRight);
    l_client->setAlignment(Qt::AlignRight);
    l_price->setAlignment(Qt::AlignRight);
    l_estimated_time->setAlignment(Qt::AlignRight);
    l_date->setAlignment(Qt::AlignRight);

    l_dishes->setAlignment(Qt::AlignRight);
    add_dish_btn->setFixedSize(25, 25);

    // Встановлення статичного розміру полей вводу
    client_select->setMaximumWidth(200);
    price_edit->setMaximumWidth(200);
    estimated_time_edit->setMaximumWidth(200);
    date_edit->setMaximumWidth(200);



    name_edit->setEnabled(false);
    estimated_time_edit->setEnabled(false);
    price_edit->setEnabled(false);

    client_select->setModel(clients_model);
    client_select->setModelColumn(1);


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

    // Компоновка віджетів
    info_layout->addWidget(l_name, 0, 0);
    info_layout->addWidget(name_edit, 0, 1);

    info_layout->addWidget(l_client, 1, 0);
    info_layout->addWidget(client_select, 1, 1);

    info_layout->addWidget(l_price, 2, 0);
    info_layout->addWidget(price_edit, 2, 1);
    info_layout->addWidget(price_l, 2, 2);

    info_layout->addWidget(l_estimated_time, 3, 0);
    info_layout->addWidget(estimated_time_edit, 3, 1);
    info_layout->addWidget(estimated_time_l, 3, 2);

    info_layout->addWidget(l_date, 4, 0);
    info_layout->addWidget(date_edit, 4, 1);

    info_layout->addWidget(l_dishes, 5, 0);
    info_layout->addWidget(add_dish_btn, 5, 1);

    buttons_layout->addWidget(accept_btn);
    buttons_layout->addWidget(cancel_btn);


    /// СИГНАЛИ ТА СЛОТИ
    connect(cancel_btn, SIGNAL(clicked()), this, SLOT(close()));

    connect(accept_btn, SIGNAL(clicked()), this, SLOT(add_order()));
    connect(this, SIGNAL(add_order(QString,QString,double,int,QString)), parent, SLOT(add_order(QString,QString,double,int,QString)));

    connect(add_dish_btn, SIGNAL(clicked()), this, SLOT(add_dish()));
}

void AddOrderForm::add_order()
{
    emit add_order(name_edit->text(), client_select->currentText(), price_edit->text().toDouble(), estimated_time_edit->text().toInt(), date_edit->text());
    // ДОДАЙ ОБРОБКУ ПОМИЛОК ТА НАЛАШТУЙ ІНДЕКСУВАННЯ
}

// МОЖНА ДОДАТИ LINEEDIT З МОЖЛИВІСТЮ УКАЗАННЯ КІЛЬКОСТІ ПОРЦІЙ А ТАКОЖ НАЛАШТУВАТИ ЗОВНІШНІЙ ВИГЛЯД
// ПОПЕРШЕ ЦЕ СТВОРЕННЯ SCROLL ОБЛАСТІ, А ПО ДРУГЕ УКАЗАННЯ СТРАВ ПЕРЕД COMBO_BOX ТАКИХ ЯК "СТРАВА 1", "СТРАВА 2" І Т.Д.
void AddOrderForm::add_dish()
{
    add_dish_selects.push_back(new QComboBox);
    add_dish_selects[current_dish_item]->setModel(dishes_model);
    add_dish_selects[current_dish_item]->setModelColumn(1);

    count_dish_edits.push_back(new QLineEdit);
    count_dish_edits[current_dish_item]->setPlaceholderText("Кількість порцій");

    remove_dish_btns.push_back(new QPushButton("x"));
    remove_dish_btns[current_dish_item]->setFixedSize(25, 25);

    info_layout->addWidget(add_dish_selects[current_dish_item], dish_grid_index + 1, 0);
    info_layout->addWidget(count_dish_edits[current_dish_item], dish_grid_index + 1, 1);
    info_layout->addWidget(remove_dish_btns[current_dish_item], dish_grid_index + 1, 2);

    connect(remove_dish_btns[current_dish_item], &QPushButton::clicked, this, std::bind(&AddOrderForm::remove_dish, this, current_dish_item));

    ++dish_grid_index;
    ++current_dish_item;
}

void AddOrderForm::remove_dish(int index)
{
    info_layout->removeWidget(add_dish_selects[index]);
    info_layout->removeWidget(count_dish_edits[index]);
    info_layout->removeWidget(remove_dish_btns[index]);
    delete add_dish_selects[index];
    delete count_dish_edits[index];
    delete remove_dish_btns[index];

    // Вектор не змінюється
//    add_dish_selects.erase(add_dish_selects.begin() + index);
//    remove_dish_btns.erase(remove_dish_btns.begin() + index);
}
