#include <QtWidgets>
#include "finddialog.h"
#include "proxymodel.h"
#include "uniqueproxymodel.h"

FindDialog::FindDialog(TableModel *model_,QWidget *parent) : QDialog(parent)
{
    model=model_;
    proxyModel = new ProxyModel(this);
    proxyModel->setSourceModel(model);

    createWidget();
    createComboBoxModels();
    createConnections();

    setWindowTitle("Find record");
    setFixedHeight(sizeHint().height());
}

void FindDialog::createWidget()
{
    labelStudent = new QLabel(tr("Student"));
    labelFather = new QLabel(tr("Father"));
    labelMother = new QLabel(tr("Mother"));
    labelFatherFrom = new QLabel(tr("Father money from"));
    labelFatherTo = new QLabel(tr("to"));
    labelMotherFrom = new QLabel(tr("Mother money from"));
    labelMotherTo = new QLabel(tr("to"));
    labelNumberBrother = new QLabel(tr("Number brother"));
    labelNumberSister = new QLabel  (tr("Number sister"));

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

    butFind = new QPushButton(tr("Find"));
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

    grid->addWidget(butFind,2,0);
    grid->addWidget(butCancel,2,1);

    resultTable = new QTableView;
    resultTable->setModel(proxyModel);
    resultTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    main->addLayout(grid);
    main->addWidget(resultTable);
    setLayout(main);
}
void FindDialog::createComboBoxModels()
{
    createComboBoxModel(lineStudent,0);
    createComboBoxModel(lineFather,1);
    createComboBoxModel(lineMother,3);
    createComboBoxModel(lineNumberBrother,5);
    createComboBoxModel(lineNumberSister,6);
}

void FindDialog::createComboBoxModel(QComboBox *comboBox, int column)
{
    delete comboBox->model();
    UniqueProxyModel *uniqueProxyModel = new UniqueProxyModel(column,this);
    uniqueProxyModel->setSourceModel(model);
    uniqueProxyModel->sort(column,Qt::AscendingOrder);
    comboBox->setModel(uniqueProxyModel);
    comboBox->setModelColumn(column);
}

void FindDialog::createConnections()
{
    connect(butFind,SIGNAL(clicked()),this,SLOT(updateUi()));
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

    connect(resultTable, SIGNAL(clicked(const QModelIndex&)),
                this, SLOT(selectionChanged()));
    connect(resultTable->selectionModel(),
                SIGNAL(currentChanged(const QModelIndex&,
                                      const QModelIndex&)),
                this, SLOT(selectionChanged()));

    connect(resultTable->horizontalHeader(),
                SIGNAL(sectionClicked(int)),
                resultTable, SLOT(sortByColumn(int)));
}

void FindDialog::updateUi()
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

void FindDialog::restoreFilters()
{
    proxyModel->setStudent(box1->isChecked()
                ? lineStudent->currentText() : QString());
}

void FindDialog::restoreFilters2()
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

void FindDialog::restoreFilters3()
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

void FindDialog::restoreFilters4()
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

