#include "proxymodel.h"

ProxyModel::ProxyModel(QObject *parent): QSortFilterProxyModel(parent)
{
    //m_maxMoneyFather=m_maxMoneyMother=m_minMoneyFather=m_minMoneyMother=m_numberBrothers=m_numberSisters=0;
}


void ProxyModel::clearFilters()
{
    m_maxMoneyFather.clear();
    m_maxMoneyMother.clear();
    m_minMoneyFather.clear();
    m_minMoneyMother.clear();
    m_numberBrothers.clear();
    m_numberSisters.clear();
    m_student.clear();
    m_father.clear();
    m_mother.clear();
    invalidateFilter();
}


bool ProxyModel::filterAcceptsRow(int sourceRow,
        const QModelIndex &sourceParent) const
{
    if (!m_student.isEmpty()) {
        QModelIndex index = sourceModel()->index(sourceRow, 0,
                                                 sourceParent);
        if (m_student != sourceModel()->data(index).toString())
            return false;
    }

    if (!m_father.isEmpty()) {
        QModelIndex index = sourceModel()->index(sourceRow,1,
                                                 sourceParent);
        if (m_father != sourceModel()->data(index).toString())
            return false;
    }

    if (m_minMoneyFather != 0 ||
        m_maxMoneyFather != 0) {
        QModelIndex index = sourceModel()->index(sourceRow, 2,
                                                 sourceParent);
        if (m_minMoneyFather != 0 &&
            sourceModel()->data(index).toString() < m_minMoneyFather)
            return false;
        if (m_maxMoneyFather != 0 &&
            sourceModel()->data(index).toString() > m_maxMoneyFather)
            return false;
    }

    if (!m_mother.isEmpty()) {
        QModelIndex index = sourceModel()->index(sourceRow,3,
                                                 sourceParent);
        if (m_mother != sourceModel()->data(index).toString())
            return false;
    }

    if (m_minMoneyMother != 0 ||
        m_maxMoneyMother != 0) {
        QModelIndex index = sourceModel()->index(sourceRow, 4,
                                                 sourceParent);
        if (m_minMoneyMother != 0 &&
            sourceModel()->data(index).toString() < m_minMoneyMother)
            return false;
        if (m_maxMoneyMother != 0 &&
            sourceModel()->data(index).toString() > m_maxMoneyMother)
            return false;
    }


    if (m_numberBrothers!=0) {
        QModelIndex index = sourceModel()->index(sourceRow, 5,
                                                 sourceParent);
        if (m_numberBrothers != sourceModel()->data(index).toString())
            return false;
    }

    if (m_numberSisters!=0) {
        QModelIndex index = sourceModel()->index(sourceRow, 6,
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

void ProxyModel::setMinMoneyFather(const QString &minMoneyFather)
{
    if (m_minMoneyFather != minMoneyFather) {
       m_minMoneyFather = minMoneyFather;
        invalidateFilter();
    }
}

void ProxyModel::setMaxMoneyFather(const QString &maxMoneyFather)
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

void ProxyModel::setMinMoneyMother(const QString &minMoneyMother)
{
    if (m_minMoneyMother != minMoneyMother) {
       m_minMoneyMother = minMoneyMother;
        invalidateFilter();
    }
}

void ProxyModel::setMaxMoneyMother(const QString &maxMoneyMother)
{
    if (m_maxMoneyMother != maxMoneyMother) {
       m_maxMoneyMother = maxMoneyMother;
        invalidateFilter();
    }
}

void ProxyModel::setNumberBrothers(const QString &numberBrothers)
{
    if (m_numberBrothers != numberBrothers) {
        m_numberBrothers = numberBrothers;
        invalidateFilter();
    }
}

void ProxyModel::setNumberSisters(const QString &numberSisters)
{
    if (m_numberSisters != numberSisters) {
        m_numberSisters = numberSisters;
        invalidateFilter();
    }
}
