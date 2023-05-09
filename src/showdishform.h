#ifndef SHOWDISHFORM_H
#define SHOWDISHFORM_H

#include <QDialog>
#include <QtWidgets>

#include <QSqlTableModel>

class ShowDishForm : public QDialog
{
    Q_OBJECT

private:
    /// GUI
    QVBoxLayout *main_layout;
    QGridLayout *info_layout;
    QHBoxLayout *buttons_layout;

public:
    explicit ShowDishForm(QModelIndex dish_index, QModelIndex category_index, QWidget *parent = 0);

signals:

public slots:
};

#endif // SHOWDISHFORM_H
