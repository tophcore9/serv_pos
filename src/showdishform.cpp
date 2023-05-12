#include "showdishform.h"

ShowDishForm::ShowDishForm(QModelIndex dish_index, QSqlTableModel *categories_model, QWidget *parent) : QDialog(parent)
{
    /// БАЗОВІ НАЛАШТУВАННЯ
    this->setFixedSize(600, 500);
    this->setWindowTitle(tr("Перегляд страви"));


    /// ВІДЖЕТИ
    // Додавання віджетів
    l_picture = new QLabel(tr("Зображення:"));
    pixmap = new QPixmap;
    picture = new QLabel(tr("Помилка завантаження зображення"));
    rechoose_picture_btn = new QPushButton(tr("Переобрати"));

    l_name = new QLabel(tr("Назва:"));
    name_edit = new QLineEdit;

    l_weight = new QLabel(tr("Вага:"));
    weight_edit = new QLineEdit;
    weight_l = new QLabel("г.");

    l_price = new QLabel(tr("Вартість:"));
    price_edit = new QLineEdit;
    price_l = new QLabel(tr("грн."));

    l_categories = new QLabel(tr("Категорія:"));
    categories_select = new QComboBox;

    l_estimated_time = new QLabel(tr("Очікуваний час приготування:"));
    estimated_time_edit = new QLineEdit;
    estimated_time_l = new QLabel(tr("хв."));

    pixmap = new QPixmap;
    picture = new QLabel;

    accept_btn = new QPushButton(tr("Підтвердити"));
    cancel_btn = new QPushButton(tr("Скасувати"));

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
    price_edit->setValidator(new QDoubleValidator);

    categories_select->setMaximumWidth(200);

    estimated_time_edit->setMaximumWidth(200);
    estimated_time_edit->setValidator(new QIntValidator);

    weight_edit->setMaximumWidth(200);
    weight_edit->setValidator(new QIntValidator);

    categories_select->setModel(categories_model);
    categories_select->setModelColumn(1);


    QSqlQuery query(categories_model->database());
    if (query.exec("SELECT * FROM Dishes JOIN Categories ON Dishes.dish_category = Categories.category_id"))
    {
        while (query.next())
        {
            if (dish_index.data(0).toString() == query.value("dish_name"))
            {
                name_edit->setText(query.value("dish_name").toString());
                new_dish_name = name_edit->text();
                past_dish_name = name_edit->text();

                price_edit->setText(query.value("dish_price").toString());
                new_dish_price = price_edit->text();

                weight_edit->setText(query.value("dish_weight").toString());
                new_dish_weight = weight_edit->text();

                categories_select->setCurrentText(query.value("category_name").toString());
                new_dish_category = categories_select->currentText();
                categories_select->setCurrentText(new_dish_category);

                estimated_time_edit->setText(query.value("dish_estimated_time").toString());
                new_dish_estimated_time = estimated_time_edit->text();

                past_dish_photo = query.value("dish_photo").toString();
                new_dish_photo = "__new";
                pixmap->load(past_dish_photo);
                picture->setPixmap(pixmap->scaled(300, 300, Qt::KeepAspectRatio));
            }
        }
    }
    else
    {
        // Обробка помилок
        QMessageBox::critical(this, tr("Помилка!"), tr("Не вдалось виконати запит!\n") +
                              tr("Повідомлення БД: ") + query.lastError().databaseText() +
                              tr("\nПовідомлення драйвера: ") + query.lastError().driverText());
    }


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

    connect(name_edit, SIGNAL(textChanged(QString)), this, SLOT(changed_name(QString)));
    connect(price_edit, SIGNAL(textChanged(QString)), this, SLOT(changed_price(QString)));
    connect(weight_edit, SIGNAL(textChanged(QString)), this, SLOT(changed_weight(QString)));
    connect(categories_select, SIGNAL(currentTextChanged(QString)), this, SLOT(changed_category(QString)));
    connect(estimated_time_edit, SIGNAL(textChanged(QString)), this, SLOT(changed_time(QString)));
}

void ShowDishForm::edit_dish()
{
    if (new_dish_photo == "__new")
    {
        new_dish_photo = past_dish_photo;
    }
    else
    {
        // Видалення попереднього зображення
        QFile file_to_delete(past_dish_photo);
        file_to_delete.open(QIODevice::WriteOnly);
        file_to_delete.remove();
        file_to_delete.close();
    }

    emit edit_dish(past_dish_name, new_dish_name, new_dish_weight.toInt(), new_dish_price.toDouble(), new_dish_category, new_dish_estimated_time.toInt(), new_dish_photo);
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
            QFile file_to_delete(new_dish_photo);
            file_to_delete.open(QIODevice::WriteOnly);
            file_to_delete.remove();

            new_dish_photo = img_folder;

            // Закриваємо файли
            source.close();
            destination.close();
            file_to_delete.close();

            // Створюємо зображення
            pixmap->load(new_dish_photo);
            picture->setPixmap(pixmap->scaled(300, 300, Qt::KeepAspectRatio));

            info_layout->addWidget(rechoose_picture_btn, 0, 3, Qt::AlignTop);
        }
    }
    else
    {
        QMessageBox::critical(this, tr("Помилка!"), tr("Не вдалось відкрити/копіювати файл!\n") + source.errorString());
    }
}

void ShowDishForm::cancel_edit_dish()
{
    // Видалення зображення
    QFile file_to_delete(new_dish_photo);
    file_to_delete.open(QIODevice::WriteOnly);
    file_to_delete.remove();
    file_to_delete.close();
    this->close();
}

void ShowDishForm::changed_name(QString new_name)
{
    new_dish_name = new_name;
}

void ShowDishForm::changed_price(QString new_price)
{
    new_dish_price = new_price;
}

void ShowDishForm::changed_weight(QString new_weight)
{
    new_dish_weight = new_weight;
}

void ShowDishForm::changed_category(QString new_category)
{
    new_dish_category = new_category;
}

void ShowDishForm::changed_time(QString new_time)
{
    new_dish_estimated_time = new_time;
}
