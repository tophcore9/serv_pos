#ifndef SHOWCATEGORYFORM_H
#define SHOWCATEGORYFORM_H

#include <QDialog>
#include <QtWidgets>

#include <QSqlTableModel>

class ShowCategoryForm : public QDialog
{
    Q_OBJECT

private:
    QString category_name;
    QString new_category_name;

    /// GUI
    QVBoxLayout *main_layout;
    QGridLayout *info_layout;
    QHBoxLayout *buttons_layout;

    QLabel *l_name;
    QLineEdit *name_edit;

    QPushButton *accept_btn;
    QPushButton *cancel_btn;

public:
    explicit ShowCategoryForm(QModelIndex category_index, QWidget *parent = 0);

signals:
    void edit_category(QString default_name, QString name);

public slots:
    void edit_category();
    void name_changed(QString new_name);
};

#endif // SHOWCATEGORYFORM_H
