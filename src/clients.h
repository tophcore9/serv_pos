#ifndef CLIENTS_H
#define CLIENTS_H

#include <QWidget>
#include <QSqlTableModel>

class Clients : public QWidget
{
    Q_OBJECT
private:
    QSqlTableModel *model;
    QWidget *parent;

public:
    explicit Clients(QSqlDatabase &db, QWidget *parent = 0);
    ~Clients();

    QSqlTableModel* get_model();

signals:

public slots:
    void add_client();
};

#endif // CLIENTS_H
