#ifndef ADDMENUFORM_H
#define ADDMENUFORM_H

#include <QtWidgets>
#include <QSqlTableModel>
#include <QDebug>
#include <functional>

class AddMenuForm : public QDialog
{
    Q_OBJECT

private:
    QSqlTableModel *dishes_model;
    std::vector<QString> dishes;
    int dish_grid_index;
    int current_dish_item;

    // GUI
    QVBoxLayout *main_layout;
    QGridLayout *info_layout;
    QHBoxLayout *buttons_layout;

    QLabel *l_name;
    QLineEdit *name_edit;

    QLabel *l_dishes;
    QPushButton *add_dish_btn;
    std::vector<QComboBox*> add_dish_selects;
    std::vector<QPushButton*> remove_dish_btns;

    QPushButton *accept_btn;
    QPushButton *cancel_btn;

public:
    explicit AddMenuForm(QSqlTableModel *menu_model, QSqlTableModel *dishes_model, QWidget *parent = 0);

signals:
    void add_menu(QString name, std::vector<QString> dishes);

public slots:
    void add_dish();
    void add_menu();

    void remove_dish(int index);
};

#endif // ADDMENUFORM_H
