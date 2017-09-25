#include <QtWidgets>
#include "adddialog.h"

AddDialog::AddDialog(QWidget *parent) : QDialog(parent)
{
    createWidget();
    createLayout();
    createConnections();

    setWindowTitle("Add record");
    setFixedHeight(sizeHint().height());
}

void AddDialog::createWidget()
{
    labelStudent = new QLabel(tr("Student"));
    labelFather = new QLabel(tr("Father"));
    labelMoneyFather = new QLabel(tr("Money father"));
    labelMother = new QLabel(tr("Mother"));
    labelMoneyMother = new QLabel(tr("Money mother"));
    labelNumberBrother = new QLabel(tr("Number brother"));
    labelNumberSister = new QLabel  (tr("Number sister"));

    lineStudent = new QLineEdit;
    lineFather = new QLineEdit;
    lineMoneyFather = new QLineEdit;
    lineMother = new QLineEdit;
    lineMoneyMother = new QLineEdit;
    lineNumberBrother = new QLineEdit;
    lineNumberSister = new QLineEdit;

    butAdd = new QPushButton(tr("Add"));
    butCancel = new QPushButton(tr("Cancel"));
}

void AddDialog::createConnections()
{
    connect(butAdd,SIGNAL(clicked()),this,SLOT(addRecord()));
    connect(butCancel,SIGNAL(clicked()),this,SLOT(close()));
}

void AddDialog::createLayout()
{
    QVBoxLayout *lbox = new QVBoxLayout;
    lbox->addWidget(labelStudent);
    lbox->addWidget(labelFather);
    lbox->addWidget(labelMoneyFather);
    lbox->addWidget(labelMother);
    lbox->addWidget(labelMoneyMother);
    lbox->addWidget(labelNumberBrother);
    lbox->addWidget(labelNumberSister);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(lineStudent);
    vbox->addWidget(lineFather);
    vbox->addWidget(lineMoneyFather);
    vbox->addWidget(lineMother);
    vbox->addWidget(lineMoneyMother);
    vbox->addWidget(lineNumberBrother);
    vbox->addWidget(lineNumberSister);

    QHBoxLayout *fbox = new QHBoxLayout;
    fbox->addLayout(lbox);
    fbox->addLayout(vbox);

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(butAdd);
    hbox->addWidget(butCancel);

    QVBoxLayout *mainlayout = new QVBoxLayout;
    mainlayout->addLayout(fbox);
    mainlayout->addLayout(hbox);
    setLayout(mainlayout);
}

void AddDialog::addRecord()
{
    emit sendData(lineStudent->text(),lineFather->text(),lineMoneyFather->text().toInt(),lineMother->text(),
                  lineMoneyMother->text().toInt(),lineNumberBrother->text().toInt(),lineNumberSister->text().toInt());
    this->close();
}
