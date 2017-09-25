#include "global.h"
#include "proxymodel.h"

ProxyModel::ProxyModel(QObject *parent): QSortFilterProxyModel(parent)
{
    m_maxMoneyFather=m_maxMoneyMother=m_minMoneyFather=m_minMoneyMother=m_numberBrothers=m_numberSisters=InvalidCode;
}


void ProxyModel::clearFilters()
{
    m_maxMoneyFather=m_maxMoneyMother=m_minMoneyFather=m_minMoneyMother=m_numberBrothers=m_numberSisters=InvalidCode;
    m_student.clear();
    m_father.clear();
    m_mother.clear();
    invalidateFilter();
}


bool ProxyModel::filterAcceptsRow(int sourceRow,
        const QModelIndex &sourceParent) const
{
    if (!m_student.isEmpty()) {
        QModelIndex index = sourceModel()->index(sourceRow, Student,
                                                 sourceParent);
        if (m_student != sourceModel()->data(index).toString())
            return false;
    }

    if (!m_father.isEmpty()) {
        QModelIndex index = sourceModel()->index(sourceRow,Father,
                                                 sourceParent);
        if (m_father != sourceModel()->data(index).toString())
            return false;
    }

    if (m_minMoneyFather != InvalidCode ||
        m_maxMoneyFather != InvalidCode) {
        QModelIndex index = sourceModel()->index(sourceRow, MoneyFather,
                                                 sourceParent);
        if (m_minMoneyFather != InvalidCode &&
            sourceModel()->data(index).toInt() < m_minMoneyFather)
            return false;
        if (m_maxMoneyFather != InvalidCode &&
            sourceModel()->data(index).toInt() > m_maxMoneyFather)
            return false;
    }

    if (!m_mother.isEmpty()) {
        QModelIndex index = sourceModel()->index(sourceRow,Mother,
                                                 sourceParent);
        if (m_mother != sourceModel()->data(index).toString())
            return false;
    }

    if (m_minMoneyMother != InvalidCode ||
        m_maxMoneyMother != InvalidCode) {
        QModelIndex index = sourceModel()->index(sourceRow, MoneyMother,
                                                 sourceParent);
        if (m_minMoneyMother != InvalidCode &&
            sourceModel()->data(index).toInt() < m_minMoneyMother)
            return false;
        if (m_maxMoneyMother != InvalidCode &&
            sourceModel()->data(index).toInt() > m_maxMoneyMother)
            return false;
    }


    if (m_numberBrothers!=InvalidCode) {
        QModelIndex index = sourceModel()->index(sourceRow, NumberBrothers,
                                                 sourceParent);
        if (m_numberBrothers != sourceModel()->data(index).toString())
            return false;
    }

    if (m_numberSisters!=InvalidCode) {
        QModelIndex index = sourceModel()->index(sourceRow, NumberSisters,
                                                 sourceParent);
        if (m_numberSisters != sourceModel()->data(index).toString())
            return false;
    }
    return true;
}

void ProxyModel::setStudent(const QString &student)
{
    if (m_student != student) {
        m_student = student;
        invalidateFilter();
    }
}

void ProxyModel::setFather(const QString &father)
{
    if (m_father != father) {
        m_father = father;
        invalidateFilter();
    }
}

void ProxyModel::setMinMoneyFather(int minMoneyFather)
{
    if (m_minMoneyFather != minMoneyFather) {
       m_minMoneyFather = minMoneyFather;
        invalidateFilter();
    }
}

void ProxyModel::setMaxMoneyFather(int maxMoneyFather)
{
    if (m_maxMoneyFather != maxMoneyFather) {
       m_maxMoneyFather = maxMoneyFather;
        invalidateFilter();
    }
}

void ProxyModel::setMother(const QString &mother)
{
    if (m_mother != mother) {
        m_mother = mother;
        invalidateFilter();
    }
}

void ProxyModel::setMinMoneyMother(int minMoneyMother)
{
    if (m_minMoneyMother != minMoneyMother) {
       m_minMoneyMother = minMoneyMother;
        invalidateFilter();
    }
}

void ProxyModel::setMaxMoneyMother(int maxMoneyMother)
{
    if (m_maxMoneyMother != maxMoneyMother) {
       m_maxMoneyMother = maxMoneyMother;
        invalidateFilter();
    }
}

void ProxyModel::setNumberBrothers(int numberBrothers)
{
    if (m_numberBrothers != numberBrothers) {
        m_numberBrothers = numberBrothers;
        invalidateFilter();
    }
}

void ProxyModel::setNumberSisters(int numberSisters)
{
    if (m_numberSisters != numberSisters) {
        m_numberSisters = numberSisters;
        invalidateFilter();
    }
}
