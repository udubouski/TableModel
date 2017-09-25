#ifndef PERSONITEMS_H
#define PERSONITEMS_H

#include "global.h"
#include <QString>

struct PersonItem
{
   explicit PersonItem(const QString &student_ = QString(),
            const QString &father_= QString(),
            int moneyFather_ = InvalidCode,
            const QString &mother_= QString(),
            int moneyMother_ = InvalidCode,
            int numberBrothers_ = InvalidCode,
            int numberSisters_ = InvalidCode )
        : student(student_), father(father_), moneyFather(moneyFather_),
          mother(mother_),moneyMother(moneyMother_),
          numberBrothers(numberBrothers_),numberSisters(numberSisters_) {}

    bool operator<(const PersonItem &other) const
        { return student != other.student ? student < other.student
                                    : father < other.father; }

    QString student;
    QString father;
    int moneyFather;
    QString mother;
    int moneyMother;
    int numberBrothers;
    int numberSisters;
};


#endif // PERSONITEMS_H
