/*****************************************************************************
 * Nathan Easton
 * Assignment I1 -- June 16
 * CS 4379B.502
 * Dr. Tamir
 *
 * This program is the first part of an incremental semester long project
 * that is intended to establish basic understanding of creating software
 * interfaces directed towards optimal usability and user satisfaction.
 *
 * Assignment I1 will include implementing various Qt widgets to represent a
 * cache memory simulation. There will be many types of widgets that can
 * ultimately be categorized as input and output widgets. The goal of this
 * assignment is to begin placing both input and output widgets and establish
 * a connection between them.
 *
 ********************************************************************************/
#include <QtGui>
#include <QApplication>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QSlider>
#include <QSpinBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QLabel>

int main(int argc, char *argv[])
	{
		QApplication app(argc, argv);

                QWidget *window = new QWidget;
                window->setWindowTitle("Assignment I1");

                QWidget *centralWidget = new QWidget(window);

                QLabel *replacementLabel = new QLabel("Replacement Policies:");
                QLabel *cacheLabel = new QLabel("Cache Type:");
                QLabel *setLabel = new QLabel("Number of Sets:");
                QLabel *waysLabel = new QLabel("Number of Ways:");
                QLabel *bytesLabel = new QLabel("Number of Bytes Per Block:");
                QLabel *displaysLabel = new QLabel("Displays:");
                QLabel *simulationsLabel = new QLabel("Simulation Controls:");
                QSpinBox *spinBox = new QSpinBox();
                QSpinBox *setsSpinBox = new QSpinBox();
                QSpinBox *waysSpinBox = new QSpinBox();
                QSlider *slider = new QSlider(Qt::Horizontal);
                QCheckBox *checkbox1 = new QCheckBox("LRU",centralWidget);
                QCheckBox *checkbox2 = new QCheckBox("LFU",centralWidget);
                QCheckBox *checkbox3 = new QCheckBox("Random", centralWidget);
                QRadioButton *button1 = new QRadioButton("Instruction", centralWidget);
                QRadioButton *button2 = new QRadioButton("Data", centralWidget);


                checkbox1->setCheckable(true);
                checkbox2->setCheckable(true);
                checkbox3->setCheckable(true);
                button1->setCheckable(true);
                button1->setText("Instruction");
                button2->setCheckable(true);
                button2->setText("Data");

                spinBox->setRange(4, 1024);
                spinBox->setSuffix(" bytes per block");
                slider->setRange(4, 1024);
                QObject::connect(spinBox, SIGNAL(valueChanged(int)),
		slider, SLOT(setValue(int)));
                QObject::connect(slider, SIGNAL(valueChanged(int)),
		spinBox, SLOT(setValue(int)));
                spinBox->setValue(4);

                setsSpinBox->setRange(0,50);
                setsSpinBox->setWrapping(true);
                waysSpinBox->setRange(0,50);
                waysSpinBox->setWrapping(true);

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

                QVBoxLayout *layout = new QVBoxLayout;
                layout->addWidget(replacementLabel);
                layout->addLayout(boxLayout);
                layout->addWidget(cacheLabel);
                layout->addLayout(buttonLayout);
                layout->addWidget(setLabel);
                layout->addWidget(setsSpinBox);
                layout->addWidget(waysLabel);
                layout->addWidget(waysSpinBox);
                layout->addWidget(bytesLabel);
                layout->addWidget(spinBox);
		layout->addWidget(slider);
                layout->addWidget(displaysLabel);

                window->setLayout(layout);
		window->show();

		return app.exec();
      }
