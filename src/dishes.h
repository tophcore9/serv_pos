#ifndef DISHES_H
#define DISHES_H

#include <QWidget>
#include <QDebug>
#include <QSqlTableModel>
#include "adddishform.h"

class Dishes : public QWidget
{
    Q_OBJECT
private:
    QSqlTableModel *model;
    QSqlTableModel *categories_model;
    AddDishForm *add_dish_form;
    QWidget *parent;
    QSqlDatabase db;

public:
    explicit Dishes(QSqlDatabase &db, QSqlTableModel *categories_model, QWidget *parent = 0);
    ~Dishes();

    QSqlTableModel* get_model();

signals:

public slots:
    void add_dish();
};

#endif // DISHES_H
