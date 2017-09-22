//main window of GUI application

#include <QtWidgets>

#include "mainwindow.h"
#include "tablemodel.h"
#include "selectdialog.h"
#include "adddialog.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    model = new TableModel(this);

    selDialog = new SelectDialog(this);
    connect(selDialog, SIGNAL(sendData(QString)), this, SLOT(recieveData(QString)));

    addDialog = new AddDialog(this);
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    readSettings();

    setWindowIcon(QIcon(":/pic/icon.png"));
    setCurrentFile("");

    setWindowTitle(tr("GUI records"));
    setMinimumSize(320, 240);
    resize(640, 480);
}

void MainWindow::recieveData(QString str)
{
    if (str=="var10")  createWidget();
        //QMessageBox::about(this, tr("About Dialog"),tr("Var 10"));

    else if (str=="var11")  QMessageBox::about(this, tr("About Dialog"),tr("Var 11"));


    else if (str=="var12")  QMessageBox::about(this, tr("About Dialog"),      tr("Var 12"));


    else if (str=="var13")  QMessageBox::about(this, tr("About Dialog"),     tr("Var 13"));


    else QMessageBox::about(this, tr("About Dialog"),            tr("Var 14"));

}

void MainWindow::createWidget()
{
    tableView = new QTableView;
    tableView->setModel(model);
  //  tableView->setItemDelegate(new ItemDelegate(this));
    tableView->verticalHeader()->setDefaultAlignment(
            Qt::AlignVCenter|Qt::AlignRight);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(tableView);
    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
   /* if (okToContinue()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }*/
    event->accept();
}

void MainWindow::newFile()
{
    /*if (okToContinue()) {
            //textEdit->clear();
            setCurrentFile("");
        }*/
    selDialog->show();

}

void MainWindow::open()
{
   /* if (okToContinue()) {
            QString fileName = QFileDialog::getOpenFileName(this);
            if (!fileName.isEmpty())
                loadFile(fileName);
        }*/
}

bool MainWindow::save()
{
  /*  if (curFile.isEmpty()) {
            return saveAs();
        } else {
            return saveFile(curFile);
        }*/
}

bool MainWindow::saveAs()
{
  /*  QString fileName = QFileDialog::getSaveFileName(this,
                                   tr("Save Table"), ".",
                                   tr("Table files (*.xml)"));
    if (fileName.isEmpty()) return false;
    return saveFile(fileName);*/
}

//work with table ![1]
void MainWindow::addRecord()
{
    addDialog->show();
}

void MainWindow::findRecord()
{

}

void MainWindow::delRecord()
{

}
// [1]!

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Dialog"),
            tr("The second lab PPVIS"));
}

void MainWindow::documentWasModified()
{
  //  setWindowModified(textEdit->document()->isModified());
    updateStatusBar();
}

void MainWindow::updateStatusBar()
{

}

void MainWindow::createActions()
{
    newAction = new QAction(tr("&New"), this);
    newAction->setIcon(QIcon(":/pic/new.png"));
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Create a new file"));
    connect(newAction, &QAction::triggered, this, &MainWindow::newFile);

    openAction = new QAction(tr("&Open"), this);
    openAction->setIcon(QIcon(":/pic/open.png"));
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));
    connect(openAction, &QAction::triggered, this, &MainWindow::open);

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setIcon(QIcon(":/pic/save.png"));
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save the document to disk"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::save);

    saveAsAction = new QAction(tr("Save &As"), this);
    saveAsAction->setIcon(QIcon(":/pic/saveAs.png"));
    saveAsAction->setShortcuts(QKeySequence::SaveAs);
    saveAsAction->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveAs);

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setIcon(QIcon(":/pic/exit.png"));
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    addAction = new QAction(tr("Add"), this);
    addAction->setIcon(QIcon(":/pic/add.png"));
    addAction->setStatusTip(tr("Add new record"));
    connect(addAction, &QAction::triggered, this, &MainWindow::addRecord);

    findAction = new QAction(tr("Find"), this);
    findAction->setIcon(QIcon(":/pic/find.png"));
    findAction->setStatusTip(tr("Find record"));
    connect(findAction, &QAction::triggered, this, &MainWindow::findRecord);

    delAction = new QAction(tr("Delete"), this);
    delAction->setIcon(QIcon(":/pic/delete.png"));
    delAction->setStatusTip(tr("Delete existing record"));
    connect(delAction, &QAction::triggered, this, &MainWindow::delRecord);

    aboutAction = new QAction(tr("About"), this);
    aboutAction->setIcon(QIcon(":/pic/about.png"));
    aboutAction->setStatusTip(tr("Show the application's About Box"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
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

    recordToolBar = addToolBar(tr("&Edit"));
    recordToolBar->addAction(addAction);
    recordToolBar->addAction(findAction);
    recordToolBar->addAction(delAction);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
   // updateStatusBar();
}

void MainWindow::readSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
    if (geometry.isEmpty()) {
        const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
        resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2,
             (availableGeometry.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }
}

void MainWindow::writeSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue("geometry", saveGeometry());
}

bool MainWindow::okToContinue()
{
   // if (!textEdit->document()->isModified())
   //     return true;
    const QMessageBox::StandardButton ret
        = QMessageBox::warning(this, tr("Application"),
                               tr("The document has been modified.\n"
                                  "Do you want to save your changes?"),
                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    switch (ret) {
    case QMessageBox::Save:
        return save();
    case QMessageBox::Cancel:
        return false;
    default:
        break;
    }
    return true;
}

bool MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return false;
    }

    QTextStream in(&file);

    QApplication::setOverrideCursor(Qt::WaitCursor);

 //   textEdit->setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
    return true;
}

bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName),
                                  file.errorString()));
        return false;
    }

    QTextStream out(&file);

    QApplication::setOverrideCursor(Qt::WaitCursor);

  //  out << textEdit->toPlainText();

    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
  //  textEdit->document()->setModified(false);
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}


