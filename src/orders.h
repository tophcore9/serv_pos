#ifndef ORDERS_H
#define ORDERS_H

#include <QObject>
#include <QSqlTableModel>

class Orders : public QObject
{
    Q_OBJECT
private:
    QSqlTableModel *model;

public:
    explicit Orders(QSqlDatabase &db, QObject *parent = 0);
    QSqlTableModel* get_model();

signals:

public slots:
};

#endif // ORDERS_H
