#ifndef MODELBASE_H
#define MODELBASE_H

#include <QtWidgets>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>

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

signals:

public slots:
    void change_index(const QModelIndex index);
    void change_sort(int sort_index);
    virtual void remove(int index);
};

#endif // MODELBASE_H
