#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clients.h"
#include <QtWidgets>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QSqlDatabase db;
    Clients *clients;

    //GUI
    QListView *client_list;
    QListView *order_list;
    QListView *dishes_list;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
