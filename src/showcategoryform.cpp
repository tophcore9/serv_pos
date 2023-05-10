#include "showcategoryform.h"

ShowCategoryForm::ShowCategoryForm(QModelIndex category_index, QWidget *parent) : QDialog(parent)
{
    this->setFixedSize(500, 400);
    this->setWindowTitle("Перегляд категорії");
    QString category_name = category_index.data(0).toString();
    setWindowTitle(category_name);

    accept_btn = new QPushButton("Підтвердити");
    cancel_btn = new QPushButton("Скасувати");

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

    buttons_layout->addWidget(accept_btn);
    buttons_layout->addWidget(cancel_btn);

    connect(accept_btn, SIGNAL(clicked()), this, SLOT(edit_category()));
    connect(this, SIGNAL(edit_category(QString)), parent, SLOT(edit_category(QString)));

    connect(cancel_btn, SIGNAL(clicked()), this, SLOT(close()));
}

void ShowCategoryForm::edit_category()
{
    emit edit_category("");
}
