#include "adddishform.h"

AddDishForm::AddDishForm(QSqlTableModel *categories_model, QWidget *parent) : QDialog(parent)
{
    this->parent = parent;
    this->categories_model = categories_model;
    this->setWindowTitle("Додати страву");
    this->setFixedSize(350, 500);

    // ВІДЖЕТИ
    accept_btn = new QPushButton("Підтвердити");
    cancel_btn = new QPushButton("Скасувати");

    // МАКЕТИ ТА КОМПОНОВКА
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
    buttons_layout->addWidget(accept_btn);
    buttons_layout->addWidget(cancel_btn);

    // СИГНАЛИ ТА СЛОТИ
    connect(cancel_btn, SIGNAL(clicked()), this, SLOT(close()));
}
