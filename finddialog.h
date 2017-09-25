#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include "tablemodel.h"
#include "proxymodel.h"

class QComboBox;
class QSpinBox;
class QPushButton;
class QLabel;
class QGroupBox;
class QTableView;

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    FindDialog(TableModel *model,QWidget *parent=0);

private slots:
    void updateUi();
    void boxClicked();

private:
    void createWidgets();
    void createConnections();
    void createComboBoxModels();
    void createComboBoxModel(QComboBox* comboBox,int column);
    void restoreFilters();

    TableModel *model;


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

    QPushButton *butFind;
    QPushButton *butCancel;
};

#endif // FINDDIALOG_H
