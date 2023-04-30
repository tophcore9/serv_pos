#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // БАЗОВІ НАЛАШТУВАННЯ
    this->setWindowTitle("ServPOS");
    this->setFixedSize(1000, 600);


    // ДОДАВАННЯ ВІДЖЕТІВ
    client_list = new QListView;
    order_list = new QListView;
    dishes_list = new QListView;



    // ПІДКЛЮЧЕННЯ К БД
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../database/main.db");

    if (db.open())
    {
        // ГОЛОВНА ЧАСТИНА ПРОГРАМИ
        clients = new Clients(db, this);

        client_list->setModel(clients->get_model());
    }
    else
    {
        // ОБРОБКА ПОМИЛОК
    }

}

MainWindow::~MainWindow()
{

}
