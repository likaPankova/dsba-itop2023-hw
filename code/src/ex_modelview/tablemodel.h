#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#include <QAbstractTableModel>
#include <QSet>


class TableModel: public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit TableModel(QObject *parent = nullptr);
    ~TableModel();

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    //bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    QList<QString> getRow(int i) const;

    void appendRow(const QList <QString> &data);

    void changeLan(const QString &lang);

    QPair<int,int> getSize();

public :
    QSet<QString> races;
    QList<int> finalResults;
    void openData(const QString &dir);
    void saveData(const QString &dir);
    void deleteOne(const QList<QString> &item);


private:
    QList<QList<QString>> dataTable;
    QList<QString> header;
    QList<QString> Vhead;
    QList<QString> headRus;
    QString dir;
    QString lang;
};

#endif // TABLEMODEL_H
