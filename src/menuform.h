#ifndef MENUFORM_H
#define MENUFORM_H

#include <QtWidgets>
#include <QDebug>
#include <QSqlTableModel>

class MenuForm : public QDialog
{
    Q_OBJECT

private:
    int current_menu;

    QVBoxLayout *main_layout;
    QVBoxLayout *view_layout;
    QHBoxLayout *buttons_layout;

    QComboBox *menu_sort;
    QListView *list_view;
    QPushButton *add_menu_btn;
    QPushButton *delete_menu_btn;
    QPushButton *exit_btn;

public:
    explicit MenuForm(QSqlTableModel *menu_model, QWidget *parent = 0);

signals:
    void send_index(const QModelIndex);
    void remove_menu_row(int);
    void reset_form();

public slots:
    void change_menu_row(const QModelIndex index);
    void remove_menu_row();
    void close_form();
};

#endif // MENUFORM_H
