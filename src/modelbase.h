#ifndef MODELBASE_H
#define MODELBASE_H

#include <QtWidgets>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlError>

class ModelBase : public QWidget
{
    Q_OBJECT
private:

public:
    explicit ModelBase(QSqlDatabase &db, QWidget *parent = 0);

    QSqlTableModel *model;
    QWidget *parent;
    QModelIndex index;

    QSqlTableModel* get_model();
    void secure_query(QString query_str, QWidget *parent = 0);
    static void secure_query_exception(QSqlQuery query, QWidget *parent = 0);

signals:

public slots:
    void change_index(const QModelIndex index);
    void change_sort(int sort_index);
    virtual void remove(int index);
};

#endif // MODELBASE_H
