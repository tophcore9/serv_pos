#ifndef CATEGORIES_H
#define CATEGORIES_H

#include <QtWidgets>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlQuery>
#include "categoriesform.h"
#include "addcategoryform.h"

class Categories : public QWidget
{
    Q_OBJECT

private:
    QSqlTableModel *model;
    CategoriesForm *categories_form;
    AddCategoryForm *add_category_form;
    QWidget *parent;

public:
    explicit Categories(QSqlDatabase &db, QWidget *parent = 0);

    QSqlTableModel* get_model();

signals:

public slots:
    void open_add_category_form();
    void add_category(QString name);
    void open_categories();
    void remove_category(int);
};

#endif // CATEGORIES_H
