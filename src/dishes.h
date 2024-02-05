#ifndef DISHES_H
#define DISHES_H

#include "modelbase.h" // BASE-CLASS

#include "adddishform.h"
#include "showdishform.h"

class Dishes : public ModelBase
{
    Q_OBJECT
private:
    QSqlTableModel *categories_model;

    AddDishForm *add_dish_form;
    ShowDishForm *show_dish_form;

public:
    explicit Dishes(QSqlDatabase &db, QSqlTableModel *categories_model, QWidget *parent = 0);

signals:

public slots:
    void open_show_dish_form();
    void open_add_dish_form();
    void add_dish(QString name, int weight, double price, QString category, int estimated_time, QString url);
    void edit_dish(QString default_name, QString name, int weight, double price, QString category, int estimated_time, QString url);
};

#endif // DISHES_H
