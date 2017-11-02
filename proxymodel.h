#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include <QSortFilterProxyModel>

class ProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit ProxyModel(QObject *parent=0);

    QString numberBrothers() const {return m_numberBrothers;}
    QString numberSisters() const {return m_numberSisters;}
    QString minMoneyFather() const {return m_minMoneyFather;}
    QString maxMoneyFather() const {return m_maxMoneyFather;}
    QString minMoneyMother() const {return m_minMoneyMother;}
    QString maxMoneyMother() const {return m_maxMoneyMother;}
    QString student() const { return m_student; }
    QString father() const { return m_father; }
    QString mother() const { return m_mother; }

public slots:
    void clearFilters();

    void setNumberBrothers(const QString &numberBrothers);
    void setNumberSisters(const QString &numberSisters);
    void setMinMoneyFather(const QString &minMoneyFather);
    void setMaxMoneyFather(const QString &maxMoneyFather);
    void setMinMoneyMother(const QString &minMoneyMother);
    void setMaxMoneyMother(const QString &maxMoneyMother);
    void setStudent(const QString &student);
    void setFather(const QString &father);
    void setMother(const QString &mother);

protected:
    bool filterAcceptsRow(int sourceRow,
                          const QModelIndex &sourceParent) const;

private:
    QString m_numberBrothers;
    QString m_numberSisters;
    QString m_minMoneyFather;
    QString m_maxMoneyFather;
    QString m_minMoneyMother;
    QString m_maxMoneyMother;
    QString m_student;
    QString m_father;
    QString m_mother;
};

#endif // PROXYMODEL_H
