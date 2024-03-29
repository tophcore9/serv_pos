#ifndef MENU_H
#define MENU_H

#include <QtWidgets>
#include <QDebug>
#include <QSqlTableModel>

#include "menuform.h"
#include "addmenuform.h"
#include "menuitems.h"
#include "showmenuform.h"
#include "modelbase.h"

class Menu : public ModelBase
{
    Q_OBJECT

private:
    QSqlTableModel *dishes_model;

    MenuItems *menu_items;
    MenuForm *menu_form;
    AddMenuForm *add_menu_form;
    ShowMenuForm *show_menu_form;

public:
    explicit Menu(QSqlDatabase &db, QSqlTableModel *dishes_model, QWidget *parent = 0);

signals:

public slots:
    void open_show_menu_form();
    void open_add_menu_form();
    void open_menu();
    void add_menu(QString name, std::vector<QString> dishes);
    void edit_menu(QString default_name, QString name, std::vector<QString> dishes);
    void reset_menu_form();

    void remove(int index) override
    {
        QVariant menu_id = model->data(model->index(index, 0));
        menu_items->remove_menu_items(menu_id.toInt());

        ModelBase::remove(index);
    }
};

#endif // MENU_H
