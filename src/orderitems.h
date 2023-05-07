#ifndef ORDERITEMS_H
#define ORDERITEMS_H

#include <QtWidgets>
#include <QSqlTableModel>
#include <QDebug>

class OrderItems : public QWidget
{
    Q_OBJECT

private:
    QSqlTableModel *model;
    QSqlDatabase db;

public:
    explicit OrderItems(QSqlDatabase &db, QWidget *parent = 0);

    QSqlTableModel* get_model();

signals:

public slots:
};

#endif // ORDERITEMS_H
