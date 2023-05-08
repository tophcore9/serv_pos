#ifndef ORDERITEMS_H
#define ORDERITEMS_H

#include <QtWidgets>
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

class OrderItems : public QWidget
{
    Q_OBJECT

private:
    QSqlTableModel *model;

public:
    explicit OrderItems(QSqlDatabase &db, QWidget *parent = 0);

    QSqlTableModel* get_model();

signals:

public slots:
    void add_order_item(QString order_name, QString dish_name);
    void remove_order_items(int order_id);
};

#endif // ORDERITEMS_H
