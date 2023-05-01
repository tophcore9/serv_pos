#ifndef ORDERS_H
#define ORDERS_H

#include <QObject>
#include <QSqlTableModel>

class Orders : public QObject
{
    Q_OBJECT
private:
    QSqlTableModel *model;
    QSqlDatabase db;

public:
    explicit Orders(QSqlDatabase &db, QObject *parent = 0);
    ~Orders();

    QSqlTableModel* get_model();

signals:

public slots:
};

#endif // ORDERS_H
