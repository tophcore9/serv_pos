#include "showorderform.h"

ShowOrderForm::ShowOrderForm(QModelIndex order_index, QSqlTableModel *dishes_model, QSqlTableModel *clients_model, QWidget *parent) : QDialog(parent)
{
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
