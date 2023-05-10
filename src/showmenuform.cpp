#include "showmenuform.h"

ShowMenuForm::ShowMenuForm(QModelIndex menu_index, QSqlDatabase db, QWidget *parent) : QDialog(parent)
{
    QString menu_name = menu_index.data(0).toString();
    QString menu_id;

    QSqlQuery query(db);
    query.exec("SELECT * FROM Menu");
    while (query.next())
    {
        if (query.value("menu_name").toString() == menu_name)
        {
            menu_id = query.value("menu_id").toString();
            break;
        }
    }

    if (query.exec("SELECT * FROM MenuItems JOIN Dishes ON MenuItems.dish_id = Dishes.dish_id"))
    while (query.next())
    {
        if (query.value("menu_id").toString() == menu_id)
        {
            dishes.push_back(query.value("dish_name").toString());
        }
        else
        {
            // ОБРОБКА ПОМИЛОК
        }
    }

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

    QString dshs = "";
    for (int i = 0; i < dishes.size(); ++i)
        dshs += dishes[i] + "\n";
    QLabel *lb = new QLabel(menu_name + "\n" + dshs);
    info_layout->addWidget(lb);
}
