//main window of GUI application

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "selectdialog.h"

class QAction;
class QActionGroup;
class QLabel;
class QMenu;

class QPlainTextEdit;
class QSessionManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    void loadFile(const QString &fileName);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();

    void addRecord();
    void findRecord();
    void delRecord();

    void about();

    void documentWasModified();
    void commitData(QSessionManager &);

private:
    void createActions();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool maybeSave();

    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);

    QMenu *fileMenu;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *exitAct;

    QMenu *recordMenu;
    QAction *addAct;
    QAction *findAct;
    QAction *delAct;

    QMenu *helpMenu;
    QAction *aboutAct;

    QPlainTextEdit *textEdit;
    QString curFile;

    SelectDialog *selDialog;


};
#endif // MAINWINDOW_H

