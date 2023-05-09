#include "showorderform.h"

ShowOrderForm::ShowOrderForm(QModelIndex order_index, QModelIndex dish_index, QModelIndex client_index, QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("order:" + QString::number(order_index.row()) + " dish:" + QString::number(dish_index.row()) + " client:" + QString::number(client_index.row()));
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

}
