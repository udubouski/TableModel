#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include "personitems.h"
#include "parser.h"
#include "record.h"
#include <QAbstractTableModel>
#include <QtXml>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit TableModel(QObject *parent=0) : QAbstractTableModel(parent) {}

    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation,int role=Qt::DisplayRole) const;

    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    int columnCount(const QModelIndex &parent=QModelIndex()) const;

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role=Qt::EditRole);
    bool setHeaderData(int, Qt::Orientation, const QVariant&,
                       int=Qt::EditRole) { return false; }

    bool insertRows(int row, int count,
                    const QModelIndex &parent=QModelIndex());
    bool removeRows(int row, int count,
                    const QModelIndex &parent=QModelIndex());

    QString filename() const { return m_filename; }
    bool readFile(const QString &filename);
    bool writeFile(const QString &filename);

    void clear();

    QDomElement makeElement(QDomDocument& domDoc, const QString& strName, const QString& strAttr,const QString& strText );

    QDomElement record(QDomDocument& domDoc,
                        const QString&      strStudent,
                        const QString&      strFather,
                        const QString&      strMoneyFather,
                        const QString&      strMother,
                        const QString&      strMoneyMother,
                        const QString&      strNumberBrothers,
                        const QString&      strNumberSisters);
private:
    XmlStreamReader reader;
    QString m_filename;
    QList<PersonItem> persons;
};
#endif // TABLEMODEL_H

