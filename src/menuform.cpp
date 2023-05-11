#include "menuform.h"

MenuForm::MenuForm(QSqlTableModel *menu_model, QWidget *parent) : QDialog(parent)
{
    /// БАЗОВІ НАЛАШТУВАННЯ
    this->setFixedSize(500, 600);
    this->setWindowTitle(tr("Меню"));


    /// ВІДЖЕТИ
    list_view = new QListView;
    add_menu_btn = new QPushButton(tr("Додати"));
    delete_menu_btn = new QPushButton(tr("Видалити"));
    exit_btn = new QPushButton(tr("Вийти"));

    // Налаштування віджетів
    list_view->setModel(menu_model);
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

    buttons_layout->addWidget(add_menu_btn);
    buttons_layout->addWidget(delete_menu_btn);
    buttons_layout->addWidget(exit_btn);


    /// СИГНАЛИ ТА СЛОТИ
    connect(exit_btn, SIGNAL(clicked()), this, SLOT(close()));
    connect(add_menu_btn, SIGNAL(clicked()), parent, SLOT(open_add_menu_form()));

    connect(list_view, SIGNAL(doubleClicked(QModelIndex)), parent, SLOT(open_show_menu_form()));
    connect(this, SIGNAL(send_index(QModelIndex)), parent, SLOT(change_index(QModelIndex)));

    connect(list_view, SIGNAL(clicked(QModelIndex)), this, SLOT(change_menu_row(QModelIndex)));

    // Видалення меню
    connect(delete_menu_btn, SIGNAL(clicked()), this, SLOT(remove_menu_row()));
    connect(this, SIGNAL(remove_menu_row(int)), parent, SLOT(remove_menu(int)));
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
