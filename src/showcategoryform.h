#ifndef SHOWCATEGORYFORM_H
#define SHOWCATEGORYFORM_H

#include <QDialog>
#include <QtWidgets>

#include <QSqlTableModel>

class ShowCategoryForm : public QDialog
{
    Q_OBJECT

private:
    /// GUI
    QVBoxLayout *main_layout;
    QGridLayout *info_layout;
    QHBoxLayout *buttons_layout;

public:
    explicit ShowCategoryForm(QModelIndex category_index, QWidget *parent = 0);

signals:

public slots:
};

#endif // SHOWCATEGORYFORM_H
