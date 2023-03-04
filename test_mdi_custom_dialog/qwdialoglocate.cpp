#include "mainwindow.h"
#include "qwdialoglocate.h"
#include "ui_qwdialoglocate.h"

#include <QMessageBox>

QWDialogLocate::QWDialogLocate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWDialogLocate)
{
    ui->setupUi(this);
    
    
}

QWDialogLocate::~QWDialogLocate()
{
    QMessageBox::information(this, "提示", "单元格定位对话框被删除");
    delete ui;
}


void QWDialogLocate::setSpinRange(int rowCount, int colCount)
{// 设置SpinBox输入最大值
    ui->spinBoxRow->setMaximum(rowCount - 1);
    ui->spinBoxColumn->setMaximum(colCount - 1);
}

void QWDialogLocate::setSpinValue(int rowNo, int colNo)
{// 设置SpinBox数值
    ui->spinBoxRow->setValue(rowNo);
    ui->spinBoxColumn->setValue(colNo);
}


void QWDialogLocate::closeEvent(QCloseEvent *event)
{// 窗口关闭事件，关闭时释放本窗口
    
    MainWindow *parWind = (MainWindow*)parentWidget();
    parWind->setActLocateEnable(true); // 使能actTab_Locate
    parWind->setDlgLocateNull();
}

void QWDialogLocate::showEvent(QShowEvent *event)
{
    MainWindow *parWind = (MainWindow*)this->parentWidget();
    parWind->setActLocateEnable(false);
}

void QWDialogLocate::on_btnSetText_clicked()
{// 定位到单元格，并设置字符串
    
    int row = ui->spinBoxRow->value();
    int col = ui->spinBoxColumn->value();
    
    MainWindow *parWind = (MainWindow*)parentWidget();
    parWind->setACellText(row, col, ui->edtCaption->text());
    if (ui->chkBoxRow->isChecked())
        ui->spinBoxRow->setValue(ui->spinBoxRow->value() + 1);
    if (ui->chkBoxColumn->isChecked())
        ui->spinBoxColumn->setValue(ui->spinBoxColumn->value() + 1);
}

