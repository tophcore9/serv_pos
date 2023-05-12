#ifndef SHOWMENUFORM_H
#define SHOWMENUFORM_H

#include <QDialog>
#include <QtWidgets>

#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>

class ShowMenuForm : public QDialog
{
    Q_OBJECT

private:
    QString menu_id;
    std::vector<QString> dishes;
    QString past_menu_name;
    QString new_menu_name;

    /// GUI
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
    explicit ShowMenuForm(QModelIndex menu_index, QSqlTableModel *dishes_model, QWidget *parent = 0);

signals:
    void edit_menu(QString default_name, QString name, std::vector<QString> dishes);

public slots:
    void edit_menu();
};

#endif // SHOWMENUFORM_H
