#include "adddishform.h"

AddDishForm::AddDishForm(QSqlTableModel *categories_model, QWidget *parent) : QDialog(parent)
{
    /// БАЗОВІ НАЛАШТУВАННЯ
    //this->parent = parent;
    this->categories_model = categories_model;
    this->setWindowTitle(tr("Додати страву"));
    this->setFixedSize(510, 500);


    /// ВІДЖЕТИ
    l_picture = new QLabel(tr("Зображення:"));
    picture_select_btn = new QPushButton(tr("Обрати зображення"));
    pixmap = new QPixmap;
    picture = new QLabel(tr("Помилка завантаження зображення"));
    rechoose_picture_btn = new QPushButton(tr("Переобрати"));

    l_name = new QLabel(tr("Назва:"));
    name_edit = new QLineEdit;

    l_weight = new QLabel(tr("Вага:"));
    weight_edit = new QLineEdit;
    weight_l = new QLabel(tr("г."));

    l_price = new QLabel(tr("Вартість:"));
    price_edit = new QLineEdit;
    price_l = new QLabel(tr("грн."));

    l_categories = new QLabel(tr("Категорія:"));
    categories_select = new QComboBox;

    l_estimated_time = new QLabel(tr("Очікуваний час приготування:"));
    estimated_time_edit = new QLineEdit;
    estimated_time_l = new QLabel(tr("хв."));


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

    // Компоновка віджетів
    info_layout->addWidget(l_picture, 0, 0);
    info_layout->addWidget(picture_select_btn, 0, 1);

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


    /// СИГНАЛИ ТА СЛОТИ
    connect(cancel_btn, SIGNAL(clicked()), this, SLOT(cancel_add_dish()));

    connect(picture_select_btn, SIGNAL(clicked()), this, SLOT(select_image()));

    connect(accept_btn, SIGNAL(clicked()), this, SLOT(add_dish()));
    connect(this, SIGNAL(add_dish(QString,int,double,QString,int,QString)), parent, SLOT(add_dish(QString,int,double,QString,int,QString)));
}

void AddDishForm::select_image()
{
    QString file_path = QFileDialog::getOpenFileName(this, "Open File", "/home", "Images (*.png *.jpg *.jpeg)");
    QString img_folder = "../img/" + QFileInfo(file_path).fileName();

    // Створюємо файли
    QFile source(file_path);
    QFile destination(img_folder);

    // Перевірка і відкриття файлів
    if (source.open(QIODevice::ReadOnly) && destination.open(QIODevice::WriteOnly))
    {
        // Копіюємо з перевіркою на те, що все скопіювалося
        if (destination.write(source.readAll()) == source.size())
        {
            img_path = img_folder;

            // Закриваємо файли тим самим завершуючи копіювання
            source.close();
            destination.close();

            // Створюємо зображення
            pixmap->load(img_path);
            picture->setPixmap(pixmap->scaled(200, 200, Qt::KeepAspectRatio));

            // Заміна кнопки на зображення
            info_layout->replaceWidget(picture_select_btn, picture);
            delete picture_select_btn;

            info_layout->addWidget(rechoose_picture_btn, 0, 3, Qt::AlignTop);

            connect(rechoose_picture_btn, SIGNAL(clicked()), this, SLOT(reselect_image()));
        }
    }
    else
    {
        QMessageBox::critical(this, tr("Помилка!"), tr("Не вдалось відкрити/копіювати файл!\n") + source.errorString());
    }
}

void AddDishForm::reselect_image()
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
            QFile file_to_delete(img_path);
            file_to_delete.open(QIODevice::WriteOnly);
            file_to_delete.remove();

            img_path = img_folder;

            // Закриваємо файли
            source.close();
            destination.close();
            file_to_delete.close();

            // Створюємо зображення
            pixmap->load(img_path);
            picture->setPixmap(pixmap->scaled(200, 200, Qt::KeepAspectRatio));

            info_layout->addWidget(rechoose_picture_btn, 0, 3, Qt::AlignLeft);
        }
    }
    else
    {
        QMessageBox::critical(this, tr("Помилка!"), tr("Не вдалось відкрити/копіювати файл!\n") + source.errorString());
    }
}

void AddDishForm::cancel_add_dish()
{
    // Видалення зображення
    QFile file_to_delete(img_path);
    file_to_delete.open(QIODevice::WriteOnly);
    file_to_delete.remove();
    file_to_delete.close();
    this->close();
}

void AddDishForm::add_dish()
{
    emit add_dish(name_edit->text(), weight_edit->text().toDouble(), price_edit->text().toDouble(),
                  categories_select->currentText(), estimated_time_edit->text().toInt(), img_path);
}
