#include "dishes.h"

Dishes::Dishes(QSqlDatabase &db, QSqlTableModel *categories_model, QWidget *parent) : QWidget(parent)
{
    this->categories_model = categories_model;
    this->parent = parent;
    model = new QSqlTableModel(parent, db);
    model->setTable("Dishes");
    model->select();

    // Обробка фото
//    QLabel *photo = new QLabel;
//    QPixmap *photo_pixmap = new QPixmap;
//    photo_pixmap->load("../img/img2.jpg");
//    photo->setPixmap(photo_pixmap->scaled(200, photo->height(), Qt::KeepAspectRatio));

//    main_layout->addWidget(photo);
}

QSqlTableModel *Dishes::get_model()
{
    return model;
}

void Dishes::remove_dish(int index)
{
    if (model->rowCount() > index)
    {
        model->removeRow(index);
        model->select();
    }
    else qDebug() << "Incorect index";
}

void Dishes::add_dish()
{
    add_dish_form = new AddDishForm(categories_model, this);
    add_dish_form->setModal(true);
    add_dish_form->show();
}
