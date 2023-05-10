#ifndef SHOWORDERFORM_H
#define SHOWORDERFORM_H

#include <QDialog>
#include <QtWidgets>

#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>

class ShowOrderForm : public QDialog
{
    Q_OBJECT

private:
    /// GUI
    QVBoxLayout *main_layout;
    QGridLayout *info_layout;
    QHBoxLayout *buttons_layout;

    std::vector<QString> dishes;

public:
    explicit ShowOrderForm(QModelIndex order_index, QSqlDatabase db, QWidget *parent = 0);

signals:

public slots:
};

#endif // SHOWORDERFORM_H
