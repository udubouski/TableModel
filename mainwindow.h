//main window of GUI application

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QAction;
class QActionGroup;
class QLabel;
class QMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

/*protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    */

private slots:
    void newFile();
    void open();
    void save();
    void saveAs();
    void addRecord();
    void findRecord();
    void delRecord();
    void about();

private:
    void createActions();
    void createMenus();

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

