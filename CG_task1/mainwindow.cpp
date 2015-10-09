#include "mainwindow.h"
#include "newrowdialog.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>

const QString fileName = "Population";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new EditedTableModel();
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0, 100);
    ui->tableView->setColumnWidth(1, 150);
    OpenDocument(fileName);
    nd = nullptr;
}

MainWindow::~MainWindow()
{
    SaveDocument(fileName);
    delete ui, model;
    if (nd)
    {
        delete nd;
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
    if (!nd)
    {
        nd = new NewRowDialog(this);
    }
    nd->show();
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
