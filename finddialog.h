//find record in array of records

#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
class QLabel;
class QCheckBox;
class QLineEdit;
class QPushButton;

class FindDialog:public QDialog
{
    Q_OBJECT
public:
    FindDialog(QWidget *parent=0);
signals:
    void findNext(const QString &str, bool caseSensitive);
    void findPrev(const QString &str, bool caseSensitive);
private slots:
    void findClicked();
    void enableFindButton(const QString &text);
private:
    QLabel *label;
    QLineEdit *lineEdit;
    QCheckBox *caseCheckBox;
    QCheckBox *backwardCheckBox;
    QPushButton *findButton;
    QPushButton *closeButton;
};
#endif // FINDDIALOG_H
