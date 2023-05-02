#ifndef MENU_H
#define MENU_H

#include <QtWidgets>
#include <QDebug>
#include <QSqlTableModel>

class Menu : public QWidget
{
    Q_OBJECT

private:
    QSqlTableModel *model;
    QWidget *parent;
    QSqlDatabase db;

public:
    explicit Menu(QSqlDatabase &db, QWidget *parent = 0);

    QSqlTableModel* get_model();

signals:

public slots:
    void add_menu();
};

#endif // MENU_H
