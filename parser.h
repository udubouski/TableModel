#ifndef PARSER_H
#define PARSER_H

#include <QXmlStreamReader>
#include <QString>
#include "record.h"

class XmlStreamReader
{
public:
    XmlStreamReader();

    bool readFile(const QString &fileName);
    Table getTable() {return tablet;}

private:
    void readTableElement(Table &table);
    void readRowElement(Row &row);
    void readFieldElement(Field &field);
    QString readTypeElement();
    QString readNameElement();
    QString readValueElement();
    void skipUnknownElement();

    QXmlStreamReader reader;
    Table tablet;
};


#endif // PARSER_H
