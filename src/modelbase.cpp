#include "modelbase.h"

ModelBase::ModelBase(QSqlDatabase &db, QWidget *parent) : QWidget(parent)
{
    this->model = model;
    this->parent = parent;
    model = new QSqlTableModel(parent, db);
}

QSqlTableModel *ModelBase::get_model()
{
    return model;
}

void ModelBase::change_index(const QModelIndex index)
{
    this->index = index;
}

void ModelBase::change_sort(int sort_index)
{
    switch (sort_index) {
    case 0:
        model->setSort(0, Qt::AscendingOrder);
        break;
    case 1:
        model->setSort(1, Qt::AscendingOrder);
        break;
    case 2:
        model->setSort(2, Qt::AscendingOrder);
        break;
    case 3:
        model->setSort(3, Qt::AscendingOrder);
        break;
    case 4:
        model->setSort(4, Qt::AscendingOrder);
        break;
    case 5:
        model->setSort(5, Qt::AscendingOrder);
        break;
    }
    model->select();
}

void ModelBase::remove(int index)
{
    if (model->rowCount() > index)
    {
        model->removeRow(index);
        model->select();
    }
    else
    {
        QMessageBox::critical(this, tr("Помилка!"), tr("Не вдалось виконати запит!\n") +
                              tr("Будь ласка, оберіть елемент перед тим, як видалити його."));
    }
}
