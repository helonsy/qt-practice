#include "dialog.h"
#include "ui_dialog.h"

#include <QColorDialog>
#include <QDir>
#include <QFileDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QLineEdit>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_btnOpen_clicked()
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = "选择一个文件";
    QString filter = "文本文件(*.txt);;图片文件(*.jpg *.gif *.png);;所有文件(*.*)";
    
    QString aFileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);
    
    if (!aFileName.isEmpty())
        ui->plainTextEdit->appendPlainText(aFileName);
}


void Dialog::on_btnOpenMulti_clicked()
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = "选择多个文件";
    QString filter = "文本文件(*.txt);;图片文件(*.jpg *.gif *.png);;所有文件(*.*)";
    
    QStringList fileList = QFileDialog::getOpenFileNames(this, dlgTitle, curPath, filter);
    for (int i = 0; i < fileList.count(); ++i)
        ui->plainTextEdit->appendPlainText(fileList.at(i));
}


void Dialog::on_btnSelDir_clicked()
{
    QString curPath = QCoreApplication::applicationDirPath();
    
    QString dlgTitle = "选择一个目录";
    QString selectedDir = QFileDialog::getExistingDirectory(this, dlgTitle, curPath, QFileDialog::ShowDirsOnly);
    if (!selectedDir.isEmpty())
        ui->plainTextEdit->appendPlainText(selectedDir);
}


void Dialog::on_btnSave_clicked()
{
    QString curPath = QCoreApplication::applicationDirPath();
    QString dlgTitle = "保存文件";
    QString filter = "文本文件(*.txt);;h文件(*.h);;C++文件(*.cpp);;所有文件(*.*)";
    QString aFileName = QFileDialog::getSaveFileName(this, dlgTitle, curPath, filter);
    if (!aFileName.isEmpty())
        ui->plainTextEdit->appendPlainText(aFileName);
}


void Dialog::on_btnColor_clicked()
{
    QPalette pal = ui->plainTextEdit->palette();
    QColor iniColor = pal.color(QPalette::Text);
    QColor color = QColorDialog::getColor(iniColor, this, "选择颜色");
    if (color.isValid())
    {
        pal.setColor(QPalette::Text, color);
        ui->plainTextEdit->setPalette(pal);
    }
}


void Dialog::on_btnFont_clicked()
{
    QFont iniFont = ui->plainTextEdit->font();
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok, iniFont, this);
    if (ok)
        ui->plainTextEdit->setFont(font);
}

void Dialog::on_btnMsgQuestion_clicked()
{
    QString dlgTitle = "Question消息框";
    QString strInfo = "文件已被修改，是否保存修改";
    
    QMessageBox::StandardButton defaultButton = QMessageBox::NoButton;
    
    QMessageBox::StandardButton result;
    
    result = QMessageBox::question(this, dlgTitle, strInfo, QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel, defaultButton);
    
    if (result == QMessageBox::Yes)
        ui->plainTextEdit->appendPlainText("Question消息框：Yes被选择");
    else if (result == QMessageBox::No)
        ui->plainTextEdit->appendPlainText("Question消息框：No被选择");
    else if (result == QMessageBox::Cancel)
        ui->plainTextEdit->appendPlainText("Question消息框：Cancel被选择");
    else
        ui->plainTextEdit->appendPlainText("Question消息框：无选择");
                
}


void Dialog::on_btnMsgInformation_clicked()
{
    QString dlgTitle = "information消息框";
    QString strInfo = "文件已经打开，字体大小已设置";
    
    QMessageBox::information(this, dlgTitle, strInfo, QMessageBox::Ok, QMessageBox::NoButton);
}


void Dialog::on_btnMsgWarning_clicked()
{
    QString dlgTitle = "warning 消息框";
    QString strInfo = "文件内容已经被修改";
    
    QMessageBox::warning(this, dlgTitle, strInfo);
}


void Dialog::on_btnMsgCritical_clicked()
{
    QString dlgTitle = "critical消息框";
    QString strInfo = "有不明程序访问网络";
    
    QMessageBox::critical(this, dlgTitle, strInfo);
}


void Dialog::on_btnMsgAbout_clicked()
{
    QString dlgTitle = "about消息框";
    QString strInfo = "我开发的数据库查看软件 V1.0 \n 保留所有版权";
    
    QMessageBox::about(this, dlgTitle, strInfo);
}


void Dialog::on_btnMsgAboutQt_clicked()
{
    QString dlgTitle = "aboutQt消息框";
    QMessageBox::aboutQt(this, dlgTitle);
}


void Dialog::on_btnClearText_clicked()
{
    ui->plainTextEdit->clear();
}


void Dialog::on_btnInputString_clicked()
{
    QString dlgTitle = "输入文字对话框";
    QString txtLabel = "请输入文件名";
    QString defaultInput = "新建文件.txt";
    
    QLineEdit::EchoMode echoMode = QLineEdit::Password;
    
    bool ok = false;
    QString text = QInputDialog::getText(this, dlgTitle, txtLabel, echoMode, defaultInput, &ok);
    if (ok && !text.isEmpty())
        ui->plainTextEdit->appendPlainText(text);
}


void Dialog::on_btnInputInt_clicked()
{
    QString dlgTitle = "输入整数对话框";
    QString txtLabel = "设置字体大小";
    int defaultValue = ui->plainTextEdit->font().pointSize();
    int minValue = 6;
    int maxValue = 50;
    int stepValue = 1;
    bool ok = false;
    int inputValue = QInputDialog::getInt(this, dlgTitle, txtLabel, defaultValue, minValue, maxValue, stepValue, &ok);
    if (ok)
    {
        QFont font = ui->plainTextEdit->font();
        font.setPointSize(inputValue);
        ui->plainTextEdit->setFont(font);
    }
}


void Dialog::on_btnInputFloat_clicked()
{
    QString dlgTitle = "输入浮点数对话框";
    QString txtLabel = "输入一个浮点数";
    float defaultValue = 3.13;
    
    float minValue = 0;
    float maxValue = 10000;
    
    int decimals = 2;
    
    bool ok = false;
    float inputValue = QInputDialog::getDouble(this, dlgTitle, txtLabel, defaultValue, minValue, maxValue, decimals, &ok);
    if (ok)
    {
        QString str = QString::asprintf("输入了一个浮点数:%.2f", inputValue);
        ui->plainTextEdit->appendPlainText(str);
    }
}


void Dialog::on_btnInputItem_clicked()
{
    QStringList items;
    items << "优化" << "良好" << "合格" << "不合格";
    
    QString dlgTitle = "条目选择对话框";
    QString txtLabel = "请选择级别";
    int curIndex = 0;
    bool editable = true;
    bool ok = false;
    QString text = QInputDialog::getItem(this, dlgTitle, txtLabel, items, curIndex, editable, &ok);
    
    if (ok && !text.isEmpty())
        ui->plainTextEdit->appendPlainText(text);
}





