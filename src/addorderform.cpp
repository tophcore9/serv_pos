#include "addorderform.h"

AddOrderForm::AddOrderForm(QWidget *parent) : QWidget(parent)
{
    this->parent = parent;
    this->dishes_model = dishes_model;
    this->setWindowTitle("Додати клієнта");
    this->setFixedSize(350, 500);

}
