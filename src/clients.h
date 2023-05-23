#ifndef CLIENTS_H
#define CLIENTS_H

#include <QWidget>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>

#include "addclientform.h"
#include "showclientform.h"
#include "modelbase.h"

class Clients : public ModelBase
{
    Q_OBJECT
private:
    QSqlTableModel *dishes_model;

    AddClientForm *add_client_form;
    ShowClientForm *show_client_form;

public:
    explicit Clients(QSqlDatabase &db, QSqlTableModel *dishes_model, QWidget *parent = 0);

signals:

public slots:
    void open_show_client_form();
    void open_add_client_form();
    void add_client(QString name, QString phone, QString date, QString favourite);
    void edit_client(QString default_phone, QString name, QString phone, QString date, QString favourite);
};

#endif // CLIENTS_H
