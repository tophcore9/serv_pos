#ifndef SHOWCLIENTFORM_H
#define SHOWCLIENTFORM_H

#include <QDialog>
#include <QtWidgets>

#include <QSqlTableModel>

class ShowClientForm : public QDialog
{
    Q_OBJECT

private:
    /// GUI
    QVBoxLayout *main_layout;
    QGridLayout *info_layout;
    QHBoxLayout *buttons_layout;

public:
    explicit ShowClientForm(QModelIndex client_index, QModelIndex dish_index, QWidget *parent = 0);

signals:

public slots:
};

#endif // SHOWCLIENTFORM_H
