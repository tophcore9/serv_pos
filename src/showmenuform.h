#ifndef SHOWMENUFORM_H
#define SHOWMENUFORM_H

#include <QDialog>
#include <QtWidgets>

#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>

class ShowMenuForm : public QDialog
{
    Q_OBJECT

private:
    /// GUI
    QVBoxLayout *main_layout;
    QGridLayout *info_layout;
    QHBoxLayout *buttons_layout;

    std::vector<QString> dishes;

public:
    explicit ShowMenuForm(QModelIndex menu_index, QSqlDatabase db, QWidget *parent = 0);

signals:

public slots:
};

#endif // SHOWMENUFORM_H
