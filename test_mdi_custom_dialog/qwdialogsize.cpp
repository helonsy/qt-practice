#include "qwdialogsize.h"
#include "ui_qwdialogsize.h"

#include <QMessageBox>

QWDialogSize::QWDialogSize(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWDialogSize)
{
    ui->setupUi(this);
    
    
}

QWDialogSize::~QWDialogSize()
{
    QMessageBox::information(this, "提示", "设置表格行数对话框被删除");
    delete ui;
}

int QWDialogSize::rowCount()
{//用于主窗口调用获得行数的输入值
    
    return ui->spinBoxRow->value();
}

int QWDialogSize::columnCount()
{
    return ui->spinBoxColumn->value();
}

void QWDialogSize::setRowColumn(int row, int column)
{
    ui->spinBoxRow->setValue(row);
    ui->spinBoxColumn->setValue(column);
}
