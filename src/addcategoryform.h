#ifndef ADDCATEGORYFORM_H
#define ADDCATEGORYFORM_H

#include <QtWidgets>
#include <QDialog>
#include <QSqlTableModel>
#include <QDebug>

class AddCategoryForm : public QDialog
{
    Q_OBJECT

private:
    // GUI
    QVBoxLayout *main_layout;
    QGridLayout *info_layout;
    QHBoxLayout *buttons_layout;

    QLabel *l_name;
    QLineEdit *name_edit;

    QPushButton *accept_btn;
    QPushButton *cancel_btn;

public:
    explicit AddCategoryForm(QSqlTableModel *categories_model, QWidget *parent = 0);

signals:
    void add_category(QString);

public slots:
    void add_category();
};

#endif // ADDCATEGORYFORM_H
