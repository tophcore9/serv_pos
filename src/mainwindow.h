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
    QListView *client_list_view;
    QListView *order_list_view;
    QListView *dishes_list_view;

    QPushButton *add_client_btn;
    QPushButton *delete_client_btn;
    QPushButton *edit_client_btn;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
