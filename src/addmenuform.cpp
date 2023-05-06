#include "addmenuform.h"

AddMenuForm::AddMenuForm(QSqlTableModel *menu_model, QSqlTableModel *dishes_model, QWidget *parent) : QDialog(parent)
{
    /// БАЗОВІ НАЛАШТУВАННЯ
    this->setWindowTitle("Додати меню");
    this->setFixedWidth(300);
    dish_index = 1;

    /// ВІДЖЕТИ
    l_name = new QLabel("Назва меню:");
    name_edit = new QLineEdit;

    l_dishes = new QLabel("Страви");
    add_dish_btn = new QPushButton("+");
    dishes_select = new QComboBox;
    remove_dish_btn = new QPushButton("x");

    accept_btn = new QPushButton("Підтвердити");
    cancel_btn = new QPushButton("Скасувати");


    // Налаштування віджетів
    l_name->setAlignment(Qt::AlignRight);

    remove_dish_btn->setMaximumSize(30, 30);
    add_dish_btn->setMaximumSize(30, 30);

    dishes_select->setModel(dishes_model);
    dishes_select->setModelColumn(1);


    /// МАКЕТИ ТА КОМПОНОВКА
    // Налаштування макетів
    main_layout = new QVBoxLayout;
    info_layout = new QGridLayout;
    buttons_layout = new QHBoxLayout;
    setLayout(main_layout);

    buttons_layout->setAlignment(Qt::AlignBottom);

    // Компоновка макетів
    main_layout->addLayout(info_layout);
    main_layout->addLayout(buttons_layout);


    // Компоновка віджетів
    info_layout->addWidget(l_name, 0, 0);
    info_layout->addWidget(name_edit, 0, 1);

    info_layout->addWidget(l_dishes, 1, 0);
    info_layout->addWidget(add_dish_btn, 2, 0);
//    info_layout->addWidget(dishes_select, 1, 0);
//    info_layout->addWidget(remove_dish_btn, 1, 1);

    buttons_layout->addWidget(accept_btn);
    buttons_layout->addWidget(cancel_btn);


    /// СИГНАЛИ ТА СЛОТИ
    connect(cancel_btn, SIGNAL(clicked()), this, SLOT(close()));

    connect(accept_btn, SIGNAL(clicked()), this, SLOT(add_menu()));
    connect(this, SIGNAL(add_menu(QString)), parent, SLOT(add_menu(QString)));

    connect(add_dish_btn, SIGNAL(clicked()), this, SLOT(add_first_dish()));
}

void AddMenuForm::add_first_dish()
{
    //info_layout->addWidget(add_dish_btn, );
}

void AddMenuForm::add_menu()
{
    emit add_menu(name_edit->text());
}
