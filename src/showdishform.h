#ifndef SHOWDISHFORM_H
#define SHOWDISHFORM_H

#include <QDialog>
#include <QtWidgets>
#include <QDebug>

#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>

class ShowDishForm : public QDialog
{
    Q_OBJECT

private:
    /// GUI
    QVBoxLayout *main_layout;
    QGridLayout *info_layout;
    QHBoxLayout *buttons_layout;

    QLabel *lb;

public:
    explicit ShowDishForm(QModelIndex dish_index, QSqlTableModel *categories_model, QWidget *parent = 0);

signals:

public slots:
};

#endif // SHOWDISHFORM_H
