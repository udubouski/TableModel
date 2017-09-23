//main window of GUI application

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QTableView;
class TableModel;
class SelectDialog;
class AddDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent=0);

protected:
    void closeEvent(QCloseEvent *event);

public slots:
    void recieveData(QString str);

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();

    void addRecord();
    void findRecord();
    void delRecord();

    void about();

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createToolPages();
    void createStatusBar();

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

    QTableView *tableView;
    TableModel *model;

    SelectDialog *selDialog;
    AddDialog *addDialog;
};
#endif // MAINWINDOW_H

