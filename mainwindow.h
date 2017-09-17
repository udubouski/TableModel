//main window of GUI application

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    void closeEvent(QCloseEvent *event) override;

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

    QPlainTextEdit *textEdit;
    QString curFile;

    QMenu *fileMenu;
    QMenu *recordMenu;
    QMenu *helpMenu;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *exitAct;
    QAction *addAct;
    QAction *findAct;
    QAction *delAct;
    QAction *aboutAct;
    QLabel *infoLabel;

};
#endif // MAINWINDOW_H

