//select dialog

#include <QtWidgets>
#include <selectdialog.h>

SelectDialog::SelectDialog(QWidget *parent) : QDialog(parent)
{
    box = new QGroupBox(tr("Select variant of task"));

    rad10ch = new QRadioButton(tr("Variant 10"));
    rad11ch = new QRadioButton(tr("Variant 11"));
    rad12ch = new QRadioButton(tr("Variant 12"));
    rad13ch = new QRadioButton(tr("Variant 13"));
    rad14ch = new QRadioButton(tr("Variant 14"));

    butOk = new QPushButton(tr("OK"));
    butCancel = new QPushButton(tr("Cancel"));

    connect(butOk,SIGNAL(clicked()),this,SLOT(close()));
    connect(butCancel,SIGNAL(clicked()),this,SLOT(close()));

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

    setWindowTitle("Select dialog");
    setFixedHeight(sizeHint().height());
}
