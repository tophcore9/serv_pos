#include "showmenuform.h"

ShowMenuForm::ShowMenuForm(QModelIndex menu_index, QSqlDatabase db, QWidget *parent) : QDialog(parent)
{
    /// БАЗОВІ НАЛАШТУВАННЯ
    this->setFixedSize(500, 400);
    this->setWindowTitle("Перегляд меню");
    QString menu_name = menu_index.data(0).toString();
    QString menu_id;

    QSqlQuery query(db);
    query.exec("SELECT * FROM Menu");
    while (query.next())
    {
        if (query.value("menu_name").toString() == menu_name)
        {
            menu_id = query.value("menu_id").toString();
            break;
        }
    }

    if (query.exec("SELECT * FROM MenuItems JOIN Dishes ON MenuItems.dish_id = Dishes.dish_id"))
    while (query.next())
    {
        if (query.value("menu_id").toString() == menu_id)
        {
            dishes.push_back(query.value("dish_name").toString());
        }
        else
        {
            // ОБРОБКА ПОМИЛОК
        }
    }


    /// ВІДЖЕТИ
    // Додавання віджетів
    accept_btn = new QPushButton("Підтвердити");
    cancel_btn = new QPushButton("Скасувати");

    // Налаштування віджетів
    QString dshs = "";
    for (int i = 0; i < dishes.size(); ++i)
        dshs += dishes[i] + "\n";
    QLabel *lb = new QLabel(menu_name + "\n" + dshs);


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
    info_layout->addWidget(lb);
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
