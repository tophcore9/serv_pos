#include "menuform.h"

MenuForm::MenuForm(QSqlTableModel *menu_model, QWidget *parent) : QDialog(parent)
{
    /// БАЗОВІ НАЛАШТУВАННЯ
    this->setFixedSize(500, 600);
    this->setWindowTitle(tr("Меню"));


    /// ВІДЖЕТИ
    menu_sort = new QComboBox;
    list_view = new QListView;
    add_menu_btn = new QPushButton(tr("Додати"));
    delete_menu_btn = new QPushButton(tr("Видалити"));
    exit_btn = new QPushButton(tr("Вийти"));

    // Налаштування віджетів
    menu_sort->addItem(tr("Сортувати за додаванням"));
    menu_sort->addItem(tr("Сортувати за назвою"));

    list_view->setModel(menu_model);
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
    view_layout->addWidget(menu_sort);
    view_layout->addWidget(list_view);

    buttons_layout->addWidget(add_menu_btn);
    buttons_layout->addWidget(delete_menu_btn);
    buttons_layout->addWidget(exit_btn);


    /// СИГНАЛИ ТА СЛОТИ
    connect(exit_btn, SIGNAL(clicked()), this, SLOT(close_form()));
    connect(this, SIGNAL(reset_form()), parent, SLOT(reset_menu_form()));

    connect(add_menu_btn, SIGNAL(clicked()), parent, SLOT(open_add_menu_form()));

    connect(list_view, SIGNAL(doubleClicked(QModelIndex)), parent, SLOT(open_show_menu_form()));
    connect(this, SIGNAL(send_index(QModelIndex)), parent, SLOT(change_index(QModelIndex)));

    connect(list_view, SIGNAL(clicked(QModelIndex)), this, SLOT(change_menu_row(QModelIndex)));

    // Видалення меню
    connect(delete_menu_btn, SIGNAL(clicked()), this, SLOT(remove_menu_row()));
    connect(this, SIGNAL(remove_menu_row(int)), parent, SLOT(remove(int)));

    connect(menu_sort, SIGNAL(currentIndexChanged(int)), parent, SLOT(change_sort(int)));
}

void MenuForm::change_menu_row(const QModelIndex index)
{
    current_menu = index.row();
    send_index(index);
}

void MenuForm::remove_menu_row()
{
    emit remove_menu_row(current_menu);
}

void MenuForm::close_form()
{
    emit reset_form();
}
