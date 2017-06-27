#include <QtWidgets>

#include "mainwindow.h"

MainWindow::MainWindow()
{
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    createWindow();
    createActions();
    createMenus();
    createInfoLabel();
    createFormGoupBox();
    //createOutputFormGroupBox();

//    QWidget *topFiller = new QWidget;
//    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    memLabel = new QLabel("Size of main memory (in powers of two):");
    replacementLabel = new QLabel("Replacement Policies:");
    cacheLabel = new QLabel("Cache Type:");
    setLabel = new QLabel("Number of Sets:");
    waysLabel = new QLabel("Number of Ways:");
    bytesLabel = new QLabel("Number of Bytes Per Block:");
    refWordLabel = new QLabel("Size of a reference word (in bits):");
    offsetLabel = new QLabel("Size of the offset field (in bits):");
    indexLabel = new QLabel("Size of the index field (in bits):");
    tagLabel = new QLabel("Size of the tag field (in bits):");
    memSpinBox = new QSpinBox();
    byteSpinBox = new QSpinBox();
    setsSpinBox = new QSpinBox();
    waysSpinBox = new QSpinBox();
    checkbox1 = new QCheckBox("LRU",widget);
    checkbox2 = new QCheckBox("LFU",widget);
    checkbox3 = new QCheckBox("Random", widget);
    button1 = new QRadioButton("Instruction", widget);
    button2 = new QRadioButton("Data", widget);
    display1 = new QLCDNumber(2);
    display2 = new QLCDNumber(2);
    display3 = new QLCDNumber(2);
    display4 = new QLCDNumber(2);
    textEdit = new QTextEdit();
    memDial = new QDial(widget);

    textEdit->setPlainText(tr("This widget takes file (File|Open)"));
    checkbox1->setCheckable(true);
    checkbox2->setCheckable(true);
    checkbox3->setCheckable(true);
    button1->setCheckable(true);
    button1->setText("Instruction");
    button2->setCheckable(true);
    button2->setText("Data");

    memSpinBox->setRange(256, 268435456);
    QObject::connect(memSpinBox, SIGNAL(valueChanged(int)),
                     memDial, SLOT(setValue(int)));
    QObject::connect(memDial, SIGNAL(valueChanged(int)),
                     memSpinBox, SLOT(setValue(int)));

    byteSpinBox->setRange(2, 1024);
    byteSpinBox->setSuffix(" bytes per block");
    byteSpinBox->setValue(4);
    byteSpinBox->setSingleStep(2);

    setsSpinBox->setRange(0,50);
    //setsSpinBox->setWrapping(true);
    setsSpinBox->setValue(0);
    waysSpinBox->setRange(0,50);
    //waysSpinBox->setWrapping(true);
    waysSpinBox->setValue(0);

    QButtonGroup *boxGroup = new QButtonGroup;
    boxGroup->addButton(checkbox1);
    boxGroup->addButton(checkbox2);
    boxGroup->addButton(checkbox3);
    boxGroup->setExclusive(true);
    QHBoxLayout *boxLayout = new QHBoxLayout;
    boxLayout->addWidget(checkbox1);
    boxLayout->addWidget(checkbox2);
    boxLayout->addWidget(checkbox3);

    QButtonGroup *buttonGroup = new QButtonGroup;
    buttonGroup->addButton(button1);
    buttonGroup->addButton(button2);
    buttonGroup->setExclusive(true);
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(button1);
    buttonLayout->addWidget(button2);

//    QWidget *bottomFiller = new QWidget;
//    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *hLayout = new QVBoxLayout;
    hLayout->setMargin(5);
    hLayout->addWidget(refWordLabel);
    hLayout->addWidget(display1);
    hLayout->addWidget(offsetLabel);
    hLayout->addWidget(display2);
    hLayout->addWidget(indexLabel);
    hLayout->addWidget(display3);
    hLayout->addWidget(tagLabel);
    hLayout->addWidget(display4);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(5);
    layout->addWidget(infoLabel);
//    layout->addWidget(topFiller);
//    layout->addWidget(bottomFiller);
    layout->addWidget(textEdit);
    layout->addWidget(replacementLabel);
    layout->addLayout(boxLayout);
    layout->addWidget(cacheLabel);
    layout->addLayout(buttonLayout);
    layout->addWidget(memLabel);
    layout->addWidget(memDial);
    layout->addWidget(memSpinBox);
//    layout->addWidget(setLabel);
//    layout->addWidget(setsSpinBox);
//    layout->addWidget(waysLabel);
//    layout->addWidget(waysSpinBox);
//    layout->addWidget(bytesLabel);
//    layout->addWidget(byteSpinBox);
    layout->addWidget(formGroupBox);
    layout->addLayout(hLayout);
    widget->setLayout(layout);
}

#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU

void MainWindow::createWindow()
{
//    QWidget *window = new QWidget;
//    window->setWindowTitle("Assignment I2");

    setWindowTitle(tr("Assignment I2"));
    setMinimumSize(300, 300);
    resize(500, 800);

    QString message = tr("Cache simulator ready");
    statusBar()->showMessage(message);

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

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    aboutAct = new QAction(tr("&Help"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

    startAct = new QAction(tr("&Start"), this);
    startAct->setStatusTip(tr("Start application"));
    connect(startAct, &QAction::triggered, this, &MainWindow::start);

    goAct = new QAction(tr("&Go"), this);
    goAct->setStatusTip(tr("Go application"));
    connect(goAct, &QAction::triggered, this, &MainWindow::go);

    stepAct = new QAction(tr("&Step S"), this);
    stepAct->setStatusTip(tr("Start application until step S"));
    connect(stepAct, &QAction::triggered, this, &MainWindow::stepS);

    breakAct = new QAction(tr("&Break B"), this);
    breakAct->setStatusTip(tr("Break application at step B"));
    connect(breakAct, &QAction::triggered, this, &MainWindow::breakB);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    functionMenu = menuBar()->addMenu(tr("&Function"));
    functionMenu->addAction(startAct);
    functionMenu->addAction(goAct);
    functionMenu->addAction(stepAct);
    functionMenu->addAction(breakAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}

void MainWindow:: createInfoLabel()
{
    infoLabel = new QLabel(tr("<i>Choose a menu option, or fill-in required"
                              " inputs</i>"));
    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setAlignment(Qt::AlignCenter);
}

void MainWindow::createFormGoupBox()
{
    formGroupBox = new QGroupBox(tr(""));
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("Number of Sets:", new QSpinBox);
    formLayout->addRow("Number of Ways:", new QSpinBox);
    formLayout->addRow("Number of Bytes (per block)", new QSpinBox);
    formGroupBox->setLayout(formLayout);
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

void MainWindow::go()
{
    infoLabel->setText(tr("Invoked <b>Function|Go</b>"));
}

void MainWindow::start()
{
    infoLabel->setText(tr("Invoked <b>Function|Start</b>"));
}

void MainWindow::stepS()
{
    infoLabel->setText(tr("Invoked <b>Function|Step S</b>"));
}

void MainWindow::breakB()
{
    infoLabel->setText(tr("Invoked <b>Function|Break B</b>"));
}

void MainWindow::about()
{
    infoLabel->setText(tr("Invoked <b>Help|About</b>"));
    QMessageBox::about(this, tr("Help"),
            tr("The <b>Menu</b> example demonstrates <i>help</i> was clicked."));
}
