#ifndef MENUITEMS_H
#define MENUITEMS_H

#include <QtWidgets>
#include <QSqlTableModel>
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
};

#endif // MENUITEMS_H
