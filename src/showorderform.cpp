#include "showorderform.h"

ShowOrderForm::ShowOrderForm(QModelIndex order_index, QSqlTableModel *clients_model, QSqlTableModel *dishes_model, QWidget *parent) : QDialog(parent)
{
    /// БАЗОВІ НАЛАШТУВАННЯ
    this->setFixedSize(400, 225);
    this->setWindowTitle(tr("Перегляд замовлення"));
    this->dishes_model = dishes_model;


    /// ВІДЖЕТИ
    // Додавання віджетів
    l_name = new QLabel(tr("Ідентифікатор:"));
    name_edit = new QLineEdit;

    l_client = new QLabel(tr("Клієнт:"));
    client_select = new QComboBox;

    l_price = new QLabel(tr("Вартість:"));
    price_edit = new QLineEdit("0");
    price_l = new QLabel(tr("грн."));

    l_estimated_time = new QLabel(tr("Очікуваний час приготування:"));
    estimated_time_edit = new QLineEdit("0");
    estimated_time_l = new QLabel(tr("хв."));

    l_date = new QLabel(tr("Дата:"));
    date_edit = new QLineEdit;

    l_dishes = new QLabel(tr("Страви:"));
    add_dish_btn = new QPushButton("+");

    accept_btn = new QPushButton(tr("Підтвердити"));
    cancel_btn = new QPushButton(tr("Скасувати"));

    // Налаштування віджетів
    // Розсташування лейблів біля полей
    l_name->setAlignment(Qt::AlignRight);
    l_client->setAlignment(Qt::AlignRight);
    l_price->setAlignment(Qt::AlignRight);
    l_estimated_time->setAlignment(Qt::AlignRight);
    l_estimated_time->setMinimumWidth(185);
    l_date->setAlignment(Qt::AlignRight);

    l_dishes->setAlignment(Qt::AlignRight);
    add_dish_btn->setFixedSize(25, 25);

    // Встановлення статичного розміру полей вводу
    name_edit->setMaximumWidth(200);
    client_select->setMaximumWidth(200);
    price_edit->setMaximumWidth(200);
    estimated_time_edit->setMaximumWidth(200);

    date_edit->setMaximumWidth(200);
    date_edit->setInputMask("0000-00-00");

    name_edit->setEnabled(false);
    estimated_time_edit->setEnabled(false);
    price_edit->setEnabled(false);

    client_select->setModel(clients_model);
    client_select->setModelColumn(4);

    QSqlQuery query(clients_model->database());
    if (query.exec("SELECT * FROM Orders JOIN Clients ON Orders.client_id = Clients.client_id"))
    {
        while (query.next())
        {
            if (order_index.data(0).toString() == query.value("order_name"))
            {
                order_id = query.value("order_id").toString();
                name_edit->setText(query.value("order_name").toString());
                client_select->setCurrentText(query.value("client_phone").toString());
                price_edit->setText(query.value("order_price").toString());
                estimated_time_edit->setText(query.value("order_estimated_time").toString());
                date_edit->setText(query.value("order_date").toString());
            }
        }
    }
    else ModelBase::secure_query_exception(query, this);

    if (query.exec("SELECT * FROM OrderItems JOIN Dishes ON OrderItems.dish_id = Dishes.dish_id"))
    {
        while (query.next())
        {
            if (query.value("order_id") == order_id)
            {
                dishes.push_back(query.value("dish_name").toString());
            }
        }
    }
    else ModelBase::secure_query_exception(query, this);

    std::vector<int> counts;
    for (int i = 0; i < dishes.size(); ++i)
        counts.push_back(1);

    for (int i = 1; i < dishes.size(); ++i)
    {
        if (dishes[i] == dishes[i-1])
        {
            dishes.erase(dishes.begin() + i);
            counts.erase(counts.begin() + i);
            --i;
            ++counts[i];
        }
    }

    current_dish_item = 0;
    dish_grid_index = 6;


    /// МАКЕТИ І КОМПОНОВКА
    // Додавання і налаштування макетів
    main_layout = new QVBoxLayout;
    info_layout = new QGridLayout;
    buttons_layout = new QHBoxLayout;

    setLayout(main_layout);
    buttons_layout->setAlignment(Qt::AlignBottom);
    main_layout->setStretch(1, 1);

    // Компоновка макетів
    main_layout->addLayout(info_layout);
    main_layout->addLayout(buttons_layout);

    // Компоновка віджетів
    info_layout->addWidget(l_name, 0, 0);
    info_layout->addWidget(name_edit, 0, 1);

    info_layout->addWidget(l_client, 1, 0);
    info_layout->addWidget(client_select, 1, 1);

    info_layout->addWidget(l_price, 2, 0);
    info_layout->addWidget(price_edit, 2, 1);
    info_layout->addWidget(price_l, 2, 2);

    info_layout->addWidget(l_estimated_time, 3, 0);
    info_layout->addWidget(estimated_time_edit, 3, 1);
    info_layout->addWidget(estimated_time_l, 3, 2);

    info_layout->addWidget(l_date, 4, 0);
    info_layout->addWidget(date_edit, 4, 1);

    info_layout->addWidget(l_dishes, 5, 0);
    info_layout->addWidget(add_dish_btn, 5, 1);

    buttons_layout->addWidget(accept_btn);
    buttons_layout->addWidget(cancel_btn);

    for (int i = 0; i < dishes.size(); ++i)
    {
        add_dish();
        add_dish_selects[i]->setCurrentText(dishes[i]);
    }

    for (int i = 0; i < count_dish_edits.size(); ++i)
        count_dish_edits[i]->setText(QString::number(counts[i]));


    /// СИГНАЛИ І СЛОТИ
    connect(accept_btn, SIGNAL(clicked()), this, SLOT(edit_order()));
    connect(this, SIGNAL(edit_order(QString,QString,QString,double,int,QString,std::vector<QString>)),
            parent, SLOT(edit_order(QString,QString,QString,double,int,QString,std::vector<QString>)));

    connect(cancel_btn, SIGNAL(clicked()), this, SLOT(close()));

    connect(add_dish_btn, SIGNAL(clicked()), this, SLOT(add_dish()));
}

void ShowOrderForm::edit_order()
{
    std::vector<QString> sorted_dishes;

    for (int i = 0; i < add_dish_selects.size(); ++i)
        if (add_dish_selects[i] != NULL)
        {
            for (int j = 0; j < count_dish_edits[i]->text().toInt(); ++j)
                sorted_dishes.push_back(add_dish_selects[i]->currentText());
        }

    emit edit_order(order_id, name_edit->text(), client_select->currentText(), price_edit->text().toDouble(),
                    estimated_time_edit->text().toInt(), date_edit->text(), sorted_dishes);
}

void ShowOrderForm::add_dish()
{
    this->setFixedHeight(height() + 30);

    add_dish_selects.push_back(new QComboBox);
    add_dish_selects[current_dish_item]->setModel(dishes_model);
    add_dish_selects[current_dish_item]->setModelColumn(1);
    add_dish_selects[current_dish_item]->setMaximumWidth(185);

    count_dish_edits.push_back(new QLineEdit);
    count_dish_edits[current_dish_item]->setPlaceholderText(tr("Кількість порцій"));
    count_dish_edits[current_dish_item]->setText("1");
    count_dish_edits[current_dish_item]->setValidator(new QIntValidator);
    count_dish_edits[current_dish_item]->setMaximumWidth(175);

    remove_dish_btns.push_back(new QPushButton("x"));
    remove_dish_btns[current_dish_item]->setFixedSize(25, 25);

    info_layout->addWidget(add_dish_selects[current_dish_item], dish_grid_index + 1, 0);
    info_layout->addWidget(count_dish_edits[current_dish_item], dish_grid_index + 1, 1);
    info_layout->addWidget(remove_dish_btns[current_dish_item], dish_grid_index + 1, 2);

    connect(remove_dish_btns[current_dish_item], &QPushButton::clicked, this, std::bind(&ShowOrderForm::remove_dish, this, current_dish_item));
    connect(add_dish_selects[current_dish_item], &QComboBox::currentTextChanged, this, &ShowOrderForm::refresh_values);
    connect(count_dish_edits[current_dish_item], &QLineEdit::textChanged, this, &ShowOrderForm::refresh_values);

    refresh_values(0);

    ++dish_grid_index;
    ++current_dish_item;
}

void ShowOrderForm::refresh_values(QString)
{
    QSqlQuery query(dishes_model->database());
    QString client_dish;

    if (query.exec("SELECT * FROM Clients JOIN Dishes ON Clients.client_favourite_dish = Dishes.dish_id"))
    {
        while (query.next())
        {
            if (query.value("client_phone") == client_select->currentText())
            {
                client_dish = query.value("dish_name").toString();
            }
        }
    }
    else ModelBase::secure_query_exception(query, this);

    double current_dish_price = 0;
    int current_dish_estimated_time = 0;

    for (int i = 0; i < add_dish_selects.size(); ++i)
    {
        if (add_dish_selects[i] != NULL)
        {
            // Підрахування вартості заказу
            if (query.exec("SELECT * FROM Dishes"))
            {
                while (query.next())
                {
                    if (query.value("dish_name") == add_dish_selects[i]->currentText())
                    {
                        // У випадку співпадання улюбленої страви клієнта діє знижка 12%
                        double est_price = (count_dish_edits[i]->text().toInt() * query.value("dish_price").toDouble());
                        if (query.value("dish_name") == client_dish)
                            current_dish_price += est_price - est_price * 0.12;
                        else
                            current_dish_price += est_price;
                        break;
                    }
                }

            }
            else ModelBase::secure_query_exception(query, this);

            // Знаходження найбільшого часу приготування
            if (query.exec("SELECT * FROM Dishes"))
            {
                while (query.next())
                {
                    if (query.value("dish_name") == add_dish_selects[i]->currentText())
                    {
                        if (count_dish_edits[i]->text().toInt() > 0 && current_dish_estimated_time < query.value("dish_estimated_time").toInt())
                            current_dish_estimated_time = query.value("dish_estimated_time").toInt();
                    }
                }
            }
            else ModelBase::secure_query_exception(query, this);
        }
    }

    // Встановлення вартості та часу приготування заказу
    price_edit->setText(QString::number(current_dish_price));
    estimated_time_edit->setText(QString::number(current_dish_estimated_time));
}

void ShowOrderForm::remove_dish(int index)
{
    this->setFixedHeight(height() - 30);

    // Видалення віджету
    info_layout->removeWidget(add_dish_selects[index]);
    delete add_dish_selects[index];
    add_dish_selects[index] = NULL;

    info_layout->removeWidget(count_dish_edits[index]);
    delete count_dish_edits[index];
    count_dish_edits[index] = NULL;

    info_layout->removeWidget(remove_dish_btns[index]);
    delete remove_dish_btns[index];
    remove_dish_btns[index] = NULL;

    refresh_values(0);
}
