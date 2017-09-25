#include <QtWidgets>
#include "finddialog.h"

FindDialog::FindDialog(QWidget *parent) : QDialog(parent)
{
    fioStudent = new QRadioButton(tr("Student"));
    fioParents = new QRadioButton(tr("Parents"));
    numChildrens = new QRadioButton(tr("Number children"));
    moneyParents = new QRadioButton(tr("Money parents"));

    labelStudent = new QLabel(tr("Student"));
    labelFather = new QLabel(tr("Father"));
    labelMother = new QLabel(tr("Mother"));
    labelFatherFrom = new QLabel(tr("Father money from"));
    labelFatherTo = new QLabel(tr("to"));
    labelMotherFrom = new QLabel(tr("Mother money from"));
    labelMotherTo = new QLabel(tr("to"));
    labelNumberBrother = new QLabel(tr("Number brother"));
    labelNumberSister = new QLabel  (tr("Number sister"));

    lineStudent = new QLineEdit;
    lineFather = new QLineEdit;
    lineMoneyFatherDown = new QLineEdit;
    lineMoneyFatherUp = new QLineEdit;
    lineMother = new QLineEdit;
    lineMoneyMotherDown = new QLineEdit;
    lineMoneyMotherUp = new QLineEdit;
    lineNumberBrother = new QLineEdit;
    lineNumberSister = new QLineEdit;

    QGridLayout *grid = new QGridLayout;

    QVBoxLayout *vbox1 = new QVBoxLayout;
    vbox1->addWidget(labelStudent);
    vbox1->addWidget(lineStudent);
    QGroupBox *box1 = new QGroupBox(tr("Student"));
    box1->setCheckable(true);
    box1->setChecked(false);
    box1->setLayout(vbox1);
    grid->addWidget(box1,0,0);

    QVBoxLayout *vbox2 = new QVBoxLayout;
    vbox2->addWidget(labelFather);
    vbox2->addWidget(lineFather);
    vbox2->addWidget(labelMother);
    vbox2->addWidget(lineMother);
    QGroupBox *box2 = new QGroupBox(tr("Parents"));
    box2->setCheckable(true);
    box2->setChecked(false);
    box2->setLayout(vbox2);
    grid->addWidget(box2,0,1);

    QVBoxLayout *vbox3 = new QVBoxLayout;
    vbox3->addWidget(labelNumberBrother);
    vbox3->addWidget(lineNumberBrother);
    vbox3->addWidget(labelNumberSister);
    vbox3->addWidget(lineNumberSister);
    QGroupBox *box3 = new QGroupBox(tr("Number brothers or sisters"));
    box3->setCheckable(true);
    box3->setChecked(false);
    box3->setLayout(vbox3);
    grid->addWidget(box3,1,0);

    QVBoxLayout *vbox4 = new QVBoxLayout;
    vbox4->addWidget(labelFatherFrom);
    vbox4->addWidget(lineMoneyFatherDown);
    vbox4->addWidget(labelFatherTo);
    vbox4->addWidget(lineMoneyFatherUp);
    vbox4->addWidget(labelMotherFrom);
    vbox4->addWidget(lineMoneyMotherDown);
    vbox4->addWidget(labelMotherTo);
    vbox4->addWidget(lineMoneyMotherUp);
    QGroupBox *box4 = new QGroupBox(tr("Money parents"));
    box4->setCheckable(true);
    box4->setChecked(false);
    box4->setLayout(vbox4);
    grid->addWidget(box4,1,1);

    butFind = new QPushButton(tr("Find"));
    butCancel = new QPushButton(tr("Cancel"));
    grid->addWidget(butFind,2,0);
    grid->addWidget(butCancel,2,1);
    setLayout(grid);

    connect(butFind,SIGNAL(clicked()),this,SLOT(close()));
    connect(butCancel,SIGNAL(clicked()),this,SLOT(close()));

    setWindowTitle("Find record");
    setFixedHeight(sizeHint().height());
}




