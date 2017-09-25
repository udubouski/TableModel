//select dialog

#include <QtWidgets>
#include "selectdialog.h"

SelectDialog::SelectDialog(QWidget *parent) : QDialog(parent)
{
    createWidget();
    createLayout();
    createConnections();

    setWindowTitle("Select dialog");
    setFixedHeight(sizeHint().height());

}

void SelectDialog::createWidget()
{
    box = new QGroupBox(tr("Select variant of task"));

    rad10ch = new QRadioButton(tr("Variant 10"));
    rad11ch = new QRadioButton(tr("Variant 11"));
    rad12ch = new QRadioButton(tr("Variant 12"));
    rad13ch = new QRadioButton(tr("Variant 13"));
    rad14ch = new QRadioButton(tr("Variant 14"));

    butOk = new QPushButton(tr("OK"));
    butCancel = new QPushButton(tr("Cancel"));

}

void SelectDialog::createLayout()
{
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(rad10ch);
    vbox->addWidget(rad11ch);
    vbox->addWidget(rad12ch);
    vbox->addWidget(rad13ch);
    vbox->addWidget(rad14ch);
    box->setLayout(vbox);

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(butOk);
    hbox->addWidget(butCancel);

    QVBoxLayout *mainlayout = new QVBoxLayout;
    mainlayout->addWidget(box);
    mainlayout->addLayout(hbox);
    setLayout(mainlayout);
}

bool SelectDialog::var10() const
{
    return rad10ch->isChecked();
}

bool SelectDialog::var11() const
{
    return rad11ch->isChecked();
}

bool SelectDialog::var12() const
{
    return rad12ch->isChecked();
}

bool SelectDialog::var13() const
{
    return rad13ch->isChecked();
}

bool SelectDialog::var14() const
{
    return rad14ch->isChecked();
}

void SelectDialog::onButtonSend()
{
    if (var10())
    {
        emit sendData("var10");
        this->close();
    }

    else if (var11())
    {
        emit sendData("var11");
        this->close();
    }

    else if (var12())
    {
        emit sendData("var12");
        this->close();
    }

    else if (var13())
    {
        emit sendData("var13");
        this->close();
    }

    else
    {
        emit sendData("var14");
        this->close();
    }
}

void SelectDialog::createConnections()
{
    connect(butOk,SIGNAL(clicked()),this,SLOT(onButtonSend()));
    connect(butCancel,SIGNAL(clicked()),this,SLOT(close()));
}

