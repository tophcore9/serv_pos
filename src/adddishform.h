#ifndef ADDDISHFORM_H
#define ADDDISHFORM_H

#include <QtWidgets>
#include <QSqlTableModel>
#include "categories.h"

class AddDishForm : public QDialog
{
    Q_OBJECT

private:
    QSqlTableModel *model;
    QSqlTableModel *categories_model;
    QWidget *parent;

    // GUI
    QVBoxLayout *main_layout;
    QGridLayout *info_layout;
    QHBoxLayout *buttons_layout;

    QPushButton *accept_btn;
    QPushButton *cancel_btn;

public:
    explicit AddDishForm(QSqlTableModel *categories_model, QWidget *parent = 0);

signals:

public slots:
};

#endif // ADDDISHFORM_H
