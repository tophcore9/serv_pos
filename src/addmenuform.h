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
    // GUI
    QVBoxLayout *main_layout;
    QGridLayout *info_layout;
    QHBoxLayout *buttons_layout;

    QLabel *l_name;
    QLineEdit *name_edit;

    QPushButton *accept_btn;
    QPushButton *cancel_btn;

public:
    explicit AddMenuForm(QSqlTableModel *menu_model, QWidget *parent = 0);

signals:
    void add_menu(QString name);

public slots:
    void add_menu();
};

#endif // ADDMENUFORM_H
