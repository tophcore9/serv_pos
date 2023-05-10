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

    QPushButton *accept_btn;
    QPushButton *cancel_btn;

public:
    explicit ShowCategoryForm(QModelIndex category_index, QWidget *parent = 0);

signals:
    void edit_category(QString name);

public slots:
    void edit_category();
};

#endif // SHOWCATEGORYFORM_H
