#include "showmenuform.h"

ShowMenuForm::ShowMenuForm(QModelIndex menu_index, QSqlDatabase db, QWidget *parent) : QDialog(parent)
{
    /// БАЗОВІ НАЛАШТУВАННЯ
    this->setFixedWidth(300);
    this->setWindowTitle("Перегляд меню");
    QString menu_name = menu_index.data(0).toString();
    QString menu_id;

    QSqlQuery query(db);
    if (query.exec("SELECT * FROM Menu"))
    {
        while (query.next())
        {
            if (query.value("menu_name").toString() == menu_name)
            {
                menu_id = query.value("menu_id").toString();
                break;
            }
        }
    }
    else
    {
        QMessageBox::critical(this, "Помилка!", "Не вдалось підключитись до бази даних!\n"
                              "Повідомлення БД: " + db.lastError().databaseText() +
                              "\nПовідомлення драйвера: " + db.lastError().driverText());
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
        QMessageBox::critical(this, "Помилка!", "Не вдалось підключитись до бази даних!\n"
                              "Повідомлення БД: " + db.lastError().databaseText() +
                              "\nПовідомлення драйвера: " + db.lastError().driverText());
    }

    /// ВІДЖЕТИ
    // Додавання віджетів
    l_name = new QLabel("Назва меню:");
    name_edit = new QLineEdit;

    l_dishes = new QLabel("Страви:");
    add_dish_btn = new QPushButton("+");
    add_dish_selects.push_back(new QComboBox);

    accept_btn = new QPushButton("Підтвердити");
    cancel_btn = new QPushButton("Скасувати");

    // Налаштування віджетів
    l_name->setAlignment(Qt::AlignRight);
    name_edit->setText(menu_name);
    add_dish_btn->setMaximumSize(25, 25);


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


    /// СИГНАЛИ І СЛОТИ
    connect(accept_btn, SIGNAL(clicked()), this, SLOT(edit_menu()));
    connect(this, SIGNAL(edit_menu(QString,std::vector<QString>)), parent, SLOT(edit_menu(QString,std::vector<QString>)));

    connect(cancel_btn, SIGNAL(clicked()), this, SLOT(close()));
}

void ShowMenuForm::edit_menu()
{
    emit edit_menu("", {""});
}
