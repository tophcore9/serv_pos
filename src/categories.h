#ifndef CATEGORIES_H
#define CATEGORIES_H

#include "modelbase.h" // BASE-CLASS

#include "categoriesform.h"
#include "addcategoryform.h"
#include "showcategoryform.h"

class Categories : public ModelBase
{
    Q_OBJECT

private:
    CategoriesForm *categories_form;
    AddCategoryForm *add_category_form;
    ShowCategoryForm *show_category_form;

public:
    explicit Categories(QSqlDatabase &db, QWidget *parent = 0);

signals:

public slots:
    void open_show_category_form();
    void open_add_category_form();
    void add_category(QString name);
    void edit_category(QString default_name, QString name);
    void open_categories();
    void reset_categories_form();
};

#endif // CATEGORIES_H
