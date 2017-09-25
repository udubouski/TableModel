#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include <QSortFilterProxyModel>

class ProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit ProxyModel(QObject *parent=0);

    int numberBrothers() const {return m_numberBrothers;}
    int numberSisters() const {return m_numberSisters;}
    int minMoneyFather() const {return m_minMoneyFather;}
    int maxMoneyFather() const {return m_maxMoneyFather;}
    int minMoneyMother() const {return m_minMoneyMother;}
    int maxMoneyMother() const {return m_maxMoneyMother;}
    QString student() const { return m_student; }
    QString father() const { return m_father; }
    QString mother() const { return m_mother; }

public slots:
    void clearFilters();

    void setNumberBrothers(int numberBrothers);
    void setNumberSisters(int numberSisters);
    void setMinMoneyFather(int minMoneyFather);
    void setMaxMoneyFather(int maxMoneyFather);
    void setMinMoneyMother(int minMoneyMother);
    void setMaxMoneyMother(int maxMoneyMother);
    void setStudent(const QString &student);
    void setFather(const QString &father);
    void setMother(const QString &mother);

protected:
    bool filterAcceptsRow(int sourceRow,
                          const QModelIndex &sourceParent) const;

private:
    int m_numberBrothers;
    int m_numberSisters;
    int m_minMoneyFather;
    int m_maxMoneyFather;
    int m_minMoneyMother;
    int m_maxMoneyMother;
    QString m_student;
    QString m_father;
    QString m_mother;
};

#endif // PROXYMODEL_H
