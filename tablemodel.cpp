
#include "tablemodel.h"
#include "global.h"
#include <QDataStream>
#include <QFile>

namespace {
const qint32 MagicNumber = 0x5A697043;
const qint16 FormatNumber = 100;
}

TableModel::TableModel(QObject *parent)
    : QStandardItemModel(parent)
{
    initialize();
}


void TableModel::initialize()
{
    setHorizontalHeaderLabels(QStringList() << tr("Zipcode") << tr("Student") << tr("Father") << tr("Money Father")
                              << tr("Mother") << tr("Money Mother") << tr("Number Brother") << tr("Number Sister"));
}

void TableModel::clear()
{
    QStandardItemModel::clear();
    initialize();
}


void TableModel::load(const QString &filename)
{
    if (!filename.isEmpty())
        m_filename = filename;
  //  if (m_filename.isEmpty())
  //      throw AQP::Error(tr("no filename specified"));
    QFile file(m_filename);
  //  if (!file.open(QIODevice::ReadOnly))
  //      throw AQP::Error(file.errorString());

    QDataStream in(&file);
    qint32 magicNumber;
    in >> magicNumber;
 //   if (magicNumber != MagicNumber)
 //       throw AQP::Error(tr("unrecognized file type"));
    qint16 formatVersionNumber;
    in >> formatVersionNumber;
 //   if (formatVersionNumber > FormatNumber)
 //       throw AQP::Error(tr("file format version is too new"));
    in.setVersion(QDataStream::Qt_4_5);
    clear();

    quint16 zipcode;
    QString studentFIO;
    QString fatherFIO;
    quint16 moneyFather;
    QString motherFIO;
    quint16 moneyMother;
    quint16 numberBrother;
    quint16 numberSister;
    QMap<quint16, QList<QStandardItem*> > itemsForZipcode;

    while (!in.atEnd()) {
        in >> zipcode >> studentFIO >> fatherFIO >> moneyFather >> motherFIO >> moneyMother >> numberBrother >> numberSister;
        QList<QStandardItem*> items;
        QStandardItem *item = new QStandardItem;
        item->setData(zipcode, Qt::EditRole);
        items << item;
        foreach (const QString &text, QStringList() << studentFIO << fatherFIO << QString::number(moneyFather) << motherFIO << QString::number(moneyMother) << QString::number(numberBrother) << QString::number(numberSister))
            items << new QStandardItem(text);
        itemsForZipcode[zipcode] = items;
    }

    QMapIterator<quint16, QList<QStandardItem*> > i(itemsForZipcode);
    while (i.hasNext())
        appendRow(i.next().value());
}


void TableModel::save(const QString &filename)
{
    if (!filename.isEmpty())
        m_filename = filename;
   // if (m_filename.isEmpty())
  //      throw AQP::Error(tr("no filename specified"));
    QFile file(m_filename);
  //  if (!file.open(QIODevice::WriteOnly))
  //      throw AQP::Error(file.errorString());

    QDataStream out(&file);
    out << MagicNumber << FormatNumber;
    out.setVersion(QDataStream::Qt_4_5);
    for (int row = 0; row < rowCount(); ++row) {
        out << static_cast<quint16>(
                    item(row, Zipcode)->data(Qt::EditRole).toUInt())
            << item(row, StudentFIO)->text() << item(row, FatherFIO)->text() << item(row, MoneyFather)->text()
            << item(row, MotherFIO)->text() << item(row, MoneyMother)->text()
            << item(row, NumberBrother)->text() << item(row, NumberSister)->text();
    }
}

