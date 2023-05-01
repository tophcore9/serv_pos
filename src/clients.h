#ifndef CLIENTS_H
#define CLIENTS_H

#include <QObject>
#include <QSqlTableModel>

class Clients : public QObject
{
    Q_OBJECT
private:
    QSqlTableModel *model;

public:
    explicit Clients(QSqlDatabase &db, QObject *parent = 0);
    QSqlTableModel* get_model();

signals:

public slots:
};

#endif // CLIENTS_H
