#include "categoriesform.h"

CategoriesForm::CategoriesForm(QSqlTableModel *categories_model, QWidget *parent) : QDialog(parent)
{
    /// БАЗОВІ НАЛАШТУВАННЯ
    this->resize(500, 600);



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
}
