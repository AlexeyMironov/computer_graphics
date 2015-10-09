#include "newrowdialog.h"
#include "mainwindow.h"
#include "ui_newrowdialog.h"

NewRowDialog::NewRowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewRowDialog)
{
    ui->setupUi(this);
    mw = dynamic_cast<MainWindow*>(parent);
}

NewRowDialog::~NewRowDialog()
{
    delete ui;
}

void NewRowDialog::on_buttonBox_accepted()
{
    mw->model->addRow(ui->countryName->toPlainText(), ui->population->value());
}
