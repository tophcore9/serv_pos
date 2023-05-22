#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QEvent>

#include <QSqlError>
#include <QSqlQuery>

#include "orders.h"
#include "dishes.h"
#include "clients.h"
#include "categories.h"
#include "menu.h"
#include "statisticsform.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QTranslator *language;

    QSqlDatabase db;
    Clients *clients;
    Dishes *dishes;
    Orders *orders;
    Categories *categories;
    StatisticsForm *statistics_form;
    Menu *menu;

    int current_client, current_dish, current_order;

    /// GUI
    QHBoxLayout *main_layout;
    QVBoxLayout *orders_layout;
    QVBoxLayout *dishes_layout;
    QVBoxLayout *clients_layout;
    QVBoxLayout *other_functions_layout;
    QWidget *central_widget;

    QListView *order_list_view;
    QLabel *l_order;
    QComboBox *orders_sort;
    QPushButton *add_order_btn;
    QPushButton *delete_order_btn;

    QListView *dishes_list_view;
    QLabel *l_dishes;
    QComboBox *dishes_sort;
    QPushButton *add_dish_btn;
    QPushButton *delete_dish_btn;

    QLabel *l_clients;
    QComboBox *clients_sort;
    QListView *client_list_view;
    QPushButton *add_client_btn;
    QPushButton *delete_client_btn;

    QLabel *l_other;
    QPushButton *open_categories_btn;
    QPushButton *open_menu_btn;
    QPushButton *open_statistics_btn;
    QLabel *l_lang_change;
    QComboBox *lang_change;

    void change_main_window_lang();

public:
    MainWindow(QWidget *parent = 0);

signals:
    void send_client_index(const QModelIndex);
    void send_dish_index(const QModelIndex);
    void send_order_index(const QModelIndex);

public slots:
    void remove_client_row();
    void remove_dish_row();
    void remove_order_row();

    void change_client_row(const QModelIndex index);
    void change_dish_row(const QModelIndex index);
    void change_order_row(const QModelIndex index);

    void open_statistics();

    void change_lang();
};

#endif // MAINWINDOW_H
