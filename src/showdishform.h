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

    QPushButton *accept_btn;
    QPushButton *cancel_btn;

public:
    explicit ShowDishForm(QModelIndex dish_index, QSqlDatabase db, QWidget *parent = 0);

signals:
    void edit_dish(QString name, int weight, double price, QString category, int estimated_time, QString url);

public slots:
    void edit_dish();
};

#endif // SHOWDISHFORM_H
