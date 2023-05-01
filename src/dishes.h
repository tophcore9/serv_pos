#ifndef DISHES_H
#define DISHES_H

#include <QObject>
#include <QSqlTableModel>

class Dishes : public QObject
{
    Q_OBJECT
private:
    QSqlTableModel *model;
    QSqlDatabase db;

public:
    explicit Dishes(QSqlDatabase &db, QObject *parent = 0);
    ~Dishes();

    QSqlTableModel* get_model();

signals:

public slots:
};

#endif // DISHES_H
