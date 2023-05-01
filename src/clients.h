#ifndef CLIENTS_H
#define CLIENTS_H

#include <QObject>
#include <QSqlTableModel>

class Clients : public QObject
{
    Q_OBJECT
private:
    QSqlTableModel *model;
    QSqlDatabase db;

public:
    explicit Clients(QSqlDatabase &db, QObject *parent = 0);
    ~Clients();

    QSqlTableModel* get_model();

signals:

public slots:
    void add_client();
};

#endif // CLIENTS_H
