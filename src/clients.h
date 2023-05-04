#ifndef CLIENTS_H
#define CLIENTS_H

#include <QWidget>
#include <QDebug>
#include <QSqlTableModel>
#include "addclientform.h"

class Clients : public QWidget
{
    Q_OBJECT
private:
    QSqlTableModel *model;
    QSqlTableModel *dishes_model;
    AddClientForm *add_client_form;
    QWidget *parent;

public:
    explicit Clients(QSqlDatabase &db, QSqlTableModel *dishes_model, QWidget *parent = 0);

    QSqlTableModel* get_model();
    void add_client();

signals:

public slots:
    void remove_client(int);
};

#endif // CLIENTS_H
