//main window of GUI application

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class SelectDialog;
class QPlainTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

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
    void updateStatusBar();

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();

    void readSettings();
    void writeSettings();

    bool okToContinue();
    bool loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    void updateRecentFileActions();
    QString strippedName(const QString &fullFileName);

    SelectDialog *selDialog;
    QString curFile;
    QPlainTextEdit *textEdit;

    QMenu *fileMenu;
    QMenu *recordMenu;
    QMenu *helpMenu;

    QToolBar *fileToolBar;
    QToolBar *recordToolBar;

    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *exitAction;
    QAction *addAction;
    QAction *findAction;
    QAction *delAction;
    QAction *aboutAction;
};
#endif // MAINWINDOW_H

