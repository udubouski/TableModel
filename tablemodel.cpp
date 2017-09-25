#include "tablemodel.h"

TableModel::TableModel( QObject* parent ) : QAbstractTableModel( parent ) {
}

int TableModel::rowCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return m_persons.count();
}

int TableModel::columnCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return LAST;
}

QVariant TableModel::data( const QModelIndex& index, int role ) const {
    if(
        !index.isValid() ||
        m_persons.count() <= index.row() ||
        ( role != Qt::DisplayRole && role != Qt::EditRole )
    ) {
        return QVariant();
    }

    return m_persons[ index.row() ][ Column( index.column() ) ];
}

bool TableModel::setData( const QModelIndex& index, const QVariant& value, int role ) {
    if( !index.isValid() || role != Qt::EditRole || m_persons.count() <= index.row() ) {
        return false;
    }

    m_persons[ index.row() ][ Column( index.column() ) ] = value;
    emit dataChanged( index, index );

    return true;
}


QVariant TableModel::headerData( int section, Qt::Orientation orientation, int role ) const {
    if( role != Qt::DisplayRole ) {
        return QVariant();
    }

    if( orientation == Qt::Vertical ) {
        return section;
    }

    switch( section ) {
    case FIOSTUDENT:
        return trUtf8( "Студент" );
    case FIOFATHER:
        return trUtf8( "Отец" );
    case MONEYFATHER:
        return trUtf8( "Заработок отца" );
    case FIOMOTHER:
        return trUtf8( "Мать" );
    case MONEYMOTHER:
        return trUtf8( "Заработок матери" );
    case NUMBERBROTHER:
        return trUtf8( "Количество братьев" );
    case NUMBERSISTER:
        return trUtf8( "Количество систер" );
    }

    return QVariant();
}

Qt::ItemFlags TableModel::flags( const QModelIndex& index ) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags( index );
    return flags;
}

void TableModel::appendPerson( const QString& fioStudent, const QString& fioFather, const QString& moneyFather,
                               const QString& fioMother, const QString& moneyMother,
                               const QString& numBrother, const QString& numSister ) {
    PersonData person;
    person[ FIOSTUDENT ] = fioStudent;
    person[ FIOFATHER] = fioFather;
    person[ MONEYFATHER ] = moneyFather;
    person[ FIOMOTHER] = fioMother;
    person[ MONEYMOTHER ] = moneyMother;
    person[ NUMBERBROTHER] = numBrother;
    person[ NUMBERSISTER ] = numSister;

    int row = m_persons.count();
    beginInsertRows( QModelIndex(), row, row );
    m_persons.append( person );
    endInsertRows();
}


