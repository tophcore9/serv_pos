#ifndef STATISTICSFORM_H
#define STATISTICSFORM_H

#include <QDialog>
#include <QtWidgets>
#include <QDebug>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class StatisticsForm : public QDialog
{
    Q_OBJECT

private:
    // GUI
    QVBoxLayout *main_layout;
    QLabel *created_orders;
    QLabel *created_dishes;
    QLabel *created_clients;
    QLabel *created_menu;
    QLabel *created_categories;

    QLabel *average_price_dish;
    QLabel *average_weight_dish;
    QLabel *average_cooking_time_dish;

    QLabel *average_price_order;
    QLabel *average_cooking_time_order;

    QLabel *mvp_dish;
    QLabel *mvp_client;

    QPushButton *exit_btn;

public:
    explicit StatisticsForm(QSqlDatabase &db, QWidget *parent = 0);
    // Створених замовлень, клієнтів, страв, меню та категорій за весь час та на поточний момент
    // Середня вартість, вага, час приготування страв
    // Середня вартість замовлень
    // Найчастіша страва, найактивніший клієнт

signals:

public slots:
};

#endif // STATISTICSFORM_H
