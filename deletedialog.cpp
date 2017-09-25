#include <QtWidgets>
#include "deletedialog.h"
#include "proxymodel.h"
#include "uniqueproxymodel.h"

DeleteDialog::DeleteDialog(TableModel *model_,QWidget *parent) : QDialog(parent)
{
    model=model_;
    proxyModel = new ProxyModel(this);
    proxyModel->setSourceModel(model);

    createWidget();
    createComboBoxModels();
    createConnections();

    setWindowTitle("Delete record");
    setFixedHeight(sizeHint().height());
}

void DeleteDialog::createWidget()
{
    labelStudent = new QLabel(tr("Student"));
    labelFather = new QLabel(tr("Father"));
    labelMother = new QLabel(tr("Mother"));
    labelFatherFrom = new QLabel(tr("Father money from"));
    labelFatherTo = new QLabel(tr("to"));
    labelMotherFrom = new QLabel(tr("Mother money from"));
    labelMotherTo = new QLabel(tr("to"));
    labelNumberBrother = new QLabel(tr("Number brothers"));
    labelNumberSister = new QLabel  (tr("Number sisters"));

    lineStudent = new QComboBox;
    lineFather = new QComboBox;
    lineMoneyFatherDown = new QSpinBox;
    lineMoneyFatherDown->setRange(MinCode,MaxCode);
    lineMoneyFatherUp = new QSpinBox;
    lineMoneyFatherUp->setRange(MinCode,MaxCode);
    lineMother = new QComboBox;
    lineMoneyMotherDown = new QSpinBox;
    lineMoneyMotherUp = new QSpinBox;
    lineMoneyMotherDown->setRange(MinCode,MaxCode);
    lineMoneyMotherUp->setRange(MinCode,MaxCode);
    lineNumberBrother = new QComboBox;
    lineNumberSister = new QComboBox;

    butDelete = new QPushButton(tr("Delete"));
    butCancel = new QPushButton(tr("Cancel"));

    QHBoxLayout *main = new QHBoxLayout;
    QGridLayout *grid = new QGridLayout;

    QVBoxLayout *vbox1 = new QVBoxLayout;
    vbox1->addWidget(labelStudent);
    vbox1->addWidget(lineStudent);
    box1 = new QGroupBox(tr("Student"));
    box1->setCheckable(true);
    box1->setChecked(false);
    box1->setLayout(vbox1);
    grid->addWidget(box1,0,0);

    QVBoxLayout *vbox2 = new QVBoxLayout;
    vbox2->addWidget(labelFather);
    vbox2->addWidget(lineFather);
    vbox2->addWidget(labelMother);
    vbox2->addWidget(lineMother);
    box2 = new QGroupBox(tr("Parents"));
    box2->setCheckable(true);
    box2->setChecked(false);
    box2->setLayout(vbox2);
    grid->addWidget(box2,0,1);

    QVBoxLayout *vbox3 = new QVBoxLayout;
    vbox3->addWidget(labelNumberBrother);
    vbox3->addWidget(lineNumberBrother);
    vbox3->addWidget(labelNumberSister);
    vbox3->addWidget(lineNumberSister);
    box3 = new QGroupBox(tr("Number brothers or sisters"));
    box3->setCheckable(true);
    box3->setChecked(false);
    box3->setLayout(vbox3);
    grid->addWidget(box3,1,0);

    QVBoxLayout *vbox4 = new QVBoxLayout;
    vbox4->addWidget(labelFatherFrom);
    vbox4->addWidget(lineMoneyFatherDown);
    vbox4->addWidget(labelFatherTo);
    vbox4->addWidget(lineMoneyFatherUp);
    vbox4->addWidget(labelMotherFrom);
    vbox4->addWidget(lineMoneyMotherDown);
    vbox4->addWidget(labelMotherTo);
    vbox4->addWidget(lineMoneyMotherUp);
    box4 = new QGroupBox(tr("Money parents"));
    box4->setCheckable(true);
    box4->setChecked(false);
    box4->setLayout(vbox4);
    grid->addWidget(box4,1,1);

    grid->addWidget(butDelete,2,0);
    grid->addWidget(butCancel,2,1);

    resultTable = new QTableView;
    resultTable->setModel(proxyModel);
    resultTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    main->addLayout(grid);
    main->addWidget(resultTable);
    setLayout(main);
}
void DeleteDialog::createComboBoxModels()
{
    createComboBoxModel(lineStudent,0);
    createComboBoxModel(lineFather,1);
    createComboBoxModel(lineMother,3);
    createComboBoxModel(lineNumberBrother,5);
    createComboBoxModel(lineNumberSister,6);
}

void DeleteDialog::createComboBoxModel(QComboBox *comboBox, int column)
{
    delete comboBox->model();
    UniqueProxyModel *uniqueProxyModel = new UniqueProxyModel(column,this);
    uniqueProxyModel->setSourceModel(model);
    uniqueProxyModel->sort(column,Qt::AscendingOrder);
    comboBox->setModel(uniqueProxyModel);
    comboBox->setModelColumn(column);
}

void DeleteDialog::createConnections()
{
    connect(butDelete,SIGNAL(clicked()),this,SLOT(delRecord()));
    connect(butCancel,SIGNAL(clicked()),this,SLOT(close()));

    connect(model, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),this, SLOT(setDirty()));
    connect(model, SIGNAL(rowsRemoved(const QModelIndex&,int,int)),
               this, SLOT(setDirty()));
    connect(model, SIGNAL(modelReset()), this, SLOT(setDirty()));

    connect(box1, SIGNAL(toggled(bool)),this, SLOT(updateUi()));
    connect(lineStudent,SIGNAL(currentIndexChanged(const QString&)),this, SLOT(updateUi()));

    connect(box2, SIGNAL(toggled(bool)),this, SLOT(updateUi()));
    connect(lineFather,SIGNAL(currentIndexChanged(const QString&)),this, SLOT(updateUi()));
    connect(lineFather,SIGNAL(currentIndexChanged(const QString&)),this, SLOT(updateUi()));

    connect(box3, SIGNAL(toggled(bool)),this, SLOT(updateUi()));
    connect(lineNumberBrother,SIGNAL(currentIndexChanged(const QString&)),this, SLOT(updateUi()));
    connect(lineNumberSister,SIGNAL(currentIndexChanged(const QString&)),this, SLOT(updateUi()));

    connect(box4, SIGNAL(toggled(bool)),this, SLOT(updateUi()));
    connect(lineMoneyFatherDown,SIGNAL(valueChanged(int)),this, SLOT(updateUi()));
    connect(lineMoneyFatherUp,SIGNAL(valueChanged(int)),this, SLOT(updateUi()));
    connect(lineMoneyMotherDown,SIGNAL(valueChanged(int)),this, SLOT(updateUi()));
    connect(lineMoneyMotherUp,SIGNAL(valueChanged(int)),this, SLOT(updateUi()));

    connect(resultTable->horizontalHeader(),
                SIGNAL(sectionClicked(int)),
                resultTable, SLOT(sortByColumn(int)));
}

void DeleteDialog::updateUi()
{
    if (box1->isChecked())
            restoreFilters();
    else if (box2->isChecked())
        restoreFilters2();
    else if (box3->isChecked())
        restoreFilters3();
    else if (box4->isChecked())
        restoreFilters4();
    else proxyModel->clearFilters();
}

void DeleteDialog::restoreFilters()
{
    proxyModel->setStudent(box1->isChecked()
                ? lineStudent->currentText() : QString());
}

void DeleteDialog::restoreFilters2()
{
    if (box2->isChecked())
    {
        proxyModel->setFather(lineFather->currentText());
        proxyModel->setMother(lineMother->currentText());
    }
    else
    {
        proxyModel->setFather(QString());
        proxyModel->setMother(QString());
    }
}

void DeleteDialog::restoreFilters3()
{
    if (box3->isChecked())
    {
         proxyModel->setNumberBrothers(lineNumberBrother->currentText().toInt());
         proxyModel->setNumberSisters(lineNumberSister->currentText().toInt());
    }
    else
    {
        proxyModel->setNumberBrothers(0);
        proxyModel->setNumberSisters(0);
    }
}

void DeleteDialog::restoreFilters4()
{
    if (box4->isChecked())
    {
        proxyModel->setMinMoneyFather(lineMoneyFatherDown->value());
        proxyModel->setMaxMoneyFather(lineMoneyFatherUp->value());
        proxyModel->setMinMoneyMother(lineMoneyMotherDown->value());
        proxyModel->setMaxMoneyMother(lineMoneyMotherUp->value());
    }
    else
    {
        proxyModel->setMinMoneyFather(0);
        proxyModel->setMaxMoneyFather(0);
        proxyModel->setMinMoneyMother(0);
        proxyModel->setMaxMoneyMother(0);
    }
}

void DeleteDialog::delRecord()
{
    QItemSelectionModel *selectionModel = resultTable->selectionModel();
        if (!selectionModel->hasSelection())
            return;
        QModelIndex index = proxyModel->mapToSource(
                selectionModel->currentIndex());
        if (!index.isValid())
            return;

        if (!okToDelete(this, tr("Delete Person"),
                tr("Delete Person %1?").arg(index.row()+1, 5, 10, QChar('0'))))
            return;

        bool b_box1=box1->isChecked();
        bool b_box2=box2->isChecked();
        bool b_box3=box3->isChecked();
        bool b_box4=box4->isChecked();

        QString student,father,mother;
        int numBrother,numSister,minMoneyFather,minMoneyMother,maxMoneyFather,maxMoneyMother;
        student = box1->isChecked()
                ? lineStudent->currentText() : QString();
        if (box2->isChecked())
        {
            father = lineFather->currentText();
            mother = lineMother->currentText();
        }
        else
        {
            father = QString();
            mother = QString();
        }

        if (box3->isChecked())
        {
            numBrother = lineNumberBrother->currentText().toInt();
            numSister = lineNumberSister->currentText().toInt();
        }
        else
        {
            numBrother = 0;
            numSister = 0;
        }

        if (box4->isChecked())
        {
            minMoneyFather=lineMoneyFatherDown->value();
            minMoneyMother=lineMoneyMotherDown->value();
            maxMoneyFather=lineMoneyFatherUp->value();
            maxMoneyMother=lineMoneyMotherUp->value();
        }
        else
        {
            minMoneyFather=0;
            minMoneyMother=0;
            maxMoneyFather=0;
            maxMoneyMother=0;
        }

        model->removeRow(index.row(), index.parent());

        createComboBoxModels();
        if (!student.isEmpty())
            lineStudent->setCurrentIndex(
                    lineStudent->findText(student));
        if (!father.isEmpty())
            lineFather->setCurrentIndex(
                    lineFather->findText(father));
        if (!mother.isEmpty())
            lineMother->setCurrentIndex(
                    lineMother->findText(mother));
      /*  if (numBrother!=0)
            lineNumberBrother->setCurrentIndex(
                    lineNumberBrother->findData(numBrother));
        if (numSister!=0)
            lineNumberSister->setCurrentIndex(
                    lineNumberSister->findText(numSister));*/

        if (b_box1)
            box1->setChecked(false);
        else if (b_box2)
            box2->setChecked(false);
        else if (b_box3)
            box3->setChecked(false);
        else if (b_box4)
            box4->setChecked(false);
}

bool DeleteDialog::okToDelete(QWidget *parent, const QString &title,
                const QString &text, const QString &detailedText)
{
    QScopedPointer<QMessageBox> messageBox(new QMessageBox(parent));
    if (parent)
        messageBox->setWindowModality(Qt::WindowModal);
    messageBox->setIcon(QMessageBox::Question);
    messageBox->setWindowTitle(QString("%1 - %2")
            .arg(QApplication::applicationName()).arg(title));
    messageBox->setText(text);
    if (!detailedText.isEmpty())
        messageBox->setInformativeText(detailedText);
    QAbstractButton *deleteButton = messageBox->addButton(
            QObject::tr("&Delete"), QMessageBox::AcceptRole);
    messageBox->addButton(QObject::tr("Do &Not Delete"),
                          QMessageBox::RejectRole);
    messageBox->setDefaultButton(
            qobject_cast<QPushButton*>(deleteButton));
    messageBox->exec();
    return messageBox->clickedButton() == deleteButton;
}
