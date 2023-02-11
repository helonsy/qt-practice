#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>


#define     FixedColumnCount    6

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    theModel = new QStandardItemModel(2, FixedColumnCount, this);
    theSelection = new QItemSelectionModel(theModel);
    connect(theSelection, SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(on_currentChanged(QModelIndex,QModelIndex)));
    
    ui->tableView->setModel(theModel);
    ui->tableView->setSelectionModel(theSelection);
    
    ui->tableView->setItemDelegateForColumn(0, &intSpinDelegate);
    ui->tableView->setItemDelegateForColumn(1, &floatSpinDelegate);
    ui->tableView->setItemDelegateForColumn(2, &floatSpinDelegate);
    ui->tableView->setItemDelegateForColumn(3, &floatSpinDelegate);
    ui->tableView->setItemDelegateForColumn(4, &comboBoxDelegate);
    
    setCentralWidget(ui->splitter);
    
    labCurFile = new QLabel("当前文件：", this);
    labCurFile->setMinimumWidth(300);
    
    labCellPos = new QLabel("当前单元格", this);
    labCellPos->setMinimumWidth(180);
    labCellPos->setAlignment(Qt::AlignCenter);
    
    labCellText = new QLabel("单元格内容", this);
    labCellText->setMinimumWidth(200);
    
    ui->statusbar->addWidget(labCurFile);
    ui->statusbar->addWidget(labCellPos);
    ui->statusbar->addWidget(labCellText);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    if (current.isValid())
    {
        labCellPos->setText(QString::asprintf("当前单元格: %d行, %d列", current.row(), current.column()));
        
        QStandardItem *aItem;
        aItem = theModel->itemFromIndex(current);
        this->labCellText->setText("单元格内容: " + aItem->text());
        
        QFont font = aItem->font();
        ui->actFontBold->setChecked(font.bold());
    }
}

void MainWindow::on_actOpen_triggered()
{
    QString curPath;
    QString aFileName;
    QString str;
    
    curPath = QCoreApplication::applicationDirPath();
    aFileName = QFileDialog::getOpenFileName(this, tr("打开一个文件"), curPath, "井斜数据文件(*.txt);;所有文件(*.*)");
    
    if (aFileName.isEmpty())
        return;
    
    QStringList fFileContent;
    QFile aFile(aFileName);
    if (aFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream aStream(&aFile);
        ui->plainTextEdit->clear();
        while(!aStream.atEnd())
        {
            str = aStream.readLine();
            ui->plainTextEdit->appendPlainText(str);
            fFileContent.append(str);
        }
        aFile.close();
        
        this->labCurFile->setText("当前文件：" + aFileName);
        ui->actAppend->setEnabled(true);
        ui->actInsert->setEnabled(true);
        ui->actDelete->setEnabled(true);
        ui->actSave->setEnabled(true);
        
        iniModelFromStringList(fFileContent);
    }
}


void MainWindow::on_actSave_triggered()
{
    QString curPath;
    QString aFileName;
    curPath = QCoreApplication::applicationDirPath();
    aFileName = QFileDialog::getSaveFileName(this, tr("选择一个文件"), curPath
                                             , "井斜数据文件(*.txt);;所有文件(*.*)");
    
    if (aFileName.isEmpty())
        return;
    
    QFile aFile(aFileName);
    if (!aFile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate))
        return;
    
    QTextStream aStream(&aFile);
    
    QStandardItem *aItem;
    QString str;
    ui->plainTextEdit->clear();
    
    for (int i = 0; i < theModel->columnCount(); ++i)
    {
        aItem = theModel->horizontalHeaderItem(i);
        str = str + aItem->text() + "\t\t";
    }
    aStream << str << "\n";
    ui->plainTextEdit->appendPlainText(str);
    
    for (int i = 0; i < theModel->rowCount(); ++i)
    {
        str = "";
        int j = 0;
        for (int j = 0; j < theModel->columnCount() - 1; ++j)
        {
            aItem = theModel->item(i, j);
            str = str + aItem->text() + QString::asprintf("\t\t");
        }
        
        aItem = theModel->item(i, j);
        if (aItem->checkState() == Qt::Checked)
            str = str + "1";
        else
            str = str + "0";
        
        ui->plainTextEdit->appendPlainText(str);
        aStream << str << "\n";
    }
}


void MainWindow::on_actAppend_triggered()
{
    QList<QStandardItem*> aItemList;
    QStandardItem *aItem;
    QString str;
    for (int i = 0; i < FixedColumnCount - 2; ++i)
    {
        aItem = new QStandardItem("0");
        aItemList << aItem;
    }
    
    aItem = new QStandardItem("优");
    aItemList << aItem;
    
    str = theModel->headerData(theModel->columnCount() - 1, Qt::Horizontal, Qt::DisplayRole).toString();
    aItem = new QStandardItem(str);
    aItem->setCheckable(true);
    aItemList << aItem;
    
    theModel->insertRow(theModel->rowCount(), aItemList);
    QModelIndex curIndex = theModel->index(theModel->rowCount() - 1, 0);
    theSelection->clearSelection();
    theSelection->setCurrentIndex(curIndex, QItemSelectionModel::Select);
}


void MainWindow::on_actInsert_triggered()
{
    QList<QStandardItem*> aItemList;
    QStandardItem *aItem;
    QString str;
    for (int i = 0; i < FixedColumnCount - 2; ++i)
    {
        aItem = new QStandardItem("0");
        aItemList << aItem;
    }
    aItem = new QStandardItem("优");
    aItemList << aItem;
    
    str = theModel->headerData(theModel->columnCount() - 1, Qt::Horizontal, Qt::DisplayRole).toString();
    aItem = new QStandardItem(str);
    aItem->setCheckable(true);
    aItemList << aItem;
    QModelIndex curIndex = theSelection->currentIndex();
    theModel->insertRow(curIndex.row(), aItemList);
    theSelection->clearSelection();
    theSelection->setCurrentIndex(curIndex, QItemSelectionModel::Select);
}


void MainWindow::on_actDelete_triggered()
{
    QModelIndex curIndex = theSelection->currentIndex();
    if (curIndex.row() == theModel->rowCount() - 1)
        theModel->removeRow(curIndex.row());
    else
    {
        theModel->removeRow(curIndex.row());
        theSelection->setCurrentIndex(curIndex, QItemSelectionModel::Select);
    }
}


void MainWindow::on_actModelData_triggered()
{
    ui->plainTextEdit->clear();
    QStandardItem *aItem;
    QString str;
    
    for (int i = 0; i < theModel->columnCount(); ++i)
    {
        aItem = theModel->horizontalHeaderItem(i);
        str = str + aItem->text() + "\t";
    }
    ui->plainTextEdit->appendPlainText(str);

    for (int i = 0; i < theModel->rowCount(); ++i)
    {
        str = "";
        int j = 0;
        for (j = 0; j < theModel->columnCount() - 1; ++j)
        {
            aItem = theModel->item(i, j);
            str = str + aItem->text() + QString::asprintf("\t");
        }
        aItem = theModel->item(i, j);
        if (aItem->checkState() == Qt::Checked)
            str = str + "1";
        else
            str = str + "0";
        
        ui->plainTextEdit->appendPlainText(str);
    }
}


void MainWindow::on_actAlignLeft_triggered()
{
    if (!theSelection->hasSelection())
        return;
    
    QModelIndexList selectedIndex = theSelection->selectedIndexes();
    
    QModelIndex aIndex;
    QStandardItem *aItem;
    
    for (int i = 0; i < selectedIndex.count(); ++i)
    {
        aIndex = selectedIndex.at(i);
        aItem = theModel->itemFromIndex(aIndex);
        aItem->setTextAlignment(Qt::AlignLeft);
    }
}


void MainWindow::on_actFontBold_triggered(bool checked)
{
    if (!theSelection->hasSelection())
        return;
    
    QModelIndexList selectedIndexes = theSelection->selectedIndexes();
    
    QModelIndex aIndex;
    QStandardItem *aItem;
    QFont font;
    
    for (int i = 0; i < selectedIndexes.count(); ++i)
    {
        aIndex = selectedIndexes.at(i);
        aItem = theModel->itemFromIndex(aIndex);
        font = aItem->font();
        font.setBold(checked);
        aItem->setFont(font);
    }
}


void MainWindow::on_actAlignCenter_triggered()
{
    if (!theSelection->hasSelection())
        return;
    
    QModelIndexList selectedIndexes = theSelection->selectedIndexes();
    
    QModelIndex aIndex;
    QStandardItem *aItem;
    QFont font;
    
    for (int i = 0; i < selectedIndexes.count(); ++i)
    {
        aIndex = selectedIndexes.at(i);
        aItem = theModel->itemFromIndex(aIndex);
        aItem->setTextAlignment(Qt::AlignHCenter);
    }
}

void MainWindow::iniModelFromStringList(QStringList& aFileContent)
{
    // 从一个StringList  获取数据，初始化Model
    int rowCnt = aFileContent.count();
    theModel->setRowCount(rowCnt - 1);
    
    QString header;
    QString aLineText;
    QStandardItem *aItem;
    QStringList headerList;
    QStringList tempList;
    
    // 设置表头 
    header = aFileContent.at(0);
    headerList = header.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    theModel->setHorizontalHeaderLabels(headerList);
    
    int j = 0;
    for (int i = 1; i < rowCnt; ++i)
    {
        aLineText = aFileContent.at(i);
        tempList = aLineText.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
        for (j = 0; j < FixedColumnCount - 1; j++)
        {
            aItem = new QStandardItem(tempList.at(j));
            theModel->setItem(i - 1, j, aItem);
        }
        aItem = new QStandardItem(headerList.at(j));
        aItem->setCheckable(true);
        if (tempList.at(j) == "0")
            aItem->setCheckState(Qt::Unchecked);
        else
            aItem->setCheckState(Qt::Checked);
        
        theModel->setItem(i - 1, j, aItem);
    }
}

void MainWindow::on_actAlignRight_triggered()
{
    if (!theSelection->hasSelection())
        return;
    
    QModelIndexList selectedIndex = theSelection->selectedIndexes();
    
    QModelIndex aIndex;
    QStandardItem *aItem;
    
    for (int i = 0; i < selectedIndex.count(); ++i)
    {
        aIndex = selectedIndex.at(i);
        aItem = theModel->itemFromIndex(aIndex);
        aItem->setTextAlignment(Qt::AlignRight);
    }
}

