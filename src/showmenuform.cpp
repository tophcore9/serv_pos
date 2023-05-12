#include "showmenuform.h"

ShowMenuForm::ShowMenuForm(QModelIndex menu_index, QSqlTableModel *dishes_model, QWidget *parent) : QDialog(parent)
{
    /// БАЗОВІ НАЛАШТУВАННЯ
    this->setFixedWidth(300);
    this->setWindowTitle(tr("Перегляд меню"));
    this->dishes_model = dishes_model;
    past_menu_name = menu_index.data(0).toString();
    new_menu_name = past_menu_name;


    /// ВІДЖЕТИ
    // Додавання віджетів
    l_name = new QLabel(tr("Назва меню:"));
    name_edit = new QLineEdit;

    l_dishes = new QLabel(tr("Страви:"));
    add_dish_btn = new QPushButton("+");
    add_dish_selects.push_back(new QComboBox);

    accept_btn = new QPushButton(tr("Підтвердити"));
    cancel_btn = new QPushButton(tr("Скасувати"));

    // Налаштування віджетів
    l_name->setAlignment(Qt::AlignRight);
    name_edit->setText(past_menu_name);
    add_dish_btn->setMaximumSize(25, 25);

    QSqlQuery query(dishes_model->database());
    if (query.exec("SELECT * FROM Menu"))
    {
        while (query.next())
        {
            if (query.value("menu_name").toString() == past_menu_name)
            {
                menu_id = query.value("menu_id").toString();
                break;
            }
        }
    }
    else
    {
        QMessageBox::critical(this, tr("Помилка!"), tr("Не вдалось виконати запит!\n") +
                              tr("Повідомлення БД: ") + query.lastError().databaseText() +
                              tr("\nПовідомлення драйвера: ") + query.lastError().driverText());
    }

    if (query.exec("SELECT * FROM MenuItems JOIN Dishes ON MenuItems.dish_id = Dishes.dish_id"))
    {
        while (query.next())
        {
            if (query.value("menu_id").toString() == menu_id)
            {
                dishes.push_back(query.value("dish_name").toString());
            }
        }
    }
    else
    {
        QMessageBox::critical(this, tr("Помилка!"), tr("Не вдалось виконати запит!\n") +
                              tr("Повідомлення БД: ") + query.lastError().databaseText() +
                              tr("\nПовідомлення драйвера: ") + query.lastError().driverText());
    }

    current_dish_item = 0;
    dish_grid_index = 2 + current_dish_item;


    /// МАКЕТИ І КОМПОНОВКА
    // Додавання і налаштування макетів
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

    for (int i = 0; i < dishes.size(); ++i)
    {
        add_dish();
        add_dish_selects[i]->setCurrentText(dishes[i]);
    }


    /// СИГНАЛИ І СЛОТИ
    connect(accept_btn, SIGNAL(clicked()), this, SLOT(edit_menu()));
    connect(this, SIGNAL(edit_menu(QString,QString,std::vector<QString>)), parent, SLOT(edit_menu(QString,QString,std::vector<QString>)));

    connect(cancel_btn, SIGNAL(clicked()), this, SLOT(close()));

    connect(add_dish_btn, SIGNAL(clicked()), this, SLOT(add_dish()));
}

void ShowMenuForm::edit_menu()
{
    emit edit_menu("", "", {""});
}

void ShowMenuForm::add_dish()
{
    add_dish_selects.push_back(new QComboBox);
    add_dish_selects[current_dish_item]->setModel(dishes_model);
    add_dish_selects[current_dish_item]->setModelColumn(1);

    remove_dish_btns.push_back(new QPushButton("x"));
    remove_dish_btns[current_dish_item]->setFixedSize(25, 25);

    info_layout->addWidget(add_dish_selects[current_dish_item], dish_grid_index + 1, 0);
    info_layout->addWidget(remove_dish_btns[current_dish_item], dish_grid_index + 1, 1);

    connect(remove_dish_btns[current_dish_item], &QPushButton::clicked, this, std::bind(&ShowMenuForm::remove_dish, this, current_dish_item));

    ++dish_grid_index;
    ++current_dish_item;
}

void ShowMenuForm::remove_dish(int index)
{
    info_layout->removeWidget(add_dish_selects[index]);
    info_layout->removeWidget(remove_dish_btns[index]);

    delete add_dish_selects[index];
    add_dish_selects[index] = NULL;

    delete remove_dish_btns[index];
    remove_dish_btns[index] = NULL;
}
