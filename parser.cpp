#include "parser.h"
#include "QtXml"

XmlStreamReader::XmlStreamReader() {}

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
                readFieldElement();
            } else{
                reader.raiseError(QObject::tr("Not a table file"));
            }
        } else {
            reader.readNext();
        }
    }

    file.close();
}

void XmlStreamReader::readRowElement()
{
    reader.readNext();
    while (!reader.atEnd()){
        if (reader.isEndElement()){
            reader.readNext();
            break;
        }
    }

    if (reader.isStartDocument()) {
        if (reader.name() == "row"){
            readFieldElement();
        }
    } else {
        reader.readNext();
    }
}

void XmlStreamReader::readFieldElement()
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
            readTypeNameValue();
        }
    } else {
        reader.readNext();
    }
}

void XmlStreamReader::readTypeNameValue()
{
    reader.readNext();
    while (!reader.atEnd()){
        if (reader.isEndElement()){
            reader.readNext();
            break;
        }
    }

    if (reader.isStartDocument())
}
