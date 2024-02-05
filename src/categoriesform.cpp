#include "categoriesform.h"

CategoriesForm::CategoriesForm(QSqlTableModel *categories_model, QWidget *parent) : QDialog(parent)
{
    /// БАЗОВІ НАЛАШТУВАННЯ
    this->setWindowTitle(tr("Категорії"));
    this->setFixedSize(500, 600);


    /// ВІДЖЕТИ
    categories_sort = new QComboBox;
    list_view = new QListView;
    add_category_btn = new QPushButton(tr("Додати"));
    delete_category_btn = new QPushButton(tr("Видалити"));
    exit_btn = new QPushButton(tr("Вийти"));

    // Налаштування віджетів
    categories_sort->addItem(tr("Сортувати за додаванням"));
    categories_sort->addItem(tr("Сортувати за назвою"));

    list_view->setModel(categories_model);
    list_view->setModelColumn(1);


    /// МАКЕТИ ТА КОМПОНОВКА
    main_layout = new QVBoxLayout;
    view_layout = new QVBoxLayout;
    buttons_layout = new QHBoxLayout;
    setLayout(main_layout);

    // Компоновка макетів
    main_layout->addLayout(view_layout);
    main_layout->addLayout(buttons_layout);

    // Компоновка віджетів
    view_layout->addWidget(categories_sort);
    view_layout->addWidget(list_view);

    buttons_layout->addWidget(add_category_btn);
    buttons_layout->addWidget(delete_category_btn);
    buttons_layout->addWidget(exit_btn);


    /// СИГНАЛИ ТА СЛОТИ
    connect(exit_btn, SIGNAL(clicked()), this, SLOT(close_form()));
    connect(this, SIGNAL(reset_form()), parent, SLOT(reset_categories_form()));

    connect(list_view, SIGNAL(doubleClicked(QModelIndex)), parent, SLOT(open_show_category_form()));

    connect(list_view, SIGNAL(clicked(QModelIndex)), this, SLOT(change_category_row(QModelIndex)));
    connect(this, SIGNAL(send_index(QModelIndex)), parent, SLOT(change_index(QModelIndex)));

    connect(delete_category_btn, SIGNAL(clicked()), this, SLOT(remove_category_row()));
    connect(this, SIGNAL(remove_category_row(int)), parent, SLOT(remove(int)));

    connect(add_category_btn, SIGNAL(clicked()), parent, SLOT(open_add_category_form()));

    connect(categories_sort, SIGNAL(currentIndexChanged(int)), parent, SLOT(change_sort(int)));
}

void CategoriesForm::change_category_row(const QModelIndex index)
{
    current_category = index.row();
    send_index(index);
}

void CategoriesForm::remove_category_row()
{
    emit remove_category_row(current_category);
}

void CategoriesForm::close_form()
{
    emit reset_form();
}
