#include "showcategoryform.h"

ShowCategoryForm::ShowCategoryForm(QModelIndex category_index, QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle(QString::number(category_index.row()));
    /// МАКЕТИ ТА КОМПОНОВКА
    // Налаштування макетів
//    main_layout = new QVBoxLayout;
//    info_layout = new QGridLayout;
//    buttons_layout = new QHBoxLayout;
//    setLayout(main_layout);

//    // Компоновка макетів
//    main_layout->addLayout(info_layout);
//    main_layout->addLayout(buttons_layout);

//    buttons_layout->setAlignment(Qt::AlignBottom);

//    info_layout->addWidget(table, 0, 0);
}
