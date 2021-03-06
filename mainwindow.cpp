#include <QtWidgets>

#include "mainwindow.h"
#include "globj.h"

MainWindow::MainWindow()
{
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    globj = new GLobj(this);

    createWindow();
    createActions();
    createMenus();
    createInfoLabel();
    createFormGoupBox();
    createChecksGroupBox();
    createDisplayFormGroupBox();

//    QWidget *topFiller = new QWidget;
//    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//    QWidget *bottomFiller = new QWidget;
//    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

/*
 * Main layout construct
 *
 */
    QHBoxLayout *hlayout1 = new QHBoxLayout;
    hlayout1->addWidget(replaceGroupBox);
    hlayout1->addWidget(cacheGroupBox);
    hlayout1->addWidget(formGroupBox);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(15);
    layout->addWidget(infoLabel);
//    layout->addWidget(topFiller);
//    layout->addWidget(bottomFiller);
    layout->addLayout(hlayout1);
    layout->addWidget(displayGroupBox);
    layout->addWidget(globj);
    widget->setLayout(layout);
}

#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU

/*
 * Creates the window with parameters.
 *
 */
void MainWindow::createWindow()
{
    setWindowTitle(tr("Assignment I3"));
    setMinimumSize(300, 300);
    resize(500, 800);

    QString message = tr("Cache simulator ready");
    statusBar()->showMessage(message);

}

/*
 * Creates the user actions contained in the menu bar.
 *
 */
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


/*
 * Creates the menu bar that holds corresponding actions
 *
 */
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


/*
 * Creates message at the top of the interface that informs the user
 * of their interactions
 *
 */
void MainWindow:: createInfoLabel()
{
    infoLabel = new QLabel(tr("<i>Choose a menu option, or fill-in required"
                              " inputs</i>"));
    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setAlignment(Qt::AlignCenter);
    infoLabel->setMaximumHeight(20);
}

/*
 * Creates format for policy and
 */
void MainWindow::createChecksGroupBox()
{
    checkbox1 = new QCheckBox("LRU");
    checkbox2 = new QCheckBox("LFU");
    checkbox3 = new QCheckBox("Random");

    button1 = new QRadioButton("Instruction");
    button2 = new QRadioButton("Data");

    replaceGroupBox = new QGroupBox(tr("Replacement Policies:"));
    QButtonGroup *boxGroup = new QButtonGroup;
    boxGroup->addButton(checkbox1);
    boxGroup->addButton(checkbox2);
    boxGroup->addButton(checkbox3);
    boxGroup->setExclusive(true);
    QVBoxLayout *boxLayout = new QVBoxLayout;
    boxLayout->addWidget(checkbox1);
    boxLayout->addWidget(checkbox2);
    boxLayout->addWidget(checkbox3);
    replaceGroupBox->setLayout(boxLayout);

    cacheGroupBox = new QGroupBox(tr("Cache Type:"));
    QButtonGroup *buttonGroup = new QButtonGroup;
    buttonGroup->addButton(button1);
    buttonGroup->addButton(button2);
    buttonGroup->setExclusive(true);
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(button1);
    buttonLayout->addWidget(button2);
    cacheGroupBox->setLayout(buttonLayout);

    checkbox1->setCheckable(true);
    checkbox2->setCheckable(true);
    checkbox3->setCheckable(true);
    button1->setCheckable(true);
    button1->setText("Instruction");
    button2->setCheckable(true);
    button2->setText("Data");

}


/*
 * Should consider changing to grid layout in real-life application. Used form
 * layout here for educational purposes
 *
 */
void MainWindow::createFormGoupBox()
{
    memLabel = new QLabel("Size of main memory (in powers of two):");
    memDial = new QDial();
    memSpinBox = new QSpinBox();

    memSpinBox->setRange(256, 268435456);
    memSpinBox->setSingleStep(4);
    memSpinBox->setMinimumWidth(167);
    memSpinBox->setMaximumWidth(167);
    memDial->setRange(256, 268435456);
    memDial->setSingleStep(1);
    memDial->setMinimumWidth(50);
    memDial->setMaximumWidth(50);

    QHBoxLayout *memLayout = new QHBoxLayout;
    memLayout->addWidget(memDial);
    memLayout->addWidget(memSpinBox);

    connect(memSpinBox, SIGNAL(valueChanged(int)),
                     memDial, SLOT(setValue(int)));
    connect(memDial, SIGNAL(valueChanged(int)),
                     memSpinBox, SLOT(setValue(int)));

    formGroupBox = new QGroupBox(tr("Inputs:"));
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(memLabel);
    formLayout->addRow(memLayout);
    formLayout->addRow("Number of Sets:", new QSpinBox);
    formLayout->addRow("Number of Ways:", new QSpinBox);
    formLayout->addRow("Number of Bytes (per block)", new QSpinBox);
    formGroupBox->setLayout(formLayout);
}


/*
 * Creates the output display
 *
 */
void MainWindow::createDisplayFormGroupBox()
{
    display1 = new QLCDNumber(2);
    display2 = new QLCDNumber(2);
    display3 = new QLCDNumber(2);
    display4 = new QLCDNumber(2);

    displayGroupBox = new QGroupBox(tr("Displays:"));
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("Size of a reference word (in bits):", display1);
    formLayout->addRow(" ", new QLabel);
    formLayout->addRow("Size of the offset field (in bits):", display2);
    formLayout->addRow(" ", new QLabel);
    formLayout->addRow("Size of the index field (in bits):", display3);
    formLayout->addRow(" ", new QLabel);
    formLayout->addRow("Size of the tag field (in bits):", display4);
    formLayout->addRow(" ", new QLabel);

    displayGroupBox->setLayout(formLayout);
}


/*
 * Reading file in until end of file.
 *
 */
void MainWindow::readFile()
{
        infoLabel->setText(tr("Invoked <b>File|Open</b>"));
        QString filename = "trace.txt";
        QString path = QDir::currentPath();
        QFile file("//Users//nathan1324//Desktop//trace.txt");
        if(!file.exists()){
            qDebug() << "File cannot be found "<<filename;
            qDebug() << " " << path;
            return;
        }

        QString line;
        textEdit->clear();
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug() << "Could not open file" << filename;
            return;
        }

        qDebug() << filename<<" Opening...";

        QTextStream stream(&file);

        while (!stream.atEnd()) {
            line = stream.readLine();
            if(!line.isNull()){
                textEdit->append("0x"+line);
                qDebug() << "line: "<<line;
            }
        }
        file.close();
}

void MainWindow::newFile()
{
    infoLabel->setText(tr("Invoked <b>File|New</b>"));
}


/*
 * Action for 'File|Open'. The interface feedback will reflect the interaction
 * and a file will be sought after to open and read in.
 *
 */
void MainWindow::open()
{
    infoLabel->setText(tr("Invoked <b>File|Open</b>"));
    readFile();
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
