#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qwdialogheaders.h"
#include "qwdialoglocate.h"

#include <QItemSelectionModel>
#include <QLabel>
#include <QMainWindow>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
private:
    QLabel *m_labCellPos;
    QLabel *m_labCellText;
    
    QStandardItemModel *theModel;
    QItemSelectionModel *theSelection;
    
    QWDialogHeaders *dlgSetHeaders = nullptr;
    QWDialogLocate *dlgLocate = nullptr;
    
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
    void setActLocateEnable(bool enable);
    void setACellText(int row, int column, QString text);
    void setDlgLocateNull();
    
    void closeEvent(QCloseEvent *event)override;
    
private slots:
    void on_currentChanged(const QModelIndex &current, const QModelIndex &previous);
    
    void on_actTab_SetSize_triggered();
    
    void on_actTab_SetHeader_triggered();
    
    void on_actTab_Locate_triggered();
    
    void on_tableView_clicked(const QModelIndex &index);
    
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
