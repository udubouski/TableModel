#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QStandardItemModel>

class TableModel : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit TableModel(QObject *parent=0);

    QString filename() const { return m_filename; }
    void clear();
    void load(const QString &filename="");
    void save(const QString &filename="");

private:
    void initialize();

    QString m_filename;
};


#endif // TABLEMODEL_H

