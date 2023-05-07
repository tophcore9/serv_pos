#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "orders.h"
#include "dishes.h"
#include "clients.h"
#include "categories.h"
#include "menu.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QSqlDatabase db;
    Clients *clients;
    Dishes *dishes;
    Orders *orders;
    Categories *categories;
    Menu *menu;

    int current_client, current_dish, current_order;

    /// GUI
    QHBoxLayout *main_layout;
    QVBoxLayout *orders_layout;
    QVBoxLayout *dishes_layout;
    QVBoxLayout *clients_layout;
    QVBoxLayout *other_functions_layout;
    QWidget *central_widget;

    QLabel *l_order;
    QListView *order_list_view;
    QPushButton *add_order_btn;
    QPushButton *delete_order_btn;

    QListView *dishes_list_view;
    QLabel *l_dishes;
    QPushButton *add_dish_btn;
    QPushButton *delete_dish_btn;

    QListView *client_list_view;
    QLabel *l_clients;
    QPushButton *add_client_btn;
    QPushButton *delete_client_btn;

    QLabel *l_other;
    QPushButton *open_categories_btn;
    QPushButton *open_menu_btn;
    QPushButton *open_statistics_btn;

public:
    MainWindow(QWidget *parent = 0);

signals:

public slots:
    void remove_client_row();
    void remove_dish_row();
    void remove_order_row();

    void change_client_row(const QModelIndex index);
    void change_dish_row(const QModelIndex index);
    void change_order_row(const QModelIndex index);
//    void get_db(QSqlDatabase &database);
//    void get_clients(Clients *clients_);
//    void get_orders(Orders *orders_);
};

#endif // MAINWINDOW_H
