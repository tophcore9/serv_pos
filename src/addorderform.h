#ifndef ADDORDERFORM_H
#define ADDORDERFORM_H

#include <functional>
#include <ctime>

#include "modelbase.h"
#include "clients.h"

class AddOrderForm : public QDialog
{
    Q_OBJECT

private:
    QSqlTableModel *clients_model;
    QSqlTableModel *dishes_model;
    int dish_grid_index;
    int current_dish_item;

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
    explicit AddOrderForm(QSqlTableModel *clients_model, QSqlTableModel *dishes_model, QWidget *parent = 0);
    QString generate_uniq_hash();

signals:
    void add_order(QString name, QString client, double total_price, int total_time, QString date, std::vector<QString> dishes);

public slots:
    void add_order();
    void add_dish();

    void remove_dish(int index);
    void refresh_values(QString);
};

#endif // ADDORDERFORM_H
