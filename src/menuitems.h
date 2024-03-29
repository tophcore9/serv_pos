#ifndef MENUITEMS_H
#define MENUITEMS_H

#include "modelbase.h" // BASE-CLASS

class MenuItems : public ModelBase
{
    Q_OBJECT

public:
    explicit MenuItems(QSqlDatabase &db, QWidget *parent = 0);

public slots:
    void add_menu_item(QString menu_name, QString dish_name);
    void remove_menu_items(int menu_id);
};

#endif // MENUITEMS_H
