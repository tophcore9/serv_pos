#include "showdishform.h"

ShowDishForm::ShowDishForm(QModelIndex dish_index, QSqlDatabase db, QWidget *parent) : QDialog(parent)
{
    QString dish_name, dish_price, dish_weight, dish_category, dish_estimated_time, dish_photo;

    QSqlQuery query(db);
    if (query.exec("SELECT * FROM Dishes JOIN Categories ON Dishes.dish_category = Categories.category_id"))
    {
        while (query.next())
        {
            if (dish_index.data(0).toString() == query.value("dish_name"))
            {
                dish_name = query.value("dish_name").toString();
                dish_price = query.value("dish_price").toString();
                dish_weight = query.value("dish_weight").toString();
                dish_category = query.value("category_name").toString();
                dish_estimated_time = query.value("dish_estimated_time").toString();
                dish_photo = query.value("dish_photo").toString();
            }
        }
    }
    else
    {
        // Обробка помилок
        qDebug() << query.lastError().text();
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

    // ТИМЧАСОВЕ
    QLabel *lb = new QLabel("Name: " + dish_name + "\nPrice: " + dish_price + "\nWeight: " + dish_weight + "\nEstimated time: " + dish_estimated_time +
                    "\nCategory: " + dish_category + "\nPhoto: " + dish_photo);
    info_layout->addWidget(lb);
}
