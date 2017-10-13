#include "parser.h"
#include "QtXml"
#include <QMessageBox>

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
                readTableElement(table);

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

void XmlStreamReader::readTableElement(Table &table)
{
    reader.readNext();
    while (!reader.atEnd()) {
        if (reader.isEndElement()) {
            reader.readNext();
            break;
        }

        if (reader.isStartElement()) {
            if (reader.name() == "row") {

                Row row;
                readRowElement(row);
                table.rows.append(row);


            }else {
                skipUnknownElement();
            }
        } else {
            reader.readNext();
        }
    }
}

void XmlStreamReader::readRowElement(Row &row)
{
    reader.readNext();
    while (!reader.atEnd()) {
        if (reader.isEndElement()) {
            reader.readNext();
            break;
        }

        if (reader.isStartElement()) {
            if (reader.name() == "field") {
                Field field;
                readFieldElement(field);
                row.fields.append(field);

            }else {
                skipUnknownElement();
            }
        } else {
            reader.readNext();
        }
    }
}

void XmlStreamReader::readFieldElement(Field &field)
{
    reader.readNext();
    while (!reader.atEnd()) {
        if (reader.isEndElement()) {
            reader.readNext();
            break;
        }

    if (reader.isStartElement()) {
        if (reader.name() == "type") {
            field.type = readTypeElement();
        }
        else if (reader.name()=="name")
        {
            field.name=readNameElement();
        }
        else if (reader.name()=="value")
        {
            field.value=readValueElement();
        }else {
            skipUnknownElement();
        }

    } else {
        reader.readNext();
    }
    }
}

QString XmlStreamReader::readTypeElement()
{
    QString type = reader.readElementText();
    if (reader.isEndElement())
        reader.readNext();

    return type;
}

QString XmlStreamReader::readNameElement()
{
    QString name = reader.readElementText();
    if (reader.isEndElement())
        reader.readNext();

    return name;
}

QString XmlStreamReader::readValueElement()
{
    QString value = reader.readElementText();
    if (reader.isEndElement())
        reader.readNext();

    return value;
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
