#ifndef MENUITEMS_H
#define MENUITEMS_H

#include <QtWidgets>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QDebug>

class MenuItems : public QWidget
{
    Q_OBJECT

private:
    QSqlTableModel *model;
    QSqlDatabase db;

public:
    explicit MenuItems(QSqlDatabase &db, QWidget *parent = 0);

    QSqlTableModel* get_model();

signals:

public slots:
    void add_menu_item(QString menu_name, QString dish_name);
};

#endif // MENUITEMS_H
