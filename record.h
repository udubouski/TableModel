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
    Field():type(0),name(0),value(0) {}
};


class Row
{
private:
    QList<Field> fields;
public:
    Row() {}
};



/*
class Rows
{
private:
    QList<Field> fields;

public:
    Rows () {}

    void setFieldList(QList<Field> fields) {this->fields=fields;}
    QList<Field> getFieldList() {return fields;}
};*/

#endif // RECORD_H
