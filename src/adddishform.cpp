#include "adddishform.h"

AddDishForm::AddDishForm(QSqlTableModel *categories_model, QWidget *parent) : QDialog(parent)
{
    //this->parent = parent;
    this->categories_model = categories_model;
    this->setWindowTitle("Додати страву");
    this->setFixedSize(400, 500);

    // ВІДЖЕТИ
    l_name = new QLabel("Назва:");
    name_edit = new QLineEdit;

    l_weight = new QLabel("Вага:");
    weight_edit = new QLineEdit;
    weight_l = new QLabel("кг.");

    l_price = new QLabel("Вартість:");
    price_edit = new QLineEdit;
    price_l = new QLabel("грн.");

    l_categories = new QLabel("Категорія:");
    categories_select = new QComboBox;

    l_estimated_time = new QLabel("Очікуваний час приготування:");
    estimated_time_edit = new QLineEdit;
    estimated_time_l = new QLabel("хв.");


    accept_btn = new QPushButton("Підтвердити");
    cancel_btn = new QPushButton("Скасувати");


    // Налаштування віджетів
    // Розсташування лейблів біля полів
    l_name->setAlignment(Qt::AlignRight);
    l_weight->setAlignment(Qt::AlignRight);
    l_price->setAlignment(Qt::AlignRight);
    l_categories->setAlignment(Qt::AlignRight);
    l_estimated_time->setAlignment(Qt::AlignRight);

    categories_select->setModel(categories_model);
    categories_select->setModelColumn(1);


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
    info_layout->addWidget(l_name, 0, 0);
    info_layout->addWidget(name_edit, 0, 1);

    info_layout->addWidget(l_weight, 1, 0);
    info_layout->addWidget(weight_edit, 1, 1);
    info_layout->addWidget(weight_l, 1, 2);

    info_layout->addWidget(l_price, 2, 0);
    info_layout->addWidget(price_edit, 2, 1);
    info_layout->addWidget(price_l, 2, 2);

    info_layout->addWidget(l_categories, 3, 0);
    info_layout->addWidget(categories_select, 3, 1);

    info_layout->addWidget(l_estimated_time, 4, 0);
    info_layout->addWidget(estimated_time_edit, 4, 1);
    info_layout->addWidget(estimated_time_l, 4, 2);

    buttons_layout->addWidget(accept_btn);
    buttons_layout->addWidget(cancel_btn);

    // СИГНАЛИ ТА СЛОТИ
    connect(cancel_btn, SIGNAL(clicked()), this, SLOT(close()));
}
