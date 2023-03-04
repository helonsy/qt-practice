#include "mainwindow.h"
#include "qwdialogsize.h"
#include "ui_mainwindow.h"

#include <QCloseEvent>
#include <QMessageBox>

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton result = QMessageBox::question(this, "确认", "确定要退出本程序吗？",
                                        QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel,
                                        QMessageBox::No);
    
    if (result == QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    theModel = new QStandardItemModel(10, 5, this);
    theSelection = new QItemSelectionModel(theModel);
    
    connect(theSelection, SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(on_currentChanged(QModelIndex,QModelIndex)));
    
    ui->tableView->setModel(theModel);
    ui->tableView->setSelectionModel(theSelection);
    
    //setCentralWidget(ui->tableView);
    
    m_labCellPos = new QLabel("当前单元格:", this);
    m_labCellPos->setMinimumWidth(180);
    m_labCellPos->setAlignment(Qt::AlignHCenter);
    m_labCellText = new QLabel("单元格内容：", this);
    m_labCellText->setMinimumWidth(200);
    ui->statusbar->addWidget(m_labCellPos);
    ui->statusbar->addWidget(m_labCellText);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setActLocateEnable(bool enable)
{
    ui->actTab_Locate->setEnabled(enable);
}

void MainWindow::setACellText(int row, int column, QString text)
{// 定位到单元格，并设置字符串
    
    QModelIndex index = theModel->index(row, column);
    theSelection->clearSelection();
    theSelection->setCurrentIndex(index, QItemSelectionModel::Select);
    theModel->setData(index, text, Qt::DisplayRole);
}

void MainWindow::setDlgLocateNull()
{
    dlgLocate = NULL;
}

void MainWindow::on_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    if (current.isValid())
    {
        m_labCellPos->setText(QString::asprintf("当前单元格：%d行， %d列", current.row(), current.column()));
        QStandardItem *aItem = theModel->itemFromIndex(current);
        this->m_labCellText->setText("单元格内容：" + aItem->text());
    }
}

void MainWindow::on_actTab_SetSize_triggered()
{// 模态对话框，动态创建，用过后删除
   
    QWDialogSize *dlgTableSize = new QWDialogSize(this);
//对话框关闭时自动删除对话框对象，用于不需要读取返回值的对话框
//如果需要获取对话框的返回值，不能设置该属性，可以在调用完对话框后删除对话框    
    Qt::WindowFlags flags = dlgTableSize->windowFlags();
    dlgTableSize->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint); //设置对话框固定大小
    dlgTableSize->setRowColumn(theModel->rowCount(), theModel->columnCount()); //对话框数据初始化
    
    int ret = dlgTableSize->exec();
    if (ret == QDialog::Accepted)
    {//OK键被按下，获取对话框上的输入，设置行数和列数
        
        int cols = dlgTableSize->columnCount();
        theModel->setColumnCount(cols);
        
        int rows = dlgTableSize->rowCount();
        theModel->setRowCount(rows);
    }
    delete dlgTableSize;
}


void MainWindow::on_actTab_SetHeader_triggered()
{// 一次创建，多次调用，对话框关闭时只是隐藏
    
    if (dlgSetHeaders == nullptr)
        dlgSetHeaders = new QWDialogHeaders(this);
    
    if (dlgSetHeaders->headerList().count() != theModel->columnCount())
    {// 如果表头列数变化，重新初始化
        
        QStringList strList;
        for (int i = 0; i < theModel->columnCount(); ++i)
            strList.append(theModel->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString());
        dlgSetHeaders->setHeaderList(strList);
    }
    
    int ret = dlgSetHeaders->exec();
    if (ret == QDialog::Accepted)
    {
        QStringList strList = dlgSetHeaders->headerList();
        theModel->setHorizontalHeaderLabels(strList);
    }
}


void MainWindow::on_actTab_Locate_triggered()
{//创建StayOnTop的对话框，对话框关闭时自动删除
 // 通过控制actTab_Locate的enable属性避免重复点击
    ui->actTab_Locate->setEnabled(false);
    
    dlgLocate = new QWDialogLocate(this);
    dlgLocate->setAttribute(Qt::WA_DeleteOnClose);
    Qt::WindowFlags flags = dlgLocate->windowFlags(); // 获取已有flags
    
    dlgLocate->setWindowFlags(flags | Qt::WindowStaysOnTopHint); //设置对话框固定大侠，StayOnTop
    
    // 对话框初始化设置
    dlgLocate->setSpinRange(theModel->rowCount(), theModel->columnCount());
    QModelIndex curIndex = theSelection->currentIndex();
    if (curIndex.isValid())
        dlgLocate->setSpinValue(curIndex.row(), curIndex.column());
    
    dlgLocate->show(); // 非模态显示对话框
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{//单机单元格时，将单元格的行号，列号设置到对话框上
    
    if (dlgLocate != nullptr)
        dlgLocate->setSpinValue(index.row(), index.column());
}

