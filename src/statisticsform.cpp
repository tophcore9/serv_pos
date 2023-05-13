#include "statisticsform.h"

StatisticsForm::StatisticsForm(QSqlDatabase &db, QWidget *parent) : QDialog(parent)
{
    qDebug() << db.databaseName();
}
