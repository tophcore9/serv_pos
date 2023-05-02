#ifndef CLIENTS_H
#define CLIENTS_H

#include <QWidget>
#include <QSqlTableModel>
#include "addclientform.h"

class Clients : public QWidget
{
    Q_OBJECT
private:
    QSqlTableModel *model;
    QSqlTableModel *dishes_model;
    AddClientForm *adc;
    QWidget *parent;

public:
    explicit Clients(QSqlDatabase &db, QSqlTableModel *dishes_model, QWidget *parent = 0);
    ~Clients();

    QSqlTableModel* get_model();

signals:

public slots:
    void add_client();
};

#endif // CLIENTS_H
