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
    Table getTable() const {return tablet;}
    int RowCount() const {return tablet.rows.count();}
    int ColumnCount() const {return tablet.rows[0].fields.count();}

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
