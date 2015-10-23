#ifndef EDITEDTABLEMODEL_H
#define EDITEDTABLEMODEL_H

#include <QAbstractTableModel>
#include <QFile>
#include <QTextStream>
#include <QList>
#include <QStringList>

struct TData
{
  QString countryName;
  int population;
};

class EditedTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    EditedTableModel(QObject * parent = 0);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex & parent = QModelIndex()) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    void addRow(const QString &countryName, int population);
    QVector<TData> getData() const;
    void clear();
    Qt::ItemFlags flags(const QModelIndex & index) const;
    void removeRow(int row);
signals:
    void dataChanged();
private:
    QVector<TData> m_data;
};

#endif // EDITEDTABLEMODEL_H
