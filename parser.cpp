#include "parser.h"
#include "QtXml"

XmlStreamReader::XmlStreamReader()
{
}

bool XmlStreamReader::readFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)){
        return false;
    }

    reader.setDevice(&file);

    reader.readNext();
    while (!reader.atEnd()){
        if(reader.isStartElement())
        {
            if (reader.name()=="table")
            {
                readTableElement();
            } else{
                reader.raiseError(QObject::tr("Not a table file"));
            }
        } else {
            reader.readNext();
        }
    }

    file.close();
    return true;
}

void XmlStreamReader::readTableElement()
{
    reader.readNext();
    while (!reader.atEnd()) {
        if (reader.isEndElement()) {
            reader.readNext();
            break;
        }

        if (reader.isStartElement()) {
            if (reader.name() == "row") {
                row = new Row;
                readRowElement(row);
            }else {
                skipUnknownElement();
            }
        } else {
            reader.readNext();
        }
    }
}

void XmlStreamReader::readRowElement(Row *item)
{
    reader.readNext();
    while (!reader.atEnd()){
        if (reader.isEndElement()){
            reader.readNext();
            break;
        }
    }

    if (reader.isStartDocument()) {
        if (reader.name() == "field"){
            readFieldElement(item);
        }else {
            skipUnknownElement();
        }
    } else {
        reader.readNext();
    }
}

void XmlStreamReader::readFieldElement(Row *item)
{
    reader.readNext();
    while (!reader.atEnd()){
        if (reader.isEndElement()){
            reader.readNext();
            break;
        }
    }

    if (reader.isStartDocument()) {
        if (reader.name() == "type")
        {
            readTypeElement(item);
        }
        else if (reader.name()=="name")
        {
            readNameElement(item);
        }
        else if (reader.name()=="value")
        {
            readValueElement(item);
        }else {
            skipUnknownElement();
        }

    } else {
        reader.readNext();
    }
}

void XmlStreamReader::readTypeElement(Row *item)
{
    QString type = reader.readElementText();
    if (reader.isEndElement())
        reader.readNext();
}

void XmlStreamReader::readNameElement(Row *item)
{
    QString name = reader.readElementText();
    if (reader.isEndElement())
        reader.readNext();
}

void XmlStreamReader::readValueElement(Row *item)
{
    QString value = reader.readElementText();
    if (reader.isEndElement())
        reader.readNext();
}

void XmlStreamReader::skipUnknownElement()
{
    reader.readNext();
    while (!reader.atEnd()) {
        if (reader.isEndElement()) {
            reader.readNext();
            break;
        }

        if (reader.isStartElement()) {
            skipUnknownElement();
        } else {
            reader.readNext();
        }
    }
}
