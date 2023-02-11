#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->splitter);

    setActionsForButton();
    createSelectionPopMenu();
    
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    QMenu *menuList = new QMenu(this);
    
    menuList->addAction(ui->actListIni);
    menuList->addAction(ui->actListClear);
    menuList->addAction(ui->actListInsert);
    menuList->addAction(ui->actListAppend);
    menuList->addAction(ui->actListDelete);
    menuList->addSeparator();
    menuList->addAction(ui->actSelALL);
    menuList->addAction(ui->actSelNone);
    menuList->addAction(ui->actSelInvs);
    
    menuList->exec(QCursor::pos());
    
    delete menuList;
}

void MainWindow::setActionsForButton()
{
    ui->tBtnListIni->setDefaultAction(ui->actListIni);
    ui->tBtnListClear->setDefaultAction(ui->actListClear);
    ui->tBtnListInsert->setDefaultAction(ui->actListInsert);
    ui->tBtnListAppend->setDefaultAction(ui->actListAppend);
    ui->tBtnListDelete->setDefaultAction(ui->actListDelete);

    ui->tBtnSelALL->setDefaultAction(ui->actSelALL);
    ui->tBtnSelNone->setDefaultAction(ui->actSelNone);
    ui->tBtnSelInvs->setDefaultAction(ui->actSelInvs);
}

void MainWindow::createSelectionPopMenu()
{
    QMenu* menuSelection = new QMenu(this);
    menuSelection->addAction(ui->actSelALL);
    menuSelection->addAction(ui->actSelNone);
    menuSelection->addAction(ui->actSelInvs);

    ui->tBtnSelectItem->setPopupMode(QToolButton::MenuButtonPopup);
    ui->tBtnSelectItem->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->tBtnSelectItem->setDefaultAction(ui->actSelPopMenu);
    ui->tBtnSelectItem->setMenu(menuSelection);

    QToolButton *aBtn = new QToolButton(this);
    aBtn->setPopupMode(QToolButton::InstantPopup);
    aBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    aBtn->setDefaultAction(ui->actSelPopMenu);
    aBtn->setMenu(menuSelection);
    ui->toolBar->addWidget(aBtn);
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->actQuit);
}


void MainWindow::on_actListIni_triggered()
{
    QListWidgetItem *aItem;

    QIcon aIcon;
    aIcon.addFile(":/images/images/check2.ico");
    bool chk = ui->chkBoxListEditable->isChecked();

    ui->listWidget->clear();
    for(int i = 0; i < 10; i++)
    {
        QString str = QString::asprintf("Item %d", i);
        aItem = new QListWidgetItem();

        aItem->setText(str);;
        aItem->setIcon(aIcon);
        aItem->setCheckState(Qt::Checked);
        if (chk)
            aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        else
            aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        ui->listWidget->addItem(aItem);
    }
}


void MainWindow::on_actSelALL_triggered()
{
    int cnt = ui->listWidget->count();
    for (int i = 0; i < cnt; ++i)
    {
        QListWidgetItem *aItem = ui->listWidget->item(i);
        aItem->setCheckState(Qt::Checked);
    }
}


void MainWindow::on_actSelNone_triggered()
{
    int i;
    int cnt;
    QListWidgetItem *aItem;
    cnt = ui->listWidget->count();
    for (i = 0; i < cnt; ++i)
    {
        aItem = ui->listWidget->item(i);
        aItem->setCheckState(Qt::Unchecked);
    }
}


void MainWindow::on_actSelInvs_triggered()
{
    int cnt;
    QListWidgetItem *aItem;
    cnt = ui->listWidget->count();
    for(int i = 0; i < cnt; ++i)
    {
        aItem = ui->listWidget->item(i);
        if (aItem->checkState() != Qt::Checked)
            aItem->setCheckState(Qt::Checked);
        else
            aItem->setCheckState(Qt::Unchecked);
    }
}


void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    QString str;
    if (current != NULL)
    {
        if (previous == NULL)
            str = "当前：" + current->text();
        else
            str = "前一项：" + previous->text() + "; 当前项：" + current->text();
        ui->lineEdit_2->setText(str);
    }
}



void MainWindow::on_toolBox_currentChanged(int index)
{
    ui->tabWidget->setCurrentIndex(index);
}


void MainWindow::on_actListInsert_triggered()
{
    QIcon aIcon;
    aIcon.addFile(":/images/images/check2.ico");
    
    bool chk = ui->chkBoxListEditable->isChecked();
    
    QListWidgetItem *aItem = new QListWidgetItem("New Inserted Item");
    aItem->setIcon(aIcon);
    aItem->setCheckState(Qt::Checked);
    if (chk)
        aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    else
        aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    
    ui->listWidget->insertItem(ui->listWidget->currentRow(), aItem);
}


void MainWindow::on_actListAppend_triggered()
{
    QIcon aIcon;
    aIcon.addFile(":/images/icons/check2.ico");
    
    bool chk = ui->chkBoxListEditable->isChecked();
    QListWidgetItem *aItem = new QListWidgetItem("New Added Item");
    aItem->setIcon(aIcon);
    aItem->setCheckState(Qt::Checked);
    if (chk)
        aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    else
        aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    
    ui->listWidget->addItem(aItem);
}


void MainWindow::on_actListDelete_triggered()
{
    int row = ui->listWidget->currentRow();
    QListWidgetItem *aItem = ui->listWidget->takeItem(row);
    delete aItem;
}


void MainWindow::on_chkBoxListEditable_clicked(bool checked)
{
    int i, cnt;
    QListWidgetItem *aItem;
    
    cnt = ui->listWidget->count();
    for (int i = 0; i < cnt; i++)
    {
        aItem = ui->listWidget->item(i);
        if (checked)
            aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        else
            aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    }
}




