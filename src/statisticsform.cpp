#include "statisticsform.h"

StatisticsForm::StatisticsForm(QSqlDatabase &db, QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle(tr("Статистичні дані"));
    this->setFixedSize(300, 500);
}
