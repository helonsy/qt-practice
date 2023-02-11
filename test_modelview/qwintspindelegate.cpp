#include <QSpinBox>
#include "qwintspindelegate.h"


QWIntSpinDelegate::QWIntSpinDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{
    
}

QWidget* QWIntSpinDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    
    QSpinBox *editor = new QSpinBox(parent);
    editor->setFrame(false);
    editor->setMinimum(0);
    editor->setMaximum(10000);
    
    return editor;
}

// 从数据模型获取数据，显示到代理组件中
void QWIntSpinDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int value = index.model()->data(index, Qt::EditRole).toInt();
    
    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    spinBox->setValue(value);
    
}

// 将代理组件的数据，保存到数据模型中
void QWIntSpinDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    spinBox->interpretText(); // 解释数据，如果数据被修改后，就触发信号
    
    int value = spinBox->value();
    model->setData(index, value, Qt::EditRole);
}

void QWIntSpinDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
