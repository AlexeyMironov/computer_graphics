#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "editedtablemodel.h"
//#include "newrowdialog.h"

class NewRowDialog;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    EditedTableModel *model;
private slots:
    void on_actionInsert_Row_triggered();
    void on_actionDelete_Row_triggered();
    void on_actionSave_Ctrl_S_triggered();
    void on_actionSave_As_triggered();
    void on_actionOpen_Ctrl_O_triggered();
    void on_actionNew_Table_Ctrl_N_triggered();
    void on_dataChanged();

private:
    Ui::MainWindow *ui;
    void OpenDocument(QString fileName);
    void SaveDocument(QString fileName) const;
    bool m_dataChanged = false;
    NewRowDialog *m_newDialog = nullptr;
    QString m_fileName;
};

#endif // MAINWINDOW_H                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
