#ifndef SHOWCLIENTFORM_H
#define SHOWCLIENTFORM_H

#include <QDialog>
#include <QtWidgets>

#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>

#include "modelbase.h"

class ShowClientForm : public QDialog
{
    Q_OBJECT

private:
    QString past_client_phone;
    QString new_client_name;
    QString new_client_phone;
    QString new_client_dish;
    QString new_client_date;

    /// GUI
    QVBoxLayout *main_layout;
    QGridLayout *info_layout;
    QHBoxLayout *buttons_layout;

    QLabel *l_name;
    QLineEdit *name_edit;

    QLabel *l_phone;
    QLineEdit *phone_edit;

    QLabel *l_favourite_dish;
    QComboBox *favourite_dish_select;

    QLabel *l_registration_date;
    QLineEdit *registration_date_edit;

    QPushButton *accept_btn;
    QPushButton *cancel_btn;

public:
    explicit ShowClientForm(QModelIndex client_index, QSqlTableModel *dishes_model, QWidget *parent = 0);

signals:
    void edit_client(QString default_phone, QString name, QString phone, QString date, QString favourite);

public slots:
    void edit_client();

    void name_changed(QString);
    void phone_changed(QString);
    void date_changed(QString);
    void dish_changed(QString);
};

#endif // SHOWCLIENTFORM_H
