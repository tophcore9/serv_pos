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

    QPushButton *accept_btn;
    QPushButton *cancel_btn;

public:
    explicit ShowMenuForm(QModelIndex menu_index, QSqlDatabase db, QWidget *parent = 0);

signals:
    void edit_menu(QString name, std::vector<QString> dishes);

public slots:
    void edit_menu();
};

#endif // SHOWMENUFORM_H
