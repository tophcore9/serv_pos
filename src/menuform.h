#ifndef MENUFORM_H
#define MENUFORM_H

#include <QtWidgets>
#include <QDebug>
#include <QSqlTableModel>

class MenuForm : public QDialog
{
    Q_OBJECT

private:
    QVBoxLayout *main_layout;
    QHBoxLayout *view_layout;
    QHBoxLayout *buttons_layout;

    QListView *list_view;
    QPushButton *add_menu_btn;
    QPushButton *delete_menu_btn;
    QPushButton *exit_btn;

public:
    explicit MenuForm(QSqlTableModel *menu_model, QWidget *parent = 0);

signals:

public slots:
};

#endif // MENUFORM_H