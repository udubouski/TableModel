//main window of GUI application

#include <QtWidgets>

#include "mainwindow.h"
#include "tablemodel.h"
#include "proxymodel.h"
#include "selectdialog.h"
#include "adddialog.h"
#include "finddialog.h"
#include "deletedialog.h"
#include "record.h"
#include "parser.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    //MODELS [1]
    model = new TableModel(this);
    proxyModel = new ProxyModel(this);
    proxyModel->setSourceModel(model);
    // ![1]

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    createConnections();
   // createWidget();

    readSettings();

    selDialog =0;
    addDialog =0;
    findDialog =0;
    delDialog =0;

    setCurrentFile("");
    setWindowIcon(QIcon(":/pic/icon.png"));
    setMinimumSize(320, 240);
    resize(640, 480);
}

void MainWindow::createActions()
{
    newAction = new QAction(tr("&New"), this);
    newAction->setIcon(QIcon(":/pic/new.png"));
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Create a new file"));

    openAction = new QAction(tr("&Open"), this);
    openAction->setIcon(QIcon(":/pic/open.png"));
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setIcon(QIcon(":/pic/save.png"));
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save the document to disk"));

    saveAsAction = new QAction(tr("Save &As"), this);
    saveAsAction->setIcon(QIcon(":/pic/saveAs.png"));
    saveAsAction->setShortcuts(QKeySequence::SaveAs);
    saveAsAction->setStatusTip(tr("Save the document under a new name"));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setIcon(QIcon(":/pic/exit.png"));
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Exit the application"));

    addAction = new QAction(tr("Add"), this);
    addAction->setIcon(QIcon(":/pic/add.png"));
    addAction->setStatusTip(tr("Add new record"));

    findAction = new QAction(tr("Find"), this);
    findAction->setIcon(QIcon(":/pic/find.png"));
    findAction->setStatusTip(tr("Find record"));

    delAction = new QAction(tr("Delete"), this);
    delAction->setIcon(QIcon(":/pic/delete.png"));
    delAction->setStatusTip(tr("Delete existing record"));

    aboutAction = new QAction(tr("About"), this);
    aboutAction->setIcon(QIcon(":/pic/about.png"));
    aboutAction->setStatusTip(tr("Show the application's About Box"));

    firstPageAction = new QAction(tr("firstPage"), this);
    firstPageAction->setIcon(QIcon(":/pic/first.png"));
    firstPageAction->setStatusTip(tr("First page"));

    lastPageAction = new QAction(tr("lastPage"), this);
    lastPageAction->setIcon(QIcon(":/pic/last.png"));
    lastPageAction->setStatusTip(tr("Last page"));

    prevPageAction = new QAction(tr("prevPage"), this);
    prevPageAction->setIcon(QIcon(":/pic/previous.png"));
    prevPageAction->setStatusTip(tr("Previous page"));

    nextPageAction = new QAction(tr("nextPage"), this);
    nextPageAction->setIcon(QIcon(":/pic/next.png"));
    nextPageAction->setStatusTip(tr("Next page"));

}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    recordMenu = menuBar()->addMenu(tr("&Record"));
    recordMenu->addAction(addAction);
    recordMenu->addAction(findAction);
    recordMenu->addAction(delAction);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);
    fileToolBar->addAction(saveAsAction);

    recordToolBar = addToolBar(tr("&Record"));
    recordToolBar->addAction(addAction);
    recordToolBar->addAction(findAction);
    recordToolBar->addAction(delAction);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::createConnections()
{
    connect(newAction, &QAction::triggered, this, &MainWindow::newFile);
    connect(openAction, &QAction::triggered, this, &MainWindow::open);
    connect(saveAction, &QAction::triggered, this, &MainWindow::save);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveAs);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    connect(addAction, &QAction::triggered, this, &MainWindow::addRecord);
    connect(findAction, &QAction::triggered, this, &MainWindow::findRecord);
    connect(delAction, &QAction::triggered, this, &MainWindow::delRecord);

    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);

    connect(model, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),this, SLOT(documentWasModified()));

}

void MainWindow::recieveVariant(QString str)
{
    if (str=="var10")  QMessageBox::about(this, tr("About Dialog"),tr("Var 10"));

    else if (str=="var11")  QMessageBox::about(this, tr("About Dialog"),tr("Var 11"));


    else if (str=="var12")  QMessageBox::about(this, tr("About Dialog"),      tr("Var 12"));


    else if (str=="var13")  QMessageBox::about(this, tr("About Dialog"),     tr("Var 13"));

    else QMessageBox::about(this, tr("About Dialog"),            tr("Var 14"));

}

void MainWindow::createWidget()
{
    view = new QTableView;
    view->setModel(proxyModel);
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setCentralWidget(view);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (okToContinue()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::newFile()
{
    if (okToContinue()) {
        model->clear();
        selDialog = new SelectDialog(this);
        connect(selDialog, SIGNAL(sendData(QString)), this, SLOT(recieveVariant(QString)));
        selDialog-> show();
        selDialog->raise();
        selDialog->activateWindow();
        setCurrentFile("");
    }
}

void MainWindow::open()
{
    if (okToContinue()) {
        QString fileName = QFileDialog::getOpenFileName(this,
                                   tr("Open Table"), ".",
                                   tr("XML files (*.xml)"));
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}


bool MainWindow::save()
{
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }

}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                               tr("Save Table"), ".",
                               tr("XML files (*.xml)"));
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

void MainWindow::addRecord()
{
    addDialog = new AddDialog(this);
    connect(addDialog,SIGNAL(sendData(QString,QString,int,QString,int,int,int)),
            this,SLOT(recieveData(QString,QString,int,QString,int,int,int)));
    addDialog->show();
    addDialog->raise();
    addDialog->activateWindow();
}

void MainWindow::findRecord()
{
    findDialog = new FindDialog(model,this);
    findDialog->show();
    findDialog->raise();
    findDialog->activateWindow();
}

void MainWindow::delRecord()
{
    delDialog = new DeleteDialog(model,this);
    connect(delDialog,SIGNAL(sendSignal(bool)),this, SLOT(recSignal(bool)));
    delDialog->show();
    delDialog->raise();
    delDialog->activateWindow();
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Dialog"),tr("The second lab PPVIS"));
}

void MainWindow::recieveData(QString student, QString father, int moneyfather, QString mother, int moneymother, int numberbrothers, int numbersisters)
{
    model->insertRows(model->rowCount(), 1, QModelIndex());

    QModelIndex index = proxyModel->index(proxyModel->rowCount()-1, 0, QModelIndex());
    model->setData(index, student, Qt::EditRole);

    index = proxyModel->index(proxyModel->rowCount()-1, 1, QModelIndex());
    model->setData(index,father, Qt::EditRole);

    index = proxyModel->index(proxyModel->rowCount()-1, 2, QModelIndex());
    model->setData(index,moneyfather, Qt::EditRole);

    index = proxyModel->index(proxyModel->rowCount()-1, 3, QModelIndex());
    model->setData(index,mother, Qt::EditRole);

    index = proxyModel->index(proxyModel->rowCount()-1, 4, QModelIndex());
    model->setData(index,moneymother, Qt::EditRole);

    index = proxyModel->index(proxyModel->rowCount()-1, 5, QModelIndex());
    model->setData(index,numberbrothers, Qt::EditRole);

    index = proxyModel->index(proxyModel->rowCount()-1, 6, QModelIndex());
    model->setData(index,numbersisters, Qt::EditRole);
}

void MainWindow::updateStatusBar(const QString &str)
{
    statusBar()->showMessage(str,2000);
}

void MainWindow::documentWasModified()
{
    setWindowModified(true);
    updateStatusBar("Document was modified");
}

void MainWindow::readSettings()
{
    QSettings settings("Software", "Table Model");

    restoreGeometry(settings.value("geometry").toByteArray());

}

void MainWindow::writeSettings()
{
    QSettings settings("Software", "Table Model");

    settings.setValue("geometry", saveGeometry());

}

bool MainWindow::okToContinue()
{
    if (isWindowModified()) {
        int r = QMessageBox::warning(this, tr("Table"),
                        tr("The document has been modified.\n"
                           "Do you want to save your changes?"),
                        QMessageBox::Yes | QMessageBox::No
                        | QMessageBox::Cancel);
        if (r == QMessageBox::Yes) {
            return save();
        } else if (r == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

bool MainWindow::loadFile(const QString &fileName)
{
    if (!model->readFile(fileName)) {
        statusBar()->showMessage(tr("Loading canceled"), 2000);
        return false;
    }
    createWidget();
    model->clear();
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
    return true;
}

bool MainWindow::saveFile(const QString &fileName)
{
  /* if (!model->writeFile(fileName)) {
        statusBar()->showMessage(tr("Saving canceled"), 2000);
        return false;
    }*/
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowModified(false);

    QString shownName = tr("Untitled");
    if (!curFile.isEmpty()) {
        shownName = strippedName(curFile);
    }

    setWindowTitle(tr("%1[*] - %2").arg(shownName)
                                   .arg(tr("Table")));
}


QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::recSignal(bool chec)
{
    if (chec==true)
    {
       documentWasModified();
    }
}
