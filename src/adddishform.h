#ifndef ADDDISHFORM_H
#define ADDDISHFORM_H

#include <QtWidgets>
#include <QSqlTableModel>
#include "categories.h"

class AddDishForm : public QDialog
{
    Q_OBJECT

private:
    //QSqlTableModel *model;
    QSqlTableModel *categories_model;
    QString img_path;
    //QWidget *parent;

    /// GUI
    QVBoxLayout *main_layout;
    QGridLayout *info_layout;
    QHBoxLayout *buttons_layout;

    QLabel *l_picture;
    QPushButton *picture_select_btn;
    QLabel *picture;
    QPixmap *pixmap;
    QPushButton *rechoose_picture_btn;

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
    bool loading_image();

signals:
    void add_dish(QString name, double weight, double price, QString category, int estimated_time, QString url);

public slots:
    void select_image();
    void reselect_image();
    void add_dish();
};

#endif // ADDDISHFORM_H
