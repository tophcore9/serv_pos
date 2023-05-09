#ifndef SHOWORDERFORM_H
#define SHOWORDERFORM_H

#include <QDialog>
#include <QtWidgets>

#include <QSqlTableModel>

class ShowOrderForm : public QDialog
{
    Q_OBJECT

private:
    /// GUI
    QVBoxLayout *main_layout;
    QGridLayout *info_layout;
    QHBoxLayout *buttons_layout;

public:
    explicit ShowOrderForm(QModelIndex order_index, QModelIndex dish_index, QModelIndex client_index, QWidget *parent = 0);

signals:

public slots:
};

#endif // SHOWORDERFORM_H
