#include "showcategoryform.h"

ShowCategoryForm::ShowCategoryForm(QModelIndex category_index, QWidget *parent) : QDialog(parent)
{
    /// БАЗОВІ НАЛАШТУВАННЯ
    this->setFixedSize(300, 80);
    this->setWindowTitle(tr("Перегляд категорії"));


    /// ВІДЖЕТИ
    // Додавання віджетів
    l_name = new QLabel(tr("Назва категорії:"));
    name_edit = new QLineEdit;

    accept_btn = new QPushButton(tr("Підтвердити"));
    cancel_btn = new QPushButton(tr("Скасувати"));

    // Налаштування віджетів
    name_edit->setText(category_index.data(0).toString());
    past_category_name = name_edit->text();
    new_category_name = name_edit->text();

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

    connect(cancel_btn, SIGNAL(clicked()), this, SLOT(close()));

    connect(name_edit, SIGNAL(textChanged(QString)), this, SLOT(name_changed(QString)));
}

void ShowCategoryForm::edit_category()
{
    emit edit_category(past_category_name, new_category_name);
}

void ShowCategoryForm::name_changed(QString new_name)
{
    new_category_name = new_name;
}
