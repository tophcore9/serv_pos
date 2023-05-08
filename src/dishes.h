#ifndef DISHES_H
#define DISHES_H

#include <QWidget>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include "adddishform.h"

class Dishes : public QWidget
{
    Q_OBJECT
private:
    QSqlTableModel *model;
    QSqlTableModel *categories_model;
    AddDishForm *add_dish_form;
    QWidget *parent;

public:
    explicit Dishes(QSqlDatabase &db, QSqlTableModel *categories_model, QWidget *parent = 0);

    QSqlTableModel* get_model();

signals:

public slots:
    void open_add_dish_form();
    void remove_dish(int);
    void add_dish(QString name, double weight, double price, QString category, int estimated_time, QString url);
};

#endif // DISHES_H
