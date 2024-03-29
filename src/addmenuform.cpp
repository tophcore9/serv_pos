#include "addmenuform.h"

AddMenuForm::AddMenuForm(QSqlTableModel *menu_model, QSqlTableModel *dishes_model, QWidget *parent) : QDialog(parent)
{
    /// БАЗОВІ НАЛАШТУВАННЯ
    this->setWindowTitle(tr("Додати меню"));
    this->setFixedSize(300, 110);
    this->dishes_model = dishes_model;
    dish_grid_index = 2;
    current_dish_item = 0;

    /// ВІДЖЕТИ
    l_name = new QLabel(tr("Назва меню:"));
    name_edit = new QLineEdit;

    l_dishes = new QLabel(tr("Страви:"));
    add_dish_btn = new QPushButton("+");
    add_dish_selects.push_back(new QComboBox);

    accept_btn = new QPushButton(tr("Підтвердити"));
    cancel_btn = new QPushButton(tr("Скасувати"));


    // Налаштування віджетів
    l_name->setAlignment(Qt::AlignRight);
    l_dishes->setAlignment(Qt::AlignRight);
    l_dishes->setMinimumWidth(175);

    add_dish_btn->setMaximumSize(25, 25);



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
    info_layout->addWidget(add_dish_btn, 1, 1);

    buttons_layout->addWidget(accept_btn);
    buttons_layout->addWidget(cancel_btn);


    /// СИГНАЛИ ТА СЛОТИ
    connect(cancel_btn, SIGNAL(clicked()), this, SLOT(close()));

    connect(accept_btn, SIGNAL(clicked()), this, SLOT(add_menu()));
    connect(this, SIGNAL(add_menu(QString,std::vector<QString>)), parent, SLOT(add_menu(QString,std::vector<QString>)));

    connect(add_dish_btn, SIGNAL(clicked()), this, SLOT(add_dish()));
}

void AddMenuForm::add_dish()
{
    this->setFixedHeight(height() + 30);

    add_dish_selects.push_back(new QComboBox);
    add_dish_selects[current_dish_item]->setModel(dishes_model);
    add_dish_selects[current_dish_item]->setModelColumn(1);
    add_dish_selects[current_dish_item]->setMaximumWidth(175);

    remove_dish_btns.push_back(new QPushButton("x"));
    remove_dish_btns[current_dish_item]->setFixedSize(25, 25);

    info_layout->addWidget(add_dish_selects[current_dish_item], dish_grid_index + 1, 0);
    info_layout->addWidget(remove_dish_btns[current_dish_item], dish_grid_index + 1, 1);

    connect(remove_dish_btns[current_dish_item], &QPushButton::clicked, this, std::bind(&AddMenuForm::remove_dish, this, current_dish_item));

    ++dish_grid_index;
    ++current_dish_item;
}

void AddMenuForm::add_menu()
{
    for (int i = 0; i < add_dish_selects.size() - 1; ++i)
        if (add_dish_selects[i] != NULL)
            dishes.push_back(add_dish_selects[i]->currentText());

    emit add_menu(name_edit->text(), dishes);
}

void AddMenuForm::remove_dish(int index)
{
    this->setFixedHeight(height() - 30);

    info_layout->removeWidget(add_dish_selects[index]);
    info_layout->removeWidget(remove_dish_btns[index]);

    delete add_dish_selects[index];
    add_dish_selects[index] = NULL;

    delete remove_dish_btns[index];
    remove_dish_btns[index] = NULL;
}
