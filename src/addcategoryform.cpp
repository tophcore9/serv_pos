#include "addcategoryform.h"

AddCategoryForm::AddCategoryForm(QSqlTableModel *categories_model, QWidget *parent) : QDialog(parent)
{
    /// БАЗОВІ НАЛАШТУВАННЯ
    this->setWindowTitle(tr("Додати категорію"));
    this->setFixedSize(300, 80);

    /// ВІДЖЕТИ
    l_name = new QLabel("Назва категорії:");
    name_edit = new QLineEdit;

    accept_btn = new QPushButton("Підтвердити");
    cancel_btn = new QPushButton("Скасувати");


    // Налаштування віджетів
    l_name->setAlignment(Qt::AlignRight);


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

    buttons_layout->addWidget(accept_btn);
    buttons_layout->addWidget(cancel_btn);


    /// СИГНАЛИ ТА СЛОТИ
    connect(cancel_btn, SIGNAL(clicked()), this, SLOT(close()));

    connect(accept_btn, SIGNAL(clicked()), this, SLOT(add_category()));
    connect(this, SIGNAL(add_category(QString)), parent, SLOT(add_category(QString)));
}

void AddCategoryForm::add_category()
{
    emit add_category(name_edit->text());
}
