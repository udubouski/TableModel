/*#include "tablemodel.h"


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
        return tr( "Student" );
    case FIOFATHER:
        return tr( "Father" );
    case MONEYFATHER:
        return tr( "Money father" );
    case FIOMOTHER:
        return tr( "Mother" );
    case MONEYMOTHER:
        return tr( "Money mother" );
    case NUMBERBROTHER:
        return tr( "Number brothers" );
    case NUMBERSISTER:
        return tr( "Number sisters" );
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

*/

//#include "aqp.hpp"
#include "global.h"
#include "tablemodel.h"
#include <QApplication>
#include <QDataStream>
#include <QFile>
#include <QFontMetrics>
#include <QStyleOptionComboBox>


namespace {
const qint32 MagicNumber = 0x5A697043;
const qint16 FormatNumber = 100;
const int MaxColumns = 7;
}


QDataStream &operator<<(QDataStream &out, const PersonItem &item)
{
    out<< item.student<<item.father<<static_cast<quint16>(item.moneyFather)
       <<item.mother<<static_cast<quint16>(item.moneyMother)
      <<static_cast<quint16>(item.numberBrothers)<<static_cast<quint16>(item.numberSisters);
    return out;
}


QDataStream &operator>>(QDataStream &in, PersonItem &item)
{
    quint16 moneyFather, moneyMother, numberBrothers, numberSisters;
    in >> item.student >> item.father >> moneyFather >> item.mother>>moneyMother>>numberBrothers>>numberSisters;
    item.moneyFather = static_cast<int>(moneyFather);
    item.moneyMother = static_cast<int>(moneyMother);
    item.numberBrothers = static_cast<int>(numberBrothers);
    item.numberSisters = static_cast<int>(numberSisters);
    return in;
}


Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags theFlags = QAbstractTableModel::flags(index);
    /*if (index.isValid())
        theFlags |= Qt::ItemIsSelectable|Qt::ItemIsEditable|
                    Qt::ItemIsEnabled;*/
    return theFlags;
}


QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() ||
        index.row() < 0 || index.row() >= persons.count() ||
        index.column() < 0 || index.column() >= MaxColumns)
        return QVariant();
    const PersonItem &item = persons.at(index.row());
    if (role == Qt::SizeHintRole) {
        QStyleOptionComboBox option;
        switch (index.column()) {
            case Student: option.currentText = item.student; break;

            case Father: option.currentText = item.student; break;

            case MoneyFather: {
                option.currentText = QString::number(MaxCode);
                const QString header = headerData(MoneyFather,
                        Qt::Horizontal, Qt::DisplayRole).toString();
                if (header.length() > option.currentText.length())
                    option.currentText = header;
                break;
            }

            case Mother: option.currentText = item.student; break;

            case MoneyMother: {
            option.currentText = QString::number(MaxCode);
            const QString header = headerData(MoneyMother,
                    Qt::Horizontal, Qt::DisplayRole).toString();
            if (header.length() > option.currentText.length())
                option.currentText = header;
            break;
            }

            case NumberBrothers: {
                option.currentText = QString::number(MaxCode);
                const QString header = headerData(NumberBrothers,
                        Qt::Horizontal, Qt::DisplayRole).toString();
                if (header.length() > option.currentText.length())
                    option.currentText = header;
                break;
            }

            case NumberSisters: {
            option.currentText = QString::number(MaxCode);
            const QString header = headerData(NumberSisters,
                  Qt::Horizontal, Qt::DisplayRole).toString();
            if (header.length() > option.currentText.length())
                option.currentText = header;
            break;
             }

            default: Q_ASSERT(false);
        }
        QFontMetrics fontMetrics(data(index, Qt::FontRole)
                                 .value<QFont>());
        option.fontMetrics = fontMetrics;
        QSize size(fontMetrics.width(option.currentText),
                   fontMetrics.height());
        return qApp->style()->sizeFromContents(QStyle::CT_ComboBox,
                                               &option, size);
    }
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
            case Student: return item.student;
            case Father: return item.father;
            case MoneyFather: return item.moneyFather;
            case Mother: return item.mother;
            case MoneyMother: return item.moneyMother;
            case NumberBrothers: return item.numberBrothers;
            case NumberSisters: return item.numberSisters;
            default: Q_ASSERT(false);
        }
    }
    return QVariant();
}


QVariant TableModel::headerData(int section,
        Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal) {
        switch (section) {
            case Student: return tr("Student");
            case Father: return tr("Father");
            case MoneyFather: return tr("Money father");
            case Mother: return tr("Mother");
            case MoneyMother: return tr("Money mother");
            case NumberBrothers: return tr("Brothers");
            case NumberSisters: return tr("Sisters");
            default: Q_ASSERT(false);
        }
    }
    return section + 1;
}


int TableModel::rowCount(const QModelIndex &index) const
{
    return index.isValid() ? 0 : persons.count();
}


int TableModel::columnCount(const QModelIndex &index) const
{
    return index.isValid() ? 0 : MaxColumns;
}


bool TableModel::setData(const QModelIndex &index,
                         const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::EditRole ||
        index.row() < 0 || index.row() >= persons.count() ||
        index.column() < 0 || index.column() >= MaxColumns)
        return false;
    PersonItem &item = persons[index.row()];
    switch (index.column()) {
        case Student: item.student = value.toString(); break;
        case Father: item.father = value.toString(); break;
        case MoneyFather: {
            bool ok;
            int moneyfather = value.toInt(&ok);
            if (!ok || moneyfather < MinCode || moneyfather > MaxCode)
                return false;
            item.moneyFather = moneyfather;
            break;
        }
        case Mother: item.mother = value.toString(); break;
        case MoneyMother: {
            bool ok;
            int moneymother = value.toInt(&ok);
            if (!ok || moneymother < MinCode || moneymother > MaxCode)
                return false;
            item.moneyMother = moneymother;
            break;
        }
        case NumberBrothers: {
            bool ok;
            int numberbrothers = value.toInt(&ok);
            if (!ok || numberbrothers < MinCode || numberbrothers > MaxCode)
                return false;
            item.numberBrothers = numberbrothers;
            break;
        }
        case NumberSisters: {
            bool ok;
            int numbersisters = value.toInt(&ok);
            if (!ok || numbersisters < MinCode || numbersisters > MaxCode)
                return false;
            item.numberSisters = numbersisters;
            break;
        }
        default: Q_ASSERT(false);
    }
    emit dataChanged(index, index);
    return true;
}


bool TableModel::insertRows(int row, int count, const QModelIndex&)
{
    beginInsertRows(QModelIndex(), row, row + count - 1);
    for (int i = 0; i < count; ++i)
        persons.insert(row, PersonItem());
    endInsertRows();
    return true;
}


bool TableModel::removeRows(int row, int count, const QModelIndex&)
{
    beginRemoveRows(QModelIndex(), row, row + count - 1);
    for (int i = 0; i < count; ++i)
        persons.removeAt(row);
    endRemoveRows();
    return true;
}


void TableModel::load(const QString &filename)
{
    if (!filename.isEmpty())
        m_filename = filename;
    if (m_filename.isEmpty())
    {}
        //throw AQP::Error(tr("no filename specified"));
    QFile file(m_filename);
    if (!file.open(QIODevice::ReadOnly)) {}
      //  throw AQP::Error(file.errorString());

    QDataStream in(&file);
    qint32 magicNumber;
    in >> magicNumber;
    if (magicNumber != MagicNumber)
            {}
       // throw AQP::Error(tr("unrecognized file type"));

    qint16 formatVersionNumber;
    in >> formatVersionNumber;
    if (formatVersionNumber > FormatNumber)
     //   throw AQP::Error(tr("file format version is too new"));
    {}
    in.setVersion(QDataStream::Qt_4_5);
    persons.clear();

    PersonItem item;
    while (!in.atEnd()) {
        in >> item;
        persons << item;
    }
    qSort(persons);
    reset();
}


void TableModel::save(const QString &filename)
{
    if (!filename.isEmpty())
        m_filename = filename;
    if (m_filename.isEmpty())
    {}
       // throw AQP::Error(tr("no filename specified"));
    QFile file(m_filename);
    if (!file.open(QIODevice::WriteOnly))
    {}
        //throw AQP::Error(file.errorString());

    QDataStream out(&file);
    out << MagicNumber << FormatNumber;
    out.setVersion(QDataStream::Qt_4_5);
    QListIterator<PersonItem> i(persons);
    while (i.hasNext())
        out << i.next();
}

