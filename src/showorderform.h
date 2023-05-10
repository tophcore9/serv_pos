#ifndef SHOWORDERFORM_H
#define SHOWORDERFORM_H

#include <QDialog>
#include <QtWidgets>

#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>

class ShowOrderForm : public QDialog
{
    Q_OBJECT

private:
    std::vector<QString> dishes;

    /// GUI
    QVBoxLayout *main_layout;
    QGridLayout *info_layout;
    QHBoxLayout *buttons_layout;

    QLabel *l_name;
    QLineEdit *name_edit;

    QLabel *l_client;
    QComboBox *client_select;

    QLabel *l_price;
    QLineEdit *price_edit;
    QLabel *price_l;

    QLabel *l_estimated_time;
    QLineEdit *estimated_time_edit;
    QLabel *estimated_time_l;

    QLabel *l_date;
    QLineEdit *date_edit;

    QLabel *l_dishes;
    QPushButton *add_dish_btn;
    std::vector<QComboBox*> add_dish_selects;
    std::vector<QPushButton*> remove_dish_btns;
    std::vector<QLineEdit*> count_dish_edits;

    QPushButton *accept_btn;
    QPushButton *cancel_btn;

public:
    explicit ShowOrderForm(QModelIndex order_index, QSqlTableModel *clients_model, QWidget *parent = 0);

signals:
    void edit_order(QString name, QString client, double total_price, int total_time, QString date, std::vector<QString> dishes);

public slots:
    void edit_order();
};

#endif // SHOWORDERFORM_H
