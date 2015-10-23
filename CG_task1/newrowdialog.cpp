#include "newrowdialog.h"
#include "mainwindow.h"
#include "ui_newrowdialog.h"

NewRowDialog::NewRowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewRowDialog)
{
    ui->setupUi(this);
    m_window = dynamic_cast<MainWindow*>(parent);
}

NewRowDialog::~NewRowDialog()
{
    delete ui;
}

void NewRowDialog::on_buttonBox_accepted()
{
    m_window->model->addRow(ui->countryName->toPlainText(), ui->population->value());
}
