#ifndef CATEGORIES_H
#define CATEGORIES_H

#include <QtWidgets>
#include <QDebug>

#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>

#include "categoriesform.h"
#include "addcategoryform.h"
#include "showcategoryform.h"

class Categories : public QWidget
{
    Q_OBJECT

private:
    QSqlTableModel *model;

    QModelIndex index;

    CategoriesForm *categories_form;
    AddCategoryForm *add_category_form;
    ShowCategoryForm *show_category_form;

    QWidget *parent;

public:
    explicit Categories(QSqlDatabase &db, QWidget *parent = 0);

    QSqlTableModel* get_model();

signals:

public slots:
    void open_show_category_form();
    void open_add_category_form();
    void add_category(QString name);
    void edit_category(QString name);
    void open_categories();
    void remove_category(int);
    void change_index(const QModelIndex index);
};

#endif // CATEGORIES_H
