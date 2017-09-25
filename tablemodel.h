#ifndef TABLEMODEL_H
#define TABLEMODEL_H
/*
#include <QAbstractTableModel>

class TableModel : public QAbstractTableModel {

    //Q_OBJECT
public:
    TableModel ( QObject* parent = 0 );

    int rowCount( const QModelIndex& parent ) const;
    int columnCount( const QModelIndex& parent ) const;
    QVariant data( const QModelIndex& index, int role ) const;
    bool setData( const QModelIndex& index, const QVariant& value, int role );
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
    Qt::ItemFlags flags( const QModelIndex& index ) const;

    void appendPerson( const QString& fioStudent, const QString& fioFather, const QString& moneyFather,
                       const QString& fioMother, const QString& moneyMother,
                       const QString& numBrother, const QString& numSister);


private:
    enum Column {
        FIOSTUDENT = 0,
        FIOFATHER,
        MONEYFATHER,
        FIOMOTHER,
        MONEYMOTHER,
        NUMBERBROTHER,
        NUMBERSISTER,
        LAST
    };

    typedef QHash< Column, QVariant > PersonData;
    typedef QList< PersonData > Persons;
    Persons m_persons;

};
*/

#include "personitems.h"
#include <QAbstractTableModel>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TableModel(QObject *parent=0) : QAbstractTableModel(parent) {}

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
    void load(const QString &filename=QString());
    void save(const QString &filename=QString());

private:
    QString m_filename;
    QList<PersonItem> persons;
};
#endif // TABLEMODEL_H

