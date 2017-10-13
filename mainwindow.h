//main window of GUI application

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "parser.h"
#include "record.h"
class QAction;
class QTableView;
class TableModel;
class ProxyModel;
class SelectDialog;
class AddDialog;
class FindDialog;
class DeleteDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent=0);

protected:
    void closeEvent(QCloseEvent *event);

public slots:
    void recieveVariant(QString str);
    void recieveData(QString student, QString father, int moneyfather, QString mother, int moneymother,
                     int numberbrothers, int numbersisters);
    void recSignal(bool chec);

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void addRecord();
    void findRecord();
    void delRecord();
    void about();
    void updateStatusBar(const QString &str);
    void documentWasModified();

private:
    void enableButtons(bool enable=true);
    void createWidget();
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createConnections();

    void readSettings();
    void writeSettings();
    bool okToContinue();
    bool loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);

    QString curFile;

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

    QAction *firstPageAction;
    QAction *lastPageAction;
    QAction *prevPageAction;
    QAction *nextPageAction;

    QTableView *view;
    TableModel *model;
    ProxyModel *proxyModel;

    SelectDialog *selDialog;
    AddDialog *addDialog;
    FindDialog *findDialog;
    DeleteDialog *delDialog;


};
#endif // MAINWINDOW_H

