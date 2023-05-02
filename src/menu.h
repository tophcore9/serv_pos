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

public:
    explicit Menu(QWidget *parent = 0);

signals:

public slots:
    void add_menu();
};

#endif // MENU_H
