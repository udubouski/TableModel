#ifndef TABLEMODEL_H
#define TABLEMODEL_H

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

#endif // TABLEMODEL_H

