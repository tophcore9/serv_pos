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

    QPushButton *accept_btn;
    QPushButton *cancel_btn;

public:
    explicit ShowOrderForm(QModelIndex order_index, QSqlDatabase db, QWidget *parent = 0);

signals:
    void edit_order(QString name, QString client, double total_price, int total_time, QString date, std::vector<QString> dishes);

public slots:
    void edit_order();
};

#endif // SHOWORDERFORM_H
