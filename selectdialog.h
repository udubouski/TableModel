//select dialog

#ifndef SELECTDIALOG_H
#define SELECTDIALOG_H

#include <QDialog>

class QRadioButton;
class QGroupBox;
class QPushButton;

class SelectDialog : public QDialog
{
    Q_OBJECT

public:
    SelectDialog(QWidget *parent=0);

    bool var10() const;
    bool var11() const;
    bool var12() const;
    bool var13() const;
    bool var14() const;


signals:
    void sendData(QString str);

private slots:
    void onButtonSend();

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
