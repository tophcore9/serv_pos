///BUGLIST
// 1 Помилка на Windows при додаванні замовлень
// 2 Не видаляються зображення при видаленні страви та при виході через хрестик
// 3 Не можна обирати зображення з корневої директорії

// Є можливість додати scroll до переліку страв в AddOrder та AddMenu
// Можна додати можливість обрати предмет показу в деяких таблицях
// Змінити структуру проекту, використати успадкування та статичні класи
// Додати клас обробки помилок
// Додати клас налаштувань та перемістити туди вибір мови
// Додати знижку для найактивнішого клієнта 5%
// Menu, баг при одночасній зміні ім'я та страв

#ifndef ADDCATEGORYFORM_H
#define ADDCATEGORYFORM_H

#include <QtWidgets>
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
