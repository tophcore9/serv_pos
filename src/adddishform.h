#ifndef ADDDISHFORM_H
#define ADDDISHFORM_H

#include <QtWidgets>
#include <QSqlTableModel>
#include "categories.h"

class AddDishForm : public QDialog
{
    Q_OBJECT

private:
    QSqlTableModel *model;
    QSqlTableModel *categories_model;
    QWidget *parent;

    // GUI
    QVBoxLayout *main_layout;
    QGridLayout *info_layout;
    QHBoxLayout *buttons_layout;

    QLabel *l_name;
    QLineEdit *name_edit;

    QLabel *l_weight;
    QLineEdit *weight_edit;
    QLabel *weight_l;

    QLabel *l_price;
    QLineEdit *price_edit;
    QLabel *price_l;

    QLabel *l_categories;
    QComboBox *categories_select;

    QLabel *l_estimated_time;
    QLineEdit *estimated_time_edit;
    QLabel *estimated_time_l;


    QPushButton *accept_btn;
    QPushButton *cancel_btn;

public:
    explicit AddDishForm(QSqlTableModel *categories_model, QWidget *parent = 0);

signals:

public slots:
};

#endif // ADDDISHFORM_H
