#ifndef ADDCLIENTFORM_H
#define ADDCLIENTFORM_H

#include <QtWidgets>
#include <QSqlTableModel>

class AddClientForm : public QDialog
{
    Q_OBJECT
private:
    QSqlTableModel *model;

    // GUI
    QVBoxLayout *main_layout;
    QGridLayout *info_layout;
    QHBoxLayout *buttons_layout;

    QLabel *l_name;
    QLineEdit *name_edit;

    QLabel *l_phone;
    QLineEdit *phone_edit;

    QLabel *l_favourite_dish;
    QLineEdit *favourite_dish_edit;

    QLabel *l_registration_date;
    QLineEdit *registration_date_edit;

    QPushButton *accept_btn;
    QPushButton *cancel_btn;

public:
    explicit AddClientForm(QSqlTableModel *model, QDialog *parent = 0);
    ~AddClientForm();

signals:

public slots:
};

#endif // ADDCLIENTFORM_H