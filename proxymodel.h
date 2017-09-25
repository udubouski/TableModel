#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include <QSortFilterProxyModel>

class ProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit ProxyModel(QObject *parent=0);

};

#endif // PROXYMODEL_H
