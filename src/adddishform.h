#ifndef ADDDISHFORM_H
#define ADDDISHFORM_H

#include <QtWidgets>
#include <QSqlTableModel>

class AddDishForm : public QWidget
{
    Q_OBJECT

private:
    QSqlTableModel *model;
    QSqlTableModel *dishes_model;
    QWidget *parent;

public:
    explicit AddDishForm(QWidget *parent = 0);

signals:

public slots:
};

#endif // ADDDISHFORM_H
