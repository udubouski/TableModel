#ifndef RECORD_H
#define RECORD_H

#include <QList>
#include <QString>
#include <QList>

struct Field
{
    QString type;
    QString name;
    QString value;
};


class Row
{
public:
    QList<Field> fields;
    Row() {}
};

class Table
{
public:
    QList<Row> rows;
    Table() {}
};
#endif // RECORD_H
