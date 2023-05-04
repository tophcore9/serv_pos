#include "categoriesform.h"

CategoriesForm::CategoriesForm(QSqlTableModel *categories_model, QWidget *parent) : QDialog(parent)
{
    /// БАЗОВІ НАЛАШТУВАННЯ
    this->setFixedSize(500, 600);


    /// ВІДЖЕТИ
    list_view = new QListView;
    add_category_btn = new QPushButton("Додати");
    delete_category_btn = new QPushButton("Видалити");
    exit_btn = new QPushButton("Вийти");

    // Налаштування віджетів
    list_view->setModel(categories_model);
    list_view->setModelColumn(1);


    /// МАКЕТИ ТА КОМПОНОВКА
    main_layout = new QVBoxLayout;
    view_layout = new QHBoxLayout;
    buttons_layout = new QHBoxLayout;
    setLayout(main_layout);

    // Компоновка макетів
    main_layout->addLayout(view_layout);
    main_layout->addLayout(buttons_layout);

    // Компоновка віджетів
    view_layout->addWidget(list_view);

    buttons_layout->addWidget(add_category_btn);
    buttons_layout->addWidget(delete_category_btn);
    buttons_layout->addWidget(exit_btn);


    /// СИГНАЛИ ТА СЛОТИ
    connect(exit_btn, SIGNAL(clicked()), this, SLOT(close()));

    connect(list_view, SIGNAL(clicked(QModelIndex)), this, SLOT(change_category_row(QModelIndex)));

    connect(delete_category_btn, SIGNAL(clicked()), this, SLOT(remove_category_row()));
    connect(this, SIGNAL(remove_category_row(int)), parent, SLOT(remove_category(int)));
}

void CategoriesForm::change_category_row(const QModelIndex index)
{
    current_category = index.row();
}

void CategoriesForm::remove_category_row()
{
    emit remove_category_row(current_category);
}
