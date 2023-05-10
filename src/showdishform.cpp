#include "showdishform.h"

ShowDishForm::ShowDishForm(QModelIndex dish_index, QSqlDatabase db, QWidget *parent) : QDialog(parent)
{
    /// БАЗОВІ НАЛАШТУВАННЯ
    this->setFixedSize(500, 400);
    this->setWindowTitle("Перегляд страви");
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

    /// ВІДЖЕТИ
    // Додавання віджетів
    QLabel *lb = new QLabel("Name: " + dish_name + "\nPrice: " + dish_price + "\nWeight: " + dish_weight + "\nEstimated time: " + dish_estimated_time +
                    "\nCategory: " + dish_category);

    QPixmap *pixmap = new QPixmap;
    QLabel *picture = new QLabel;

    accept_btn = new QPushButton("Підтвердити");
    cancel_btn = new QPushButton("Скасувати");

    // Налаштування віджетів
    pixmap->load(dish_photo);
    picture->setPixmap(pixmap->scaled(500, 500, Qt::KeepAspectRatio));


    /// МАКЕТИ ТА КОМПОНОВКА
    // Налаштування макетів
    main_layout = new QVBoxLayout;
    info_layout = new QGridLayout;
    buttons_layout = new QHBoxLayout;

    main_layout->addLayout(info_layout);
    main_layout->addLayout(buttons_layout);

    setLayout(main_layout);
    buttons_layout->setAlignment(Qt::AlignRight);

    // Компоновка макетів
    buttons_layout->addWidget(accept_btn);
    buttons_layout->addWidget(cancel_btn);

    // Компоновка віджетів
    info_layout->addWidget(lb);
    info_layout->addWidget(picture);


    /// СИГНАЛИ І СЛОТИ
    connect(accept_btn, SIGNAL(clicked()), this, SLOT(edit_dish()));
    connect(this, SIGNAL(edit_dish(QString,int,double,QString,int,QString)), parent, SLOT(edit_dish(QString,int,double,QString,int,QString)));

    connect(cancel_btn, SIGNAL(clicked()), this, SLOT(close()));
}

void ShowDishForm::edit_dish()
{
    emit edit_dish("", 0, 0.0, "", 0, "");
}
