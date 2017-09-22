#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>

class QLineEdit;
class QPushButton;
class QLabel;

class AddDialog : public QDialog
{
public:
    AddDialog(QWidget *parent=0);

//signals:

//private slots:

private:
    QLabel *labelStudent;
    QLabel *labelFather;
    QLabel *labelMoneyFather;
    QLabel *labelMother;
    QLabel *labelMoneyMother;
    QLabel *labelNumberBrother;
    QLabel *labelNumberSister;

    QLineEdit *lineStudent;
    QLineEdit *lineFather;
    QLineEdit *lineMoneyFather;
    QLineEdit *lineMother;
    QLineEdit *lineMoneyMother;
    QLineEdit *lineNumberBrother;
    QLineEdit *lineNumberSister;

    QPushButton *butAdd;
    QPushButton *butCancel;
};

#endif // ADDDIALOG_H
