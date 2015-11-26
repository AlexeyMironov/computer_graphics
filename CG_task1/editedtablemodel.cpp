#include "editedtablemodel.h"

EditedTableModel::EditedTableModel(QObject * parent)
{
    (void)parent;
}

QVariant EditedTableModel::data(const QModelIndex & index, int role) const
{
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        {
            //return QVariant("test");
            if (index.column() == 0)
            {
               return QVariant(m_data[index.row()].countryName);
            }
            else
            {
               return QVariant( m_data[index.row()].population);
            }
        }

        return QVariant::Invalid;
}
int EditedTableModel::rowCount(const QModelIndex & parent) const
{
    (void)parent;
    return m_data.size();
}
int EditedTableModel::columnCount(const QModelIndex & parent) const
{
   (void)parent;
    return 2;
}

QVariant EditedTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Vertical)
        {
            return QVariant(section);
        }
        else if(orientation == Qt::Horizontal)
        {
            if (section == 0)
            {
                return QVariant("Country name");
            }
            else
            {
               return QVariant("Population (in millions)");
            }
        }
    }

    return QVariant::Invalid;
}

bool EditedTableModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if (role == Qt::EditRole)
    {
        if (index.column() == 0)
        {
            m_data[index.row()].countryName = value.toString();
        }
        else
        {
            m_data[index.row()].population = value.toInt();
        }
        emit dataChanged();
        return true;
    }
    else
    {
        return QAbstractTableModel::setData(index, value, role);
    }
}

void EditedTableModel::addRow(const QString &countryName, int population)
{
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    TData ti = {countryName, population};

    m_data.push_back(ti);
    emit dataChanged();
    endInsertRows();
}

QVector<TData> EditedTableModel::getData() const
{
    return m_data;
}

void EditedTableModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, m_data.size());
    m_data.clear();
    endRemoveRows();
}

Qt::ItemFlags EditedTableModel::flags(const QModelIndex & index) const
{
    (void)index;
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

void EditedTableModel::removeRow(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    m_data.remove(row);
    emit dataChanged();
    endRemoveRows();
}


