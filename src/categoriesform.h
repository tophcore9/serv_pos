#ifndef CATEGORIESFORM_H
#define CATEGORIESFORM_H

#include <QtWidgets>
#include <QSqlTableModel>
#include <QDebug>

class CategoriesForm : public QDialog
{
    Q_OBJECT

private:
    QVBoxLayout *main_layout;
    QHBoxLayout *view_layout;
    QHBoxLayout *buttons_layout;

    QListView *list_view;
    QPushButton *add_category_btn;
    QPushButton *delete_category_btn;
    QPushButton *exit_btn;

public:
    explicit CategoriesForm(QSqlTableModel *categories_model, QWidget *parent = 0);

signals:

public slots:
};

#endif // CATEGORIESFORM_H
