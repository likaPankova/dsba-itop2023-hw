#ifndef PROXYMODEL_H
#define PROXYMODEL_H
#include <QSortFilterProxyModel>

class ProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    ProxyModel(QObject* parent = 0);
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
    void setCategory(const QString& category);
    void setScore(const int score);

private:
    QString category;
    int score;
    std::map<QString, QString> translate;
    //const MainWindow ;
};

//class FilterModel : public QSortFilterProxyModel
//{
//    Q_OBJECT
//public:
//    FilterModel(QObject* parent, const QWidget* main_window);
//    bool compare(const QString& s, const QString& g) const;
//    bool lessThan(const QModelIndex& source_left, const QModelIndex& source_right) const override;
////protected:
////    virtual bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const override;
//private:
//    const QWidget* main_window = nullptr;
//};

#endif // PROXYMODEL_H
