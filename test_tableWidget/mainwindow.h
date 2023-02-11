#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qwintspindelegate.h"

QT_BEGIN_NAMESPACE

class QLabel;
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
private:
    enum CellType 
    {
        ctName = 1000,
        ctSex,
        ctBirth,
        ctNation,
        ctPartyM,
        ctScore
    };
    
    enum FieldColNum 
    {
        colName = 0,
        colSex,
        colBirth,
        colNation,
        colScore,
        colPartyM
    };
    
    QLabel *labCellIndex;
    QLabel *labCellType;
    QLabel *labStudID;
    
    
    QWIntSpinDelegate spinDelegate;
    
private:
    void createItemsARow(int rowNo, QString name, QString sex, QDate birth, QString nation, bool isPM, int score);
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private slots:
    void on_btnSetHeader_clicked();
    
    void on_btnSetRows_clicked();
    
    void on_btnIniData_clicked();
    
    void on_btnInsertRow_clicked();
    
    void on_btnAppendRow_clicked();
    
    void on_btnDelCurRow_clicked();
    
    void on_btnAutoHeight_clicked();
    
    void on_btnAutoWidth_clicked();
    
    void on_btnReadToEdit_clicked();
    
    void on_chkBoxRowColor_clicked(bool checked);
    
    void on_chkBoxTabEditable_clicked(bool checked);
    
    void on_chkBoxHeaderH_clicked(bool checked);
    
    void on_chkBoxHeaderV_clicked(bool checked);
    
    void on_rBtnSelectRow_clicked();
    
    void on_rBtnSelectItem_clicked();
    
    void on_tableIfno_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
    
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
