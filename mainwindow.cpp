//main window of GUI application

#include <QtWidgets>
#include "mainwindow.h"

MainWindow::MainWindow()
{
    textEdit = new QPlainTextEdit;
    setCentralWidget(textEdit);

    createActions();
    createStatusBar();
    readSettings();

    connect(textEdit->document(), &QTextDocument::contentsChanged,
            this, &MainWindow::documentWasModified);

    QGuiApplication::setFallbackSessionManagementEnabled(false);
    connect(qApp, &QGuiApplication::commitDataRequest,
            this, &MainWindow::commitData);

    setCurrentFile(QString());
    setUnifiedTitleAndToolBarOnMac(true);

    setWindowTitle(tr("GUI records"));
    setMinimumSize(320, 240);
    resize(640, 480);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::newFile()
{
    if (maybeSave()) {
            textEdit->clear();
            setCurrentFile(QString());
        }
}

void MainWindow::open()
{
    if (maybeSave()) {
            QString fileName = QFileDialog::getOpenFileName(this);
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
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec() != QDialog::Accepted)
        return false;
    return saveFile(dialog.selectedFiles().first());
}

//work with table ![1]
void MainWindow::addRecord()
{

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
    setWindowModified(textEdit->document()->isModified());
}


void MainWindow::createActions()
{
    //File Menu
    QMenu *fileMenu = menuBar()->addMenu(tr("File"));
    QToolBar *fileToolBar = addToolBar(tr("File"));

    const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/pic/newFile.png"));
    newAct = new QAction(newIcon, tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
    fileMenu->addAction(newAct);
    fileToolBar->addAction(newAct);

    const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/pic/openFile.png"));
    openAct = new QAction(openIcon, tr("&Open"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
    fileMenu->addAction(openAct);
    fileToolBar->addAction(openAct);

    const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(":/pic/saveFile.png"));
    saveAct = new QAction(saveIcon, tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);
    fileMenu->addAction(saveAct);
    fileToolBar->addAction(saveAct);

    const QIcon saveAsIcon = QIcon::fromTheme("document-save-as", QIcon(":/pic/saveFileAs.png"));
    saveAsAct = new QAction(saveAsIcon, tr("Save &As"), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAct, &QAction::triggered, this, &MainWindow::saveAs);
    fileMenu->addAction(saveAsAct);
    fileToolBar->addAction(saveAsAct);

    fileMenu->addSeparator();

    const QIcon exitIcon = QIcon::fromTheme("application-exit", QIcon(":/pic/exit.png"));
    exitAct = fileMenu->addAction(exitIcon, tr("E&xit"), this, &QWidget::close);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));

    //Record Menu
    QMenu *editMenu = menuBar()->addMenu(tr("Record"));
    QToolBar *editToolBar = addToolBar(tr("Record"));

    const QIcon addIcon = QIcon::fromTheme("record-add", QIcon(":/pic/add.png"));
    addAct = new QAction(addIcon, tr("Add"), this);
    addAct->setStatusTip(tr("Add new record"));
    connect(addAct, &QAction::triggered, this, &MainWindow::addRecord);
    editMenu->addAction(addAct);
    editToolBar->addAction(addAct);

    const QIcon findIcon = QIcon::fromTheme("record-find", QIcon(":/pic/find.png"));
    findAct = new QAction(findIcon, tr("Find"), this);
    findAct->setStatusTip(tr("Find record"));
    connect(findAct, &QAction::triggered, this, &MainWindow::findRecord);
    editMenu->addAction(findAct);
    editToolBar->addAction(findAct);

    const QIcon deleteIcon = QIcon::fromTheme("record-delete", QIcon(":/pic/delete.png"));
    delAct = new QAction(deleteIcon, tr("Delete"), this);
    delAct->setStatusTip(tr("Delete existing record"));
    connect(delAct, &QAction::triggered, this, &MainWindow::delRecord);
    editMenu->addAction(delAct);
    editToolBar->addAction(delAct);

    menuBar()->addSeparator();

    //Help Menu
    QMenu *helpMenu = menuBar()->addMenu(tr("Help"));
    const QIcon aboutIcon = QIcon::fromTheme("help-about", QIcon(":/pic/about.png"));
    aboutAct = new QAction(aboutIcon, tr("About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);
    helpMenu->addAction(aboutAct);

}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
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

bool MainWindow::maybeSave()
{
    if (!textEdit->document()->isModified())
        return true;
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

void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    QTextStream in(&file);

    QApplication::setOverrideCursor(Qt::WaitCursor);

    textEdit->setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
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

    out << textEdit->toPlainText();

    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    textEdit->document()->setModified(false);
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

void MainWindow::commitData(QSessionManager &manager)
{
    if (manager.allowsInteraction()) {
        if (!maybeSave())
            manager.cancel();
    } else {
        // Non-interactive: save without asking
        if (textEdit->document()->isModified())
            save();
    }
}
