#include "global.h"
#include "tablemodel.h"
#include <QApplication>
#include <QDataStream>
#include <QFile>
#include <QFontMetrics>
#include <QStyleOptionComboBox>
#include <QtXml>
#include "parser.h"
#include "record.h"
#include <QMessageBox>

namespace {
const qint32 MagicNumber = 0x5A697043;
const qint16 FormatNumber = 100;
const int MaxColumns =7;
}

/*QDataStream &operator<<(QDataStream &out, const PersonItem &item)
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
}*/


Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags theFlags = QAbstractTableModel::flags(index);
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


int TableModel::countField()
{
    Table tablet = reader.getTable();
    int num =tablet.rows[0].fields.count();
    return num;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
            switch (section) {
                case 0: return tr("Student");
                case 1: return tr("Father");
                case 2: return tr("Money father");
                case 3: return tr("Mother");
                case 4: return tr("Money mother");
                case 5: return tr("Brothers");
                case 6: return tr("Sisters");
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


bool TableModel::readFile(const QString &filename)
{
    reader.readFile(filename);
    QString st=filename;
    QMessageBox box;
    box.setText(st);
    box.exec();
    return true;
}

void TableModel::clear()
{
    removeRows(0,rowCount());
}
/*
bool TableModel::writeFile(const QString &filename)
{
    QDomDocument doc("table10");
    QDomElement  domElement = doc.createElement("table");
    doc.appendChild(domElement);

    for (int i =0;i<rowCount();++i)
    {
        QStringList list;
        QModelIndex indexe;
        for (int j = 0;j<MaxColumns;++j)
        {
            indexe = index(i,j,QModelIndex());
            list<<data(indexe,Qt::DisplayRole).toString();
        }
        QDomElement contact=record(doc,list[0],list[1],list[2],list[3],list[4],list[5],list[6]);
        domElement.appendChild(contact);
    }

    QFile file(filename);
    if(file. open (QIODevice::WriteOnly)) {
        QTextStream(&file)<< doc.toString ();
        file.close ();
    }
}

QDomElement TableModel::makeElement(QDomDocument& domDoc,const QString& strName,const QString& strAttr,const QString& strText )
{
    QDomElement domElement = domDoc.createElement(strName);

    if (!strAttr.isEmpty()) {
        QDomAttr domAttr = domDoc.createAttribute("number");
        domAttr.setValue(strAttr);
        domElement.setAttributeNode(domAttr);
    }

    if (!strText.isEmpty()) {
        QDomText domText = domDoc.createTextNode(strText);
        domElement.appendChild(domText);
    }
    return domElement;
}

QDomElement TableModel::record(QDomDocument& domDoc,const QString& strStudent,const QString& strFather,const QString& strMoneyFather,
const QString& strMother,const QString& strMoneyMother,const QString& strNumberBrothers,const QString& strNumberSisters)
{
    static int nNumber = 1;
    QDomElement domElement = makeElement(domDoc, "row", QString().setNum(nNumber),"");

    domElement.appendChild(makeElement(domDoc, "student", "", strStudent));
    domElement.appendChild(makeElement(domDoc, "father", "", strFather));
    domElement.appendChild(makeElement(domDoc, "moneyFather", "", strMoneyFather));
    domElement.appendChild(makeElement(domDoc, "mother", "", strMother));
    domElement.appendChild(makeElement(domDoc, "moneyMother", "", strMoneyMother));
    domElement.appendChild(makeElement(domDoc, "numberBrothers", "", strNumberBrothers));
    domElement.appendChild(makeElement(domDoc, "numberSisters", "", strNumberSisters));

    nNumber++;

    return domElement;
}
*/




