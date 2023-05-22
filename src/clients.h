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
    QModelIndex index;

    AddClientForm *add_client_form;
    ShowClientForm *show_client_form;

    QWidget *parent;

public:
    explicit Clients(QSqlDatabase &db, QSqlTableModel *dishes_model, QWidget *parent = 0);

    QSqlTableModel* get_model();

signals:

public slots:
    void change_index(const QModelIndex index);
    void open_show_client_form();
    void remove_client(int);
    void open_add_client_form();
    void add_client(QString name, QString phone, QString date, QString favourite);
    void edit_client(QString default_phone, QString name, QString phone, QString date, QString favourite);
    void change_sort(int sort_index);
};

#endif // CLIENTS_H
