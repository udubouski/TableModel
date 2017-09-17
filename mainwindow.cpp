//main window of GUI application

#include <QtWidgets>
#include "mainwindow.h"

MainWindow::MainWindow()
{
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to invoke a context menu</i>"));
    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(infoLabel);
    widget->setLayout(layout);

    createActions();
    createMenus();

    QString message = tr("Status Bar");
    statusBar()->showMessage(message);

    setWindowTitle(tr("GUI records"));
    setMinimumSize(320, 240);
    resize(640, 480);
}

void MainWindow::newFile()
{
    infoLabel->setText(tr("Invoked <b>File|New</b>"));
}

void MainWindow::open()
{
    infoLabel->setText(tr("Invoked <b>File|Open</b>"));
}

void MainWindow::save()
{
    infoLabel->setText(tr("Invoked <b>File|Save</b>"));
}

void MainWindow::saveAs()
{
    infoLabel->setText(tr("Invoked <b>File|Save</b>"));
}

void MainWindow::addRecord()
{
    infoLabel->setText(tr("Invoked <b>Record|Add</b>"));
}

void MainWindow::findRecord()
{
    infoLabel->setText(tr("Invoked <b>Record|Find</b>"));
}

void MainWindow::delRecord()
{
    infoLabel->setText(tr("Invoked <b>Record|Delete</b>"));
}

void MainWindow::about()
{
    infoLabel->setText(tr("Invoked <b>Help|About</b>"));
    QMessageBox::about(this, tr("About Menu"),
            tr("The <b>Menu</b> example shows how to create "
               "menu-bar menus and context menus."));
}

void MainWindow::createActions()
{
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    saveAsAct = new QAction(tr("&SaveAs"), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document to disk as ..."));
    connect(saveAsAct, &QAction::triggered, this, &MainWindow::saveAs);

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    addAct = new QAction(tr("&Add"), this);
    addAct->setStatusTip(tr("Add new record"));
    connect(addAct, &QAction::triggered, this, &MainWindow::addRecord);

    findAct = new QAction(tr("&Find"), this);
    findAct->setStatusTip(tr("Find record"));
    connect(findAct, &QAction::triggered, this, &MainWindow::findRecord);

    delAct = new QAction(tr("&Delete"), this);
    delAct->setStatusTip(tr("Delete existing record"));
    connect(delAct, &QAction::triggered, this, &MainWindow::delRecord);

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    recordMenu = menuBar()->addMenu(tr("&Edit"));
    recordMenu->addAction(addAct);
    recordMenu->addAction(findAct);
    recordMenu->addAction(delAct);
    recordMenu->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}
