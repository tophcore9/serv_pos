#include "showcategoryform.h"

ShowCategoryForm::ShowCategoryForm(QModelIndex category_index, QWidget *parent) : QDialog(parent)
{
    /// БАЗОВІ НАЛАШТУВАННЯ
    this->setFixedSize(300, 80);
    this->setWindowTitle("Перегляд категорії");
    category_name = category_index.data(0).toString();
    new_category_name = category_name;


    /// ВІДЖЕТИ
    // Додавання віджетів
    l_name = new QLabel("Назва категорії:");
    name_edit = new QLineEdit(category_name);

    accept_btn = new QPushButton("Підтвердити");
    cancel_btn = new QPushButton("Скасувати");

    // Налаштування віджетів

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

    buttons_layout->addWidget(accept_btn);
    buttons_layout->addWidget(cancel_btn);


    /// СИГНАЛИ І СЛОТИ
    connect(accept_btn, SIGNAL(clicked()), this, SLOT(edit_category()));
    connect(this, SIGNAL(edit_category(QString,QString)), parent, SLOT(edit_category(QString,QString)));

    connect(name_edit, SIGNAL(textChanged(QString)), this, SLOT(change_name(QString)));

    connect(cancel_btn, SIGNAL(clicked()), this, SLOT(close()));
}

void ShowCategoryForm::edit_category()
{
    emit edit_category(category_name, new_category_name);
}

void ShowCategoryForm::change_name(QString new_name)
{
    new_category_name = new_name;
}
