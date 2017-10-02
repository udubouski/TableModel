#ifndef PARSER_H
#define PARSER_H

#include <QXmlStreamReader>

class XmlStreamReader
{
public:
    XmlStreamReader();

    bool readFile(const QString &fileName);

private:
    void readRowElement();
    void readFieldElement();
    void readTypeNameValue();
    void readPageElement();
    void skipUnknownElement();

    QXmlStreamReader reader;
};


#endif // PARSER_H
