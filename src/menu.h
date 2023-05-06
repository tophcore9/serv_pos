#ifndef MENU_H
#define MENU_H

#include <QtWidgets>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlQuery>
#include "menuform.h"
#include "addmenuform.h"

class Menu : public QWidget
{
    Q_OBJECT

private:
    QSqlTableModel *model;
    QSqlTableModel *dishes_model;
    MenuForm *menu_form;
    AddMenuForm *add_menu_form;
    QWidget *parent;
    QSqlDatabase db;

public:
    explicit Menu(QSqlDatabase &db, QSqlTableModel *dishes_model, QWidget *parent = 0);

    QSqlTableModel* get_model();

signals:

public slots:
    void open_add_menu_form();
    void open_menu();
    void remove_menu(int);
    void add_menu(QString name);
};

#endif // MENU_H
