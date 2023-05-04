#ifndef CATEGORIES_H
#define CATEGORIES_H

#include <QtWidgets>
#include <QDebug>
#include <QSqlTableModel>
#include "categoriesform.h"

class Categories : public QWidget
{
    Q_OBJECT

private:
    QSqlTableModel *model;
    CategoriesForm *categories_form;
    QWidget *parent;

public:
    explicit Categories(QSqlDatabase &db, QWidget *parent = 0);

    QSqlTableModel* get_model();

signals:

public slots:
    void add_category();
    void open_categories();
    void remove_category(int);
};

#endif // CATEGORIES_H
