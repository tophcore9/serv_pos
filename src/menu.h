#ifndef MENU_H
#define MENU_H

#include <QtWidgets>
#include <QDebug>
#include <QSqlTableModel>

#include "menuform.h"
#include "addmenuform.h"
#include "menuitems.h"
#include "showmenuform.h"

class Menu : public QWidget
{
    Q_OBJECT

private:
    QSqlTableModel *model;
    QSqlTableModel *dishes_model;
    QModelIndex index;

    MenuItems *menu_items;
    MenuForm *menu_form;
    AddMenuForm *add_menu_form;
    ShowMenuForm *show_menu_form;

    QWidget *parent;

public:
    explicit Menu(QSqlDatabase &db, QSqlTableModel *dishes_model, QWidget *parent = 0);

    QSqlTableModel* get_model();

signals:

public slots:
    void change_index(const QModelIndex index);
    void open_show_menu_form();
    void open_add_menu_form();
    void open_menu();
    void remove_menu(int);
    void add_menu(QString name, std::vector<QString> dishes);
    void edit_menu(QString name, std::vector<QString> dishes);
};

#endif // MENU_H
