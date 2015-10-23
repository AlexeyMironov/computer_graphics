#ifndef NEWROWDIALOG_H
#define NEWROWDIALOG_H

#include <QDialog>
//#include "mainwindow.h"

class MainWindow;
namespace Ui {
class NewRowDialog;
}

class NewRowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewRowDialog(QWidget *parent = 0);
    ~NewRowDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::NewRowDialog *ui;
    MainWindow *m_window;
};

#endif // NEWROWDIALOG_H
