#ifndef PARSER_H
#define PARSER_H

#include <QXmlStreamReader>
#include "record.h"

class XmlStreamReader
{
public:
    XmlStreamReader();

    bool readFile(const QString &fileName);

private:
    void readTableElement();
    void readRowElement(Row *item);
    void readFieldElement(Row *item);
    void readTypeElement(Row *item);
    void readNameElement(Row *item);
    void readValueElement(Row *item);
    void skipUnknownElement();

    QXmlStreamReader reader;
    Row row;

};


#endif // PARSER_H
