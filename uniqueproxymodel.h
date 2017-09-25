#ifndef UNIQUEPROXYMODEL_H
#define UNIQUEPROXYMODEL_H

#include <QSet>
#include <QSortFilterProxyModel>

class UniqueProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    UniqueProxyModel(int column, QObject *parent=0) : QSortFilterProxyModel(parent), Column(column) {}

    void setSourceModel(QAbstractTableModel *sourceModel);

protected:
    bool filterAcceptsRow(int sourceRow,
                          const QModelIndex &sourceParent) const;

private slots:
    void clearCache() { cache.clear(); }

private:
    const int Column;
    mutable QSet<QString> cache;
};

#endif // UNIQUEPROXYMODEL_H
