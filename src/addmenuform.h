#ifndef ADDMENUFORM_H
#define ADDMENUFORM_H

#include <QtWidgets>
#include <QDialog>
#include <QSqlTableModel>
#include <QDebug>

class AddMenuForm : public QDialog
{
    Q_OBJECT

private:
    int dish_index;

    // GUI
    QVBoxLayout *main_layout;
    QGridLayout *info_layout;
    QHBoxLayout *buttons_layout;

    QLabel *l_name;
    QLineEdit *name_edit;

    QLabel *l_dishes;
    QPushButton *add_dish_btn;
    QComboBox *dishes_select;
    QPushButton *remove_dish_btn;

    QPushButton *accept_btn;
    QPushButton *cancel_btn;

public:
    explicit AddMenuForm(QSqlTableModel *menu_model, QSqlTableModel *dishes_model, QWidget *parent = 0);

signals:
    void add_menu(QString name);

public slots:
    void add_first_dish();
    void add_menu();
};

#endif // ADDMENUFORM_H
