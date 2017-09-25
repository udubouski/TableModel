//main window of GUI application

#include <QtWidgets>
#include "aqp.hpp"
#include "mainwindow.h"
#include "tablemodel.h"
#include "proxymodel.h"
#include "selectdialog.h"
#include "adddialog.h"
#include "finddialog.h"
#include "deletedialog.h"

const int StatusTimeout = AQP::MSecPerSecond * 10;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),loading(false)
{
    //MODELS [1]
    model = new TableModel(this);
    proxyModel = new ProxyModel(this);
    proxyModel->setSourceModel(model);
    // ![1]

    selDialog =0;
    addDialog =0;
    findDialog =0;
    delDialog =0;

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    createConnections();
    createWidget();

    setWindowIcon(QIcon(":/pic/icon.png"));
    setWindowTitle(tr("GUI records"));
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

/*void MainWindow::createToolPages()
{
    QHBoxLayout *hbox = new QHBoxLayout;

    QPushButton *butFirst = new QPushButton(QIcon(":/pic/first.png"),tr("First page"),this);
    QPushButton *butLast = new QPushButton(QIcon(":/pic/last.png"),tr("Last page"),this);
    QPushButton *butPrev = new QPushButton(QIcon(":/pic/previous.png"),tr("Previous page"),this);
    QPushButton *butNext = new QPushButton(QIcon(":/pic/next.png"),tr("Next page"),this);

    hbox->addWidget(butFirst);
    hbox->addWidget(butLast);
    hbox->addWidget(butPrev);
    hbox->addWidget(butNext);

    setLayout(hbox);
}*/

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

   /* connect(view->horizontalHeader(),
            SIGNAL(sectionClicked(int)),
            view, SLOT(sortByColumn(int)));

    connect(model,
        SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
        this, SLOT(setDirty()));

    connect(model, SIGNAL(rowsRemoved(const QModelIndex&,int,int)),
            this, SLOT(setDirty()));
    connect(model, SIGNAL(modelReset()), this, SLOT(setDirty()));*/

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
    if (true)
         event->accept();
     else
         event->ignore();
}

void MainWindow::newFile()
{
    selDialog = new SelectDialog(this);
    connect(selDialog, SIGNAL(sendData(QString)), this, SLOT(recieveVariant(QString)));
    selDialog-> show();
}

void MainWindow::open()
{
    //if (true)
      //      return;
        QString filename(model->filename());
        QString dir(filename.isEmpty() ? QString(".")
                    : QFileInfo(filename).canonicalPath());
        filename = QFileDialog::getOpenFileName(this,
                tr("%1 - Open").arg(QApplication::applicationName()),
                dir,
                tr("%1 (*.dat)").arg(QApplication::applicationName()));
        if (filename.isEmpty())
            return;

        //enableButtons(false);
        QMetaObject::invokeMethod(this, "load", Qt::QueuedConnection,
                                  Q_ARG(QString, filename));
}

/*
void MainWindow::enableButtons(bool enable)
{
    foreach(QPushButton *button, QList<QPushButton*>() << loadButton
            << saveButton << addButton << deleteButton) {
        button->setEnabled(enable);
        button->repaint(); // update isn't "strong" enough on non-Mac
    }
}*/

/*void MainWindow::open(const QString &filename)
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    loading = true;
    try {
        model->load(filename);
        view->resizeColumnsToContents();
        QHeaderView *header = view->horizontalHeader();
        header->setSortIndicatorShown(true);
        header->setSortIndicator(0, Qt::AscendingOrder);
        setWindowModified(false);
        setWindowTitle(tr("%1 - %2[*]")
                .arg(QApplication::applicationName())
                .arg(QFileInfo(filename).fileName()));
        statusBar()->showMessage(tr("Loaded %n person(s) from %1",
                "", model->rowCount()).arg(filename), StatusTimeout);
    } catch (AQP::Error &error) {
        AQP::warning(this, tr("Error"), tr("Failed to load %1: %2")
                .arg(filename).arg(QString::fromUtf8(error.what())));
    }
    loading = false;
    view->setFocus();
   // enableButtons();
    QApplication::restoreOverrideCursor();
}*/

bool MainWindow::save()
{
    try {
        model->save();
        setWindowModified(false);
        setWindowTitle(tr("%1 - %2[*]")
                .arg(QApplication::applicationName())
                .arg(QFileInfo(model->filename()).fileName()));
        statusBar()->showMessage(tr("Saved %1")
                .arg(model->filename()), StatusTimeout);
        return true;
    } catch (AQP::Error &error) {
        AQP::warning(this, tr("Error"), tr("Failed to save %1: %2")
                .arg(model->filename())
                .arg(QString::fromUtf8(error.what())));
        return false;
    }
}

bool MainWindow::saveAs()
{

}

void MainWindow::addRecord()
{
    addDialog = new AddDialog(this);
    connect(addDialog,SIGNAL(sendData(QString,QString,int,QString,int,int,int)),
            this,SLOT(recieveData(QString,QString,int,QString,int,int,int)));
    addDialog->show();
}

void MainWindow::findRecord()
{
    findDialog = new FindDialog(model,this);
    findDialog->show();
}

void MainWindow::delRecord()
{
    delDialog = new DeleteDialog(model,this);
    delDialog->show();
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Dialog"),tr("The second lab PPVIS"));
}

void MainWindow::recieveData(QString student, QString father, int moneyfather, QString mother, int moneymother, int numberbrothers, int numbersisters)
{
    /*if (!model->insertRow(model->rowCount()))
    return;
    view->scrollToBottom();
    view->setFocus();
    QModelIndex index = proxyModel->index(proxyModel->rowCount() - 1, Student);
    view->setCurrentIndex(index);
    view->edit(index);
*/
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


