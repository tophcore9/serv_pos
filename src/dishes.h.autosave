#ifndef DISHES_H
#define DISHES_H

#include <QWidget>
#include <QDebug>
#include <QSqlTableModel>

class Dishes : public QWidget
{
    Q_OBJECT
private:
    QSqlTableModel *model;
    QWidget *parent;
    QSqlDatabase db;

public:
    explicit Dishes(QSqlDatabase &db, QWidget *parent = 0);
    ~Dishes();

    QSqlTableModel* get_model();

signals:

public slots:
    void add_dish();
};

#endif // DISHES_H
