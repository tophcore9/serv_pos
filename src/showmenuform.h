#ifndef SHOWMENUFORM_H
#define SHOWMENUFORM_H

#include <QDialog>
#include <QtWidgets>

#include <QSqlTableModel>

class ShowMenuForm : public QDialog
{
    Q_OBJECT

private:
    /// GUI
    QVBoxLayout *main_layout;
    QGridLayout *info_layout;
    QHBoxLayout *buttons_layout;

public:
    explicit ShowMenuForm(QModelIndex menu_index, QWidget *parent = 0);

signals:

public slots:
};

#endif // SHOWMENUFORM_H
