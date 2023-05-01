#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "orders.h"
#include "dishes.h"
#include "clients.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QSqlDatabase db;
    Clients *clients;
    Dishes *dishes;
    Orders *orders;

    //GUI
    QLabel *l_order;
    QListView *order_list_view;
    QPushButton *add_order_btn;
    QPushButton *delete_order_btn;
    QPushButton *edit_order_btn;

    QListView *dishes_list_view;
    QLabel *l_dishes;
    QPushButton *add_dish_btn;
    QPushButton *delete_dish_btn;
    QPushButton *edit_dish_btn;

    QListView *client_list_view;
    QLabel *l_clients;
    QPushButton *add_client_btn;
    QPushButton *delete_client_btn;
    QPushButton *edit_client_btn;

    QLabel *l_other;
    QPushButton *open_categories_btn;
    QPushButton *open_menus_btn;
    QPushButton *open_statistics_btn;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
