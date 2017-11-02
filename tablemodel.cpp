#include "tablemodel.h"
#include <QApplication>
#include <QDataStream>
#include <QFile>
#include <QFontMetrics>
#include <QStyleOptionComboBox>
#include <QtXml>
#include "parser.h"
#include "record.h"

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags theFlags = QAbstractTableModel::flags(index);
    return theFlags;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() ||
        index.row() < 0 || index.row() >= reader.RowCount() ||
        index.column() < 0 || index.column() >= reader.ColumnCount())
        return QVariant();

    const Row &item = reader.getTable().rows.at(index.row());
    if (role == Qt::SizeHintRole) {
        QStyleOptionComboBox option;

        option.currentText = item.fields[index.column()].value;

        QFontMetrics fontMetrics(data(index, Qt::FontRole)
                                 .value<QFont>());
        option.fontMetrics = fontMetrics;
        QSize size(fontMetrics.width(option.currentText),
                   fontMetrics.height());
        return qApp->style()->sizeFromContents(QStyle::CT_ComboBox,
                                               &option, size);
    }
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        return item.fields[index.column()].value;
    }
    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal) {
        return reader.getTable().rows[0].fields[section].name;
    }
    return section + 1;
}

int TableModel::rowCount(const QModelIndex &index) const
{
    return index.isValid() ? 0 : reader.RowCount();
}

int TableModel::columnCount(const QModelIndex &index) const
{
    return index.isValid() ? 0 : reader.ColumnCount();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::EditRole ||
        index.row() < 0 || index.row() >= reader.RowCount() ||
        index.column() < 0 || index.column() >= reader.ColumnCount())
        return false;

    Row &item = reader.getTable().rows[index.row()];
   // switch (index.column()) {
       item.fields[index.column()].value = value.toString();
    //}
    emit dataChanged(index, index);
    return true;
}

bool TableModel::insertRows(int row, int count, const QModelIndex&)
{
    beginInsertRows(QModelIndex(), row, row + count - 1);
    for (int i = 0; i < count; ++i)
       rows.insert(row, Row());
    endInsertRows();
    return true;
}

bool TableModel::removeRows(int row, int count, const QModelIndex&)
{
    beginRemoveRows(QModelIndex(), row, row + count - 1);
    for (int i = 0; i < count; ++i)
        rows.removeAt(row);
    endRemoveRows();
    return true;
}

bool TableModel::readFile(const QString &filename)
{
    reader.readFile(filename);
    return true;
}


bool TableModel::writeFile(const QString &filename)
{/*
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
    }*/
    return true;
}
/*
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



