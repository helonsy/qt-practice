#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include "qwintspindelegate.h"
#include "qwfloatspindelegate.h"
#include "qwcomboboxdelegate.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
private:
    QLabel *labCurFile;
    QLabel *labCellPos;
    QLabel *labCellText;
    
    QWIntSpinDelegate intSpinDelegate;
    QWFloatSpinDelegate floatSpinDelegate;
    QWComboBoxDelegate comboBoxDelegate;
    
    QString fCurFile;
    
    QStandardItemModel *theModel;
    QItemSelectionModel *theSelection;
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private slots:
    void on_currentChanged(const QModelIndex &current, const QModelIndex &previous);
    
    
    void on_actOpen_triggered();
    
    void on_actSave_triggered();
    
    void on_actAppend_triggered();
    
    void on_actInsert_triggered();
    
    void on_actDelete_triggered();
    
    void on_actModelData_triggered();
    
    void on_actAlignLeft_triggered();
    
    void on_actFontBold_triggered(bool checked);
    
    void on_actAlignCenter_triggered();

    void on_actAlignRight_triggered();
    
private:
    void iniModelFromStringList(QStringList&);
    
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
