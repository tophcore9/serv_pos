#ifndef ADDORDERFORM_H
#define ADDORDERFORM_H

#include <QtWidgets>
#include <QSqlTableModel>

class AddOrderForm : public QWidget
{
    Q_OBJECT

private:
    QSqlTableModel *model;
    QSqlTableModel *dishes_model;
    QWidget *parent;

public:
    explicit AddOrderForm(QWidget *parent = 0);

signals:

public slots:
};

#endif // ADDORDERFORM_H
