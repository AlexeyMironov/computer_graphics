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

private:
    Ui::MainWindow *ui;
    void OpenDocument(QString fileName);
    void SaveDocument(QString fileName) const;
    NewRowDialog *nd;
};

#endif // MAINWINDOW_H
