#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>

class QLineEdit;
class QPushButton;
class QLabel;
class QRadioButton;

class FindDialog : public QDialog
{

public:
    FindDialog(QWidget *parent=0);

private:
    QRadioButton *fioStudent;
    QRadioButton *fioParents;
    QRadioButton *numChildrens;
    QRadioButton *moneyParents;

    QLabel *labelStudent;
    QLabel *labelFather;
    QLabel *labelMother;
    QLabel *labelFatherFrom;
    QLabel *labelFatherTo;
    QLabel *labelMotherFrom;
    QLabel *labelMotherTo;
    QLabel *labelNumberBrother;
    QLabel *labelNumberSister;

    QLineEdit *lineStudent;
    QLineEdit *lineFather;
    QLineEdit *lineMoneyFatherDown;
    QLineEdit *lineMoneyFatherUp;
    QLineEdit *lineMother;
    QLineEdit *lineMoneyMotherDown;
    QLineEdit *lineMoneyMotherUp;
    QLineEdit *lineNumberBrother;
    QLineEdit *lineNumberSister;

    QPushButton *butFind;
    QPushButton *butCancel;
};

#endif // FINDDIALOG_H
