#ifndef CLIENTS_H
#define CLIENTS_H

#include <QWidget>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>

#include "addclientform.h"
#include "showclientform.h"

class Clients : public QWidget
{
    Q_OBJECT
private:
    QSqlTableModel *model;
    QSqlTableModel *dishes_model;

    AddClientForm *add_client_form;
    ShowClientForm *show_client_form;

    QWidget *parent;

public:
    explicit Clients(QSqlDatabase &db, QSqlTableModel *dishes_model, QWidget *parent = 0);

    QSqlTableModel* get_model();

signals:

public slots:
    void open_show_client_form();
    void remove_client(int);
    void open_add_client_form();
    void add_client(QString name, QString phone, QString date, QString favourite);
};

#endif // CLIENTS_H
