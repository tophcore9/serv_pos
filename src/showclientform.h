#ifndef SHOWCLIENTFORM_H
#define SHOWCLIENTFORM_H

#include <QDialog>
#include <QtWidgets>

#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>

class ShowClientForm : public QDialog
{
    Q_OBJECT

private:
    /// GUI
    QVBoxLayout *main_layout;
    QGridLayout *info_layout;
    QHBoxLayout *buttons_layout;

public:
    explicit ShowClientForm(QModelIndex client_index, QSqlDatabase db, QWidget *parent = 0);

signals:

public slots:
};

#endif // SHOWCLIENTFORM_H
