#include "mainwindow.h"
#include "newrowdialog.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QFileDialog>

QString fileName = "Population";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new EditedTableModel();
    QObject::connect(model, SIGNAL(dataChanged()),this, SLOT(on_dataChanged()));
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0, 100);
    ui->tableView->setColumnWidth(1, 150);
    OpenDocument(fileName);
}

MainWindow::~MainWindow()
{
    //SaveDocument(fileName);
    if (m_dataChanged)
    {
        auto reply = QMessageBox::question((QWidget*)this, "Table editor",
                                     "Document was modified. Do you want to save it?",
                                     (QMessageBox::StandardButtons)(QMessageBox::Yes | QMessageBox::No));
        if (reply == QMessageBox::Yes)
        {
            on_actionSave_Ctrl_S_triggered();
        }
    }
    delete ui;
    delete model;
    if (m_newDialog)
    {
        delete m_newDialog;
    }
}

void MainWindow::SaveDocument(QString fileName) const
{
    QJsonArray values;
    auto data = model->getData();
    for (auto valuePair : data)
    {
        QJsonObject value;
        value[valuePair.countryName] = valuePair.population;
        values.append(value);
    }

    QJsonObject jsonData;
    jsonData["values"] = values;

    QJsonDocument json(jsonData);

    QFile saveFile(fileName);

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't create file");
        return;
    }

    saveFile.write(json.toJson());
}

void MainWindow::OpenDocument(QString fileName)
{
    QFile jsonFile(fileName);
    if (!jsonFile.open(QIODevice::ReadOnly))
    {
        QMessageBox msgBox;
        msgBox.setText("Couldn't open file");
        msgBox.exec();
        return;
    }

    QJsonDocument json = QJsonDocument::fromJson(jsonFile.readAll());
    if (json.isNull())
    {
        QMessageBox msgBox;
        msgBox.setText("The file is not a valid json document");
        msgBox.exec();
        return;
    }

    jsonFile.close();

    QJsonValue values = json.object()["values"];

    if (values == QJsonValue::Undefined)
    {
        QMessageBox msgBox;
        msgBox.setText("The file contains invalid data");
        msgBox.exec();
        return;
    }

    model->clear();

    QJsonArray valuesArray = values.toArray();
    for (auto value : valuesArray)
    {
        QJsonObject valuePair = value.toObject();
        QString countryName = valuePair.keys()[0];
        model->addRow(countryName, valuePair[countryName].toInt());
    }
}

void MainWindow::on_actionInsert_Row_triggered()
{
    if (!m_newDialog)
    {
        m_newDialog = new NewRowDialog(this);
    }
    m_newDialog->show();
}

void MainWindow::on_actionDelete_Row_triggered()
{
    QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();
    QSet<int> rowsToDelete;

    for (int i = 0; i < indexes.count(); ++i)
    {
       rowsToDelete.insert(indexes.at(i).row());
    }

    for (auto it = rowsToDelete.begin(); it != rowsToDelete.end(); it++)
    {
       model->removeRow(*it);
    }
}
void MainWindow::on_dataChanged()
{
   m_dataChanged = true;
}

void MainWindow::on_actionSave_Ctrl_S_triggered()
{
    if (m_fileName.length() == 0)
    {
        m_fileName = QFileDialog::getSaveFileName(this,("Save Document"),QDir::currentPath(),("Json files (*.json);;Any files (*)") );
    }
    if (m_fileName.length() > 0)
    {
        SaveDocument(m_fileName);
        m_dataChanged = false;
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    m_fileName = QFileDialog::getSaveFileName(this,("Save Document"),QDir::currentPath(),("Json files (*.json);;Any files (*)") );
    if (m_fileName.length() > 0)
    {
        SaveDocument(m_fileName);
        m_dataChanged = false;
    }

}

void MainWindow::on_actionOpen_Ctrl_O_triggered()
{
    if (m_dataChanged)
    {
        auto reply = QMessageBox::question((QWidget*)this, "Table editor",
                                     "Document was modified. Do you want to save it?",
                                     (QMessageBox::StandardButtons)(QMessageBox::Yes | QMessageBox::No));
        if (reply == QMessageBox::Yes)
        {
            on_actionSave_Ctrl_S_triggered();
        }
    }

    m_fileName = QFileDialog::getOpenFileName(this, ("Open File"),QDir::currentPath(),("Json files (*.json);;Any files (*)"));

    if (m_fileName.length() > 0)
    {
        //fileName = "";
        model->clear();
        model = new EditedTableModel();
        ui->tableView->setModel(model);
        ui->tableView->setColumnWidth(0, 100);
        ui->tableView->setColumnWidth(1, 150);
        OpenDocument(m_fileName);
        m_dataChanged = false;
    }
}

void MainWindow::on_actionNew_Table_Ctrl_N_triggered()
{
    if (m_dataChanged)
    {
        auto reply = QMessageBox::question((QWidget*)this, "Table editor",
                                     "Document was modified. Do you want to save it?",
                                     (QMessageBox::StandardButtons)(QMessageBox::Yes | QMessageBox::No)| QMessageBox::Cancel);
        if (reply == QMessageBox::Yes)
        {
            on_actionSave_As_triggered();
        }
        else if (reply == QMessageBox::Cancel)
        {
            return;
        }
    }

    //fileName = "";
    model->clear();
    model = new EditedTableModel();
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0, 100);
    ui->tableView->setColumnWidth(1, 150);
    m_dataChanged = true;

}
