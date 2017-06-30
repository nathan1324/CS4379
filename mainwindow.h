#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QSlider>
#include <QCheckBox>
#include <QRadioButton>
#include <QLCDNumber>
#include <QGroupBox>
#include <QTextEdit>
#include <QDial>

class QAction;
class QActionGroup;
class QLabel;
class QMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) override;
#endif // QT_NO_CONTEXTMENU

private slots:
    void newFile();
    void open();
    void save();
    void about();
    void start();
    void go();
    void stepS();
    void breakB();

private:
    void createActions();
    void createMenus();
    void createInfoLabel();
    void createWindow();
    void createFormGoupBox();
    void createChecksGroupBox();
    void createDisplayFormGroupBox();
    void readFile();

    QGroupBox *formGroupBox;
    QGroupBox *replaceGroupBox;
    QGroupBox *cacheGroupBox;
    QGroupBox *displayGroupBox;

    QMenu *fileMenu;
    QMenu *functionMenu;
    QMenu *helpMenu;

    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;
    QAction *aboutAct;
    QAction *startAct;
    QAction *goAct;
    QAction *stepAct;
    QAction *breakAct;

    QLabel *infoLabel;
    QLabel *memLabel;
    QLabel *replacementLabel;
    QLabel *cacheLabel;
    QLabel *bytesLabel;
    QLabel *setLabel;
    QLabel *refWordLabel;
    QLabel *offsetLabel;
    QLabel *indexLabel;
    QLabel *tagLabel;
    QLabel *waysLabel;

    QSpinBox *memSpinBox;
    QSpinBox *byteSpinBox;
    QSpinBox *setsSpinBox;
    QSpinBox *waysSpinBox;

    QCheckBox *checkbox1;
    QCheckBox *checkbox2;
    QCheckBox *checkbox3;

    QRadioButton *button1;
    QRadioButton *button2;

    QLCDNumber *display1;
    QLCDNumber *display2;
    QLCDNumber *display3;
    QLCDNumber *display4;

    QTextEdit *textEdit;

    QDial *memDial;
};

#endif
