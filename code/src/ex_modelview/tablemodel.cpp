#include "tablemodel.h"
#include <QFile>
#include <algorithm>
#include <QTextStream>
#include <QDebug>

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent), lang("ENG")
{}

TableModel::~TableModel() // деструктор
{}

void TableModel::openData(const QString &dir)
{
    QFile inputFile(dir);
    inputFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream inputStream(&inputFile);
    int res = 0;

    header = inputStream.readLine().replace("\"","").split(',');
    header.push_back("Total");
    int id = 1;
    while(!inputStream.atEnd())
    {
        QString line = inputStream.readLine();
        line = line.replace("\"", "");

        QList<QString> dataRow;
        for (QString& item : line.split(","))
            dataRow.append(item);
        races.insert(dataRow.at(1));

        res = (dataRow.at(5).toInt()) + (dataRow.at(6).toInt()) + (dataRow.at(7).toInt());
        dataRow.append(QString::number(res));
        dataTable.append(dataRow);
        Vhead.push_back(QString::number(id++));
    }
    inputFile.close();
    headRus.push_back("Пол");
    headRus.push_back("Группа");
    headRus.push_back("Уровень образования");
    headRus.push_back("Обед");
    headRus.push_back("Курс подготовки");
    headRus.push_back("Математика");
    headRus.push_back("Чтение");
    headRus.push_back("Письмо");
    headRus.push_back("Итог");
    emit layoutChanged();
}

void TableModel::saveData(const QString &dir)
{
    QFile outputFile(dir);
    outputFile.open(QFile::WriteOnly | QFile::Text);
    QTextStream outputStream(&outputFile);
    for (int i = 0; i < header.size(); i++)
        outputStream << header[i] << (i < header.size()-1? ',' : '\n');

    for (int i = 0; i < dataTable.size(); i++)
    {
        for (int j = 0; j < dataTable[i].size(); j++)
            outputStream << dataTable[i][j] << (j < dataTable[i].size()-1? ',' : '\n');
    }

    outputFile.close();
}

void TableModel::deleteOne(const QList<QString> &item)
{
    if (item[0].isNull())
        return;
    beginResetModel();
    QList<QList<QString>>::iterator it = dataTable.begin();
    for (; it != dataTable.end(); it++)
    {
        if (*it == item)
        {
            dataTable.erase(it);
            break;
        }
    }
    endResetModel();
    Vhead.pop_back();
    emit layoutChanged();
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return dataTable.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return header.size();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        try
        {
            if(index.column() > 4)
                return dataTable[index.row()][index.column()].toInt(); // сортировка баллов по числу, а не в алфавитном порядке
            return QVariant(dataTable[index.row()][index.column()]);
        }
        catch (...)
        {
            return QVariant();
        }
    }
    return QVariant();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role) // save changed data
{
    if (data(index, role) != value)
    {
        dataTable[index.row()][index.column()] = value.toString();
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const // нажать на ячейку, чтобы изменить
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            if(lang == "RUS")
                return headRus[section];
            else if(lang == "ENG")
                return header[section];
        }
        else if (orientation == Qt::Vertical)
            return Vhead[section];
    }
    return QVariant();
}

QList<QString> TableModel::getRow(int i) const
{
    return dataTable.at(i);
}

void TableModel::appendRow(const QList <QString> &data)
{
    beginResetModel();
    dataTable.push_back(data);
    Vhead.push_back(QString::number(Vhead.at(Vhead.size() - 1).toInt() + 1));
    endResetModel();
    emit layoutChanged();
}

QPair<int,int> TableModel::getSize()
{
    return {header.size(), dataTable.size()};
}

void TableModel::changeLan(const QString &lang)
{
    this->lang = lang;
    emit layoutChanged();
}



