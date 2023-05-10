#ifndef DISHES_H
#define DISHES_H

#include <QWidget>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>

#include "adddishform.h"
#include "showdishform.h"

class Dishes : public QWidget
{
    Q_OBJECT
private:
    QSqlTableModel *model;
    QSqlTableModel *categories_model;
    QModelIndex index;

    AddDishForm *add_dish_form;
    ShowDishForm *show_dish_form;

    QWidget *parent;

public:
    explicit Dishes(QSqlDatabase &db, QSqlTableModel *categories_model, QWidget *parent = 0);

    QSqlTableModel* get_model();

signals:

public slots:
    void change_index(const QModelIndex index);
    void open_show_dish_form();
    void open_add_dish_form();
    void remove_dish(int);
    void add_dish(QString name, int weight, double price, QString category, int estimated_time, QString url);
    void edit_dish(QString name, int weight, double price, QString category, int estimated_time, QString url);
};

#endif // DISHES_H
