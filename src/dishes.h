#ifndef DISHES_H
#define DISHES_H

#include <QObject>
#include <QSqlTableModel>

class Dishes : public QObject
{
    Q_OBJECT
private:
    QSqlTableModel *model;

public:
    explicit Dishes(QSqlDatabase &db, QObject *parent = 0);
    QSqlTableModel* get_model();

signals:

public slots:
};

#endif // DISHES_H
