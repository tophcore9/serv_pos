#ifndef CATEGORIES_H
#define CATEGORIES_H

#include <QtWidgets>
#include <QDebug>
#include <QSqlTableModel>

class Categories : public QWidget
{
    Q_OBJECT

private:
    QSqlTableModel *model;
    QWidget *parent;

public:
    explicit Categories(QWidget *parent = 0);



signals:

public slots:
    void add_category();
};

#endif // CATEGORIES_H
