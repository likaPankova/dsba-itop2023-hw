#include "proxymodel.h"

ProxyModel::ProxyModel(QObject* parent) : QSortFilterProxyModel(parent), category("All groups"), score(300)
{
    translate.insert({"группа A","group A"});
    translate.insert({"группа B","group B"});
    translate.insert({"группа C","group C"});
    translate.insert({"группа D","group D"});
    translate.insert({"группа E","group E"});
}
QVariant ProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return sourceModel()->headerData(section, orientation, role);

}
bool ProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex categoryIndex= sourceModel()->index(source_row, 1, source_parent);
    QModelIndex scoreIndex = sourceModel()->index(source_row, 8, source_parent);

    if((sourceModel()->data(categoryIndex).toString() == category || category == "All groups" || category == "Все группы") && score >= sourceModel()->data(scoreIndex).toInt())
        return true;
    return false;
}

void ProxyModel::setScore(const int score) // из слайдера значение
{
    this->score = score;
    invalidateFilter();
}

void ProxyModel::setCategory(const QString& category)
{
    if(translate.count(category))
        this->category = translate[category];
    else
        this->category = category;
    invalidateFilter();
}
