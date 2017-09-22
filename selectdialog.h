//select dialog

#ifndef SELECTDIALOG_H
#define SELECTDIALOG_H

#include <QDialog>

class QRadioButton;
class QGroupBox;
class QPushButton;

class SelectDialog : public QDialog
{
public:
    SelectDialog(QWidget *parent=0);

private:
    QGroupBox *box;
    QRadioButton *rad10ch;
    QRadioButton *rad11ch;
    QRadioButton *rad12ch;
    QRadioButton *rad13ch;
    QRadioButton *rad14ch;
    QPushButton *butOk;
    QPushButton *butCancel;
};
#endif // SELECTDIALOG_H
