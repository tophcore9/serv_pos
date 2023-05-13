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
