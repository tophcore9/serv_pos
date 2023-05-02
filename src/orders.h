#ifndef ORDERS_H
#define ORDERS_H

#include <QWidget>
#include <QDebug>
#include <QSqlTableModel>

class Orders : public QWidget
{
    Q_OBJECT
private:
    QSqlTableModel *model;
    QWidget *parent;
    QSqlDatabase db;

public:
    explicit Orders(QSqlDatabase &db, QWidget *parent = 0);
    ~Orders();

    QSqlTableModel* get_model();

signals:

public slots:
    void add_order();
};

#endif // ORDERS_H
