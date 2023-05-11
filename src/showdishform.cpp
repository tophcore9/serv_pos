#include "showdishform.h"

ShowDishForm::ShowDishForm(QModelIndex dish_index, QSqlTableModel *categories_model, QWidget *parent) : QDialog(parent)
{
    /// БАЗОВІ НАЛАШТУВАННЯ
    this->setFixedSize(600, 500);
    this->setWindowTitle("Перегляд страви");

    QSqlQuery query(categories_model->database());
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
        QMessageBox::critical(this, "Помилка!", "Не вдалось підключитись до бази даних!\n"
                              "Повідомлення БД: " + query.lastError().databaseText() +
                              "\nПовідомлення драйвера: " + query.lastError().driverText());
    }

    /// ВІДЖЕТИ
    // Додавання віджетів
    l_picture = new QLabel("Зображення:");
    pixmap = new QPixmap;
    picture = new QLabel("Помилка завантаження зображення");
    rechoose_picture_btn = new QPushButton("Переобрати");

    l_name = new QLabel("Назва:");
    name_edit = new QLineEdit(dish_name);

    l_weight = new QLabel("Вага:");
    weight_edit = new QLineEdit(dish_weight);
    weight_l = new QLabel("г.");

    l_price = new QLabel("Вартість:");
    price_edit = new QLineEdit(dish_price);
    price_l = new QLabel("грн.");

    l_categories = new QLabel("Категорія:");
    categories_select = new QComboBox;

    l_estimated_time = new QLabel("Очікуваний час приготування:");
    estimated_time_edit = new QLineEdit;
    estimated_time_l = new QLabel("хв.");

    pixmap = new QPixmap;
    picture = new QLabel;

    accept_btn = new QPushButton("Підтвердити");
    cancel_btn = new QPushButton("Скасувати");

    // Налаштування віджетів
    // Розсташування лейблів біля полів
    l_picture->setAlignment(Qt::AlignRight);
    l_name->setAlignment(Qt::AlignRight);
    l_weight->setAlignment(Qt::AlignRight);
    l_price->setAlignment(Qt::AlignRight);
    l_categories->setAlignment(Qt::AlignRight);
    l_estimated_time->setAlignment(Qt::AlignRight);


    // Встановлення статичного розміру полей вводу
    name_edit->setMaximumWidth(200);
    price_edit->setMaximumWidth(200);
    categories_select->setMaximumWidth(200);
    estimated_time_edit->setMaximumWidth(200);
    weight_edit->setMaximumWidth(200);

    categories_select->setModel(categories_model);
    categories_select->setModelColumn(1);
    categories_select->setCurrentText(dish_category);

    pixmap->load(dish_photo);
    picture->setPixmap(pixmap->scaled(300, 300, Qt::KeepAspectRatio));

    name_edit->setText(dish_name);
    weight_edit->setText(dish_weight);
    price_edit->setText(dish_price);
    estimated_time_edit->setText(dish_estimated_time);


    /// МАКЕТИ ТА КОМПОНОВКА
    // Налаштування макетів
    main_layout = new QVBoxLayout;
    info_layout = new QGridLayout;
    buttons_layout = new QHBoxLayout;

    setLayout(main_layout);
    buttons_layout->setAlignment(Qt::AlignBottom);

    // Компоновка макетів
    main_layout->addLayout(info_layout);
    main_layout->addLayout(buttons_layout);

    // Компоновка віджетів
    info_layout->addWidget(l_picture, 0, 0);
    info_layout->addWidget(picture, 0, 1);
    info_layout->addWidget(rechoose_picture_btn, 0, 2);

    info_layout->addWidget(l_name, 1, 0);
    info_layout->addWidget(name_edit, 1, 1);

    info_layout->addWidget(l_weight, 2, 0);
    info_layout->addWidget(weight_edit, 2, 1);
    info_layout->addWidget(weight_l, 2, 2);

    info_layout->addWidget(l_price, 3, 0);
    info_layout->addWidget(price_edit, 3, 1);
    info_layout->addWidget(price_l, 3, 2);

    info_layout->addWidget(l_categories, 4, 0);
    info_layout->addWidget(categories_select, 4, 1);

    info_layout->addWidget(l_estimated_time, 5, 0);
    info_layout->addWidget(estimated_time_edit, 5, 1);
    info_layout->addWidget(estimated_time_l, 5, 2);

    buttons_layout->addWidget(accept_btn);
    buttons_layout->addWidget(cancel_btn);



    /// СИГНАЛИ І СЛОТИ
    connect(accept_btn, SIGNAL(clicked()), this, SLOT(edit_dish()));
    connect(this, SIGNAL(edit_dish(QString,QString,int,double,QString,int,QString)), parent, SLOT(edit_dish(QString,QString,int,double,QString,int,QString)));

    connect(rechoose_picture_btn, SIGNAL(clicked()), this, SLOT(reselect_image()));

    connect(cancel_btn, SIGNAL(clicked()), this, SLOT(cancel_edit_dish()));
}

void ShowDishForm::edit_dish()
{
    // Видалення попереднього зображення
    QFile file_to_delete(dish_photo);
    file_to_delete.open(QIODevice::WriteOnly);
    file_to_delete.remove();
    file_to_delete.close();

    emit edit_dish("", "", 0, 0.0, "", 0, dish_new_photo);
}

void ShowDishForm::reselect_image()
{
    // Обрання нового зображення
    QString file_path = QFileDialog::getOpenFileName(this, "Open File", "/home", "Images (*.png *.jpg *.jpeg)");
    QString img_folder = "../img/" + QFileInfo(file_path).fileName();

    // Створюємо файли
    QFile source(file_path);
    QFile destination(img_folder);

    if (source.open(QIODevice::ReadOnly) && destination.open(QIODevice::WriteOnly))
    {
        if (destination.write(source.readAll()) == source.size())
        {
            // Видалення попереднього зображення
            QFile file_to_delete(dish_new_photo);
            file_to_delete.open(QIODevice::WriteOnly);
            file_to_delete.remove();

            dish_new_photo = img_folder;

            // Закриваємо файли
            source.close();
            destination.close();
            file_to_delete.close();

            // Створюємо зображення
            pixmap->load(dish_new_photo);
            picture->setPixmap(pixmap->scaled(300, 300, Qt::KeepAspectRatio));

            info_layout->addWidget(rechoose_picture_btn, 0, 3, Qt::AlignTop);
        }
    }
    else
    {
        QMessageBox::critical(this, "Помилка!", "Не вдалось відкрити/копіювати файл!\n" + source.errorString());
    }
}

void ShowDishForm::cancel_edit_dish()
{
    // Видалення зображення
    QFile file_to_delete(dish_new_photo);
    file_to_delete.open(QIODevice::WriteOnly);
    file_to_delete.remove();
    file_to_delete.close();
    this->close();
}
