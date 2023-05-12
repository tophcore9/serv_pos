#ifndef CATEGORIESFORM_H
#define CATEGORIESFORM_H

#include <QtWidgets>
#include <QSqlTableModel>
#include <QDebug>

class CategoriesForm : public QDialog
{
    Q_OBJECT

private:
    int current_category;

    QVBoxLayout *main_layout;
    QVBoxLayout *view_layout;
    QHBoxLayout *buttons_layout;

    QComboBox *categories_sort;
    QListView *list_view;
    QPushButton *add_category_btn;
    QPushButton *delete_category_btn;
    QPushButton *exit_btn;

public:
    explicit CategoriesForm(QSqlTableModel *categories_model, QWidget *parent = 0);

signals:
    void remove_category_row(int);
    void send_index(const QModelIndex);
    void reset_form();

public slots:
    void change_category_row(const QModelIndex index);
    void remove_category_row();
    void close_form();
};

#endif // CATEGORIESFORM_H
