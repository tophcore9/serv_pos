#ifndef ORDERITEMS_H
#define ORDERITEMS_H

#include "modelbase.h" // BASE-CLASS

class OrderItems : public ModelBase
{
    Q_OBJECT

public:
    explicit OrderItems(QSqlDatabase &db, QWidget *parent = 0);

public slots:
    void add_order_item(QString order_name, QString dish_name);
    void remove_order_items(int order_id);
};

#endif // ORDERITEMS_H
