#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDate>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->splitterMain);
    
    labCellIndex = new QLabel("当前单元格坐标：", this);
    labCellIndex->setMinimumWidth(250);
            
    labCellType = new QLabel("当前单元格类型", this);
    labCellType->setMinimumWidth(200);
    
    labStudID = new QLabel("学生ID: ", this);
    labStudID->setMinimumWidth(200);
       
    ui->statusbar->addWidget(labCellIndex);
    ui->statusbar->addWidget(labCellType);
    ui->statusbar->addWidget(labStudID);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::createItemsARow(int rowNo, QString name, QString sex, QDate birth, QString nation, bool isPM, int score)
{
    QTableWidgetItem *item;
    QString str;
    uint studId = 201605000;
    
    // 姓名
    item = new QTableWidgetItem(name, CellType::ctName);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    studId += rowNo;
    item->setData(Qt::UserRole, QVariant(studId));
    ui->tableIfno->setItem(rowNo, FieldColNum::colName, item);
    
    // 性别
    QIcon icon;
    if (sex == "男")
        icon.addFile(":/images/images/boy.ico");
    else
        icon.addFile(":/images/images/girl.ico");
    
    item = new QTableWidgetItem(sex, CellType::ctSex);
    item->setIcon(icon);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableIfno->setItem(rowNo, FieldColNum::colSex, item);
    
    // 出生日期 
    str = birth.toString("yyyy-MM-dd");
    item = new QTableWidgetItem(str, CellType::ctBirth);
    item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->tableIfno->setItem(rowNo, FieldColNum::colBirth, item);
    
    // 民族    
    item = new QTableWidgetItem(nation, CellType::ctNation);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableIfno->setItem(rowNo, FieldColNum::colNation, item);

    // 分数
    str.setNum(score);
    item = new QTableWidgetItem(str, CellType::ctScore);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableIfno->setItem(rowNo, FieldColNum::colScore, item);
    
    // 是否党员   
    item = new QTableWidgetItem("党员", CellType::ctPartyM);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    if (isPM)
        item->setCheckState(Qt::Checked);
    else
        item->setCheckState(Qt::Unchecked);
    
    ui->tableIfno->setItem(rowNo, FieldColNum::colPartyM, item);
}


void MainWindow::on_btnSetHeader_clicked()
{
    QTableWidgetItem *headerItem;
    QStringList headerText;
    headerText << "姓 名" << "性 别" << "出生日期" << "民 族" << "分 数" << "是否党员";
    ui->tableIfno->setColumnCount(headerText.count());
    for (int i = 0; i < ui->tableIfno->columnCount(); ++i)
    {
        headerItem = new QTableWidgetItem(headerText.at(i));
        QFont font = headerItem->font();
        font.setBold(true);
        font.setPointSize(12);
        
        headerItem->setFont(font);
        ui->tableIfno->setHorizontalHeaderItem(i, headerItem);
    }
    
    ui->tableIfno->setItemDelegateForColumn(FieldColNum::colScore, &spinDelegate);
}


void MainWindow::on_btnSetRows_clicked()
{
    ui->tableIfno->setRowCount(ui->spinRowCount->value());
    ui->tableIfno->setAlternatingRowColors(ui->chkBoxRowColor->isChecked());
}


void MainWindow::on_btnIniData_clicked()
{
    QString strName;
    QString strSex;
    
    bool isParty = false;
    
    QDate birth;
    birth.setDate(1980, 4, 7);
    ui->tableIfno->clearContents();
    
    int rows = ui->tableIfno->rowCount();
    for (int i = 0; i < rows; ++i)
    {
        strName = QString::asprintf("学生%d", i);
        if (i % 2 == 0)
            strSex = "男";
        else
            strSex = "女";
        
        createItemsARow(i, strName, strSex, birth, "汉族", isParty, 70);
        birth = birth.addDays(20);
        isParty = !isParty;
    }
}


void MainWindow::on_btnInsertRow_clicked()
{
    int curRow = ui->tableIfno->currentRow();
    ui->tableIfno->insertRow(curRow); // 在上面插入一行
    createItemsARow(curRow, "新学生", "男", QDate::fromString("1990-1-1", "yyyy-M-d"), "苗族", true, 60);
}


void MainWindow::on_btnAppendRow_clicked()
{
    int curRow = ui->tableIfno->rowCount();
    ui->tableIfno->insertRow(curRow);
    createItemsARow(curRow, "新生", "女", QDate::fromString("2000-1-1", "yyyy-M-d"), "满族", false, 50);
}


void MainWindow::on_btnDelCurRow_clicked()
{
    int curRow = ui->tableIfno->currentRow();
    ui->tableIfno->removeRow(curRow);
}


void MainWindow::on_btnAutoHeight_clicked()
{
    ui->tableIfno->resizeRowsToContents();
}


void MainWindow::on_btnAutoWidth_clicked()
{
    ui->tableIfno->resizeColumnsToContents();
}


void MainWindow::on_btnReadToEdit_clicked()
{
    QString str;
    QTableWidgetItem *cellItem;
    
    ui->textEdit->clear();
    int rowCount = ui->tableIfno->rowCount();
    for (int i = 0; i < rowCount; ++i)
    {
        str = QString::asprintf("第 %d 行：", i + 1);
        for (int j = 0; j < ui->tableIfno->columnCount() - 1; ++j)
        {
            cellItem = ui->tableIfno->item(i, j);
            str = str + cellItem->text() + "...";
        }
        cellItem = ui->tableIfno->item(i, FieldColNum::colPartyM);
        if (cellItem->checkState() == Qt::Checked)
            str = str + "党员";
        else
            str = str + "群众";
        
        ui->textEdit->appendPlainText(str);
    }
}


void MainWindow::on_chkBoxRowColor_clicked(bool checked)
{
    ui->tableIfno->setAlternatingRowColors(checked);
}


void MainWindow::on_chkBoxTabEditable_clicked(bool checked)
{
    if (checked)
        ui->tableIfno->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    else
        ui->tableIfno->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


void MainWindow::on_chkBoxHeaderH_clicked(bool checked)
{
    ui->tableIfno->horizontalHeader()->setVisible(checked);
}


void MainWindow::on_chkBoxHeaderV_clicked(bool checked)
{
    ui->tableIfno->verticalHeader()->setVisible(checked);
}


void MainWindow::on_rBtnSelectRow_clicked()
{
    ui->tableIfno->setSelectionBehavior(QAbstractItemView::SelectRows);    
}


void MainWindow::on_rBtnSelectItem_clicked()
{
    ui->tableIfno->setSelectionBehavior(QAbstractItemView::SelectItems);    
}


void MainWindow::on_tableIfno_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    Q_UNUSED(previousRow);
    Q_UNUSED(previousColumn);
 
     QTableWidgetItem* item=ui->tableIfno->item(currentRow,currentColumn); //获取单元格的 Item
     if  (item==NULL)
         return;
 
     labCellIndex->setText(QString::asprintf("当前单元格坐标：%d 行，%d 列",currentRow,currentColumn));
 
     int cellType=item->type();//获取单元格的类型
     labCellType->setText(QString::asprintf("当前单元格类型：%d",cellType));
 
     item=ui->tableIfno->item(currentRow,MainWindow::colName); //取当前行第1列的单元格的 item
     int ID=item->data(Qt::UserRole).toInt();//读取用户自定义数据
     labStudID->setText(QString::asprintf("学生ID：%d",ID));//学生ID
}

