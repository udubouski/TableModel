#ifndef DELETEDIALOG_H
#define DELETEDIALOG_H

#include <QDialog>
#include "tablemodel.h"
#include "proxymodel.h"

class QComboBox;
class QSpinBox;
class QPushButton;
class QLabel;
class QGroupBox;
class QTableView;

class DeleteDialog : public QDialog
{
    Q_OBJECT

public:
    DeleteDialog (TableModel *model,QWidget *parent=0);

signals:
    void sendSignal(bool ch);

private slots:
    void onButtonSend();
    void updateUi();
    void setDirty() { setWindowModified(true); }
    void delRecord();

private:
    bool okToDelete(QWidget *parent, const QString &title,const QString &text, const QString &detailedText=QString());
    void createWidget();
    void createConnections();
    void createComboBoxModels();
    void createComboBoxModel(QComboBox* comboBox,int column);
    void restoreFilters();
    void restoreFilters2();
    void restoreFilters3();
    void restoreFilters4();

    TableModel *model;
    ProxyModel *proxyModel;

    QTableView *resultTable;

    QGroupBox *box1;
    QGroupBox *box2;
    QGroupBox *box3;
    QGroupBox *box4;

    QLabel *labelStudent;
    QLabel *labelFather;
    QLabel *labelMother;
    QLabel *labelFatherFrom;
    QLabel *labelFatherTo;
    QLabel *labelMotherFrom;
    QLabel *labelMotherTo;
    QLabel *labelNumberBrother;
    QLabel *labelNumberSister;

    QComboBox *lineStudent;
    QComboBox *lineFather;
    QSpinBox *lineMoneyFatherDown;
    QSpinBox *lineMoneyFatherUp;
    QComboBox *lineMother;
    QSpinBox *lineMoneyMotherDown;
    QSpinBox *lineMoneyMotherUp;
    QComboBox *lineNumberBrother;
    QComboBox *lineNumberSister;

    QPushButton *butDelete;
    QPushButton *butCancel;
};

#endif // DELETEDIALOG_H
