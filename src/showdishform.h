#ifndef SHOWDISHFORM_H
#define SHOWDISHFORM_H

#include <QDialog>
#include <QtWidgets>
#include <QDebug>

#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>

class ShowDishForm : public QDialog
{
    Q_OBJECT

private:
    /// GUI
    QVBoxLayout *main_layout;
    QGridLayout *info_layout;
    QHBoxLayout *buttons_layout;

    QLabel *l_picture;
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
    explicit ShowDishForm(QModelIndex dish_index, QSqlTableModel *categories_model, QWidget *parent = 0);

signals:
    void edit_dish(QString name, int weight, double price, QString category, int estimated_time, QString url);

public slots:
    void edit_dish();
};

#endif // SHOWDISHFORM_H
