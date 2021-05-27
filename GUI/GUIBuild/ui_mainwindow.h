/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *SpeedGroup;
    QDial *SpeedDial;
    QSpinBox *SpeedBox;
    QGroupBox *KeyGroup;
    QSlider *KeySlide;
    QGroupBox *KeyLables;
    QLabel *D;
    QLabel *Eb;
    QLabel *Gb;
    QLabel *F;
    QLabel *G;
    QLabel *Ab;
    QLabel *E;
    QLabel *A;
    QLabel *C;
    QLabel *Db;
    QLabel *Bb;
    QLabel *B;
    QComboBox *KeyDrop;
    QGroupBox *LengthGroup;
    QSpinBox *MinuteBox;
    QSpinBox *MeasureBox;
    QLabel *Measures;
    QLabel *Minutes;
    QCheckBox *MinuteCheck;
    QGroupBox *TimeGroup;
    QSpinBox *TimeBox;
    QLabel *Time;
    QGroupBox *ButtonGroup;
    QPushButton *StartBut;
    QPushButton *StopBut;
    QGroupBox *groupBox;
    QLabel *Output;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QStatusBar *statusbar;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(600, 300);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        SpeedGroup = new QGroupBox(centralwidget);
        SpeedGroup->setObjectName(QString::fromUtf8("SpeedGroup"));
        SpeedGroup->setGeometry(QRect(0, 0, 150, 200));
        SpeedDial = new QDial(SpeedGroup);
        SpeedDial->setObjectName(QString::fromUtf8("SpeedDial"));
        SpeedDial->setGeometry(QRect(15, 20, 120, 130));
        SpeedDial->setMinimum(30);
        SpeedDial->setMaximum(240);
        SpeedDial->setValue(60);
        SpeedDial->setNotchTarget(2.000000000000000);
        SpeedDial->setNotchesVisible(true);
        SpeedBox = new QSpinBox(SpeedGroup);
        SpeedBox->setObjectName(QString::fromUtf8("SpeedBox"));
        SpeedBox->setGeometry(QRect(55, 160, 40, 25));
        SpeedBox->setMinimum(30);
        SpeedBox->setMaximum(240);
        SpeedBox->setValue(60);
        KeyGroup = new QGroupBox(centralwidget);
        KeyGroup->setObjectName(QString::fromUtf8("KeyGroup"));
        KeyGroup->setGeometry(QRect(150, 0, 150, 200));
        KeySlide = new QSlider(KeyGroup);
        KeySlide->setObjectName(QString::fromUtf8("KeySlide"));
        KeySlide->setGeometry(QRect(10, 18, 20, 175));
        KeySlide->setMaximum(11);
        KeySlide->setOrientation(Qt::Vertical);
        KeySlide->setInvertedAppearance(false);
        KeySlide->setInvertedControls(false);
        KeyLables = new QGroupBox(KeyGroup);
        KeyLables->setObjectName(QString::fromUtf8("KeyLables"));
        KeyLables->setEnabled(true);
        KeyLables->setGeometry(QRect(40, 16, 20, 175));
        KeyLables->setAutoFillBackground(false);
        KeyLables->setTitle(QString::fromUtf8(""));
        KeyLables->setFlat(true);
        KeyLables->setCheckable(false);
        D = new QLabel(KeyLables);
        D->setObjectName(QString::fromUtf8("D"));
        D->setGeometry(QRect(0, 135, 18, 10));
        Eb = new QLabel(KeyLables);
        Eb->setObjectName(QString::fromUtf8("Eb"));
        Eb->setGeometry(QRect(0, 120, 18, 10));
        Gb = new QLabel(KeyLables);
        Gb->setObjectName(QString::fromUtf8("Gb"));
        Gb->setGeometry(QRect(0, 75, 18, 10));
        F = new QLabel(KeyLables);
        F->setObjectName(QString::fromUtf8("F"));
        F->setGeometry(QRect(0, 90, 18, 10));
        G = new QLabel(KeyLables);
        G->setObjectName(QString::fromUtf8("G"));
        G->setGeometry(QRect(0, 60, 18, 10));
        Ab = new QLabel(KeyLables);
        Ab->setObjectName(QString::fromUtf8("Ab"));
        Ab->setGeometry(QRect(0, 45, 18, 10));
        E = new QLabel(KeyLables);
        E->setObjectName(QString::fromUtf8("E"));
        E->setGeometry(QRect(0, 105, 18, 10));
        A = new QLabel(KeyLables);
        A->setObjectName(QString::fromUtf8("A"));
        A->setGeometry(QRect(0, 30, 18, 10));
        C = new QLabel(KeyLables);
        C->setObjectName(QString::fromUtf8("C"));
        C->setGeometry(QRect(0, 165, 18, 9));
        Db = new QLabel(KeyLables);
        Db->setObjectName(QString::fromUtf8("Db"));
        Db->setGeometry(QRect(0, 150, 18, 10));
        Bb = new QLabel(KeyLables);
        Bb->setObjectName(QString::fromUtf8("Bb"));
        Bb->setGeometry(QRect(0, 15, 18, 10));
        B = new QLabel(KeyLables);
        B->setObjectName(QString::fromUtf8("B"));
        B->setGeometry(QRect(0, 0, 18, 10));
        KeyDrop = new QComboBox(KeyGroup);
        KeyDrop->addItem(QString());
        KeyDrop->addItem(QString());
        KeyDrop->addItem(QString());
        KeyDrop->addItem(QString());
        KeyDrop->addItem(QString());
        KeyDrop->addItem(QString());
        KeyDrop->addItem(QString());
        KeyDrop->addItem(QString());
        KeyDrop->addItem(QString());
        KeyDrop->addItem(QString());
        KeyDrop->addItem(QString());
        KeyDrop->addItem(QString());
        KeyDrop->setObjectName(QString::fromUtf8("KeyDrop"));
        KeyDrop->setGeometry(QRect(85, 90, 40, 20));
        LengthGroup = new QGroupBox(centralwidget);
        LengthGroup->setObjectName(QString::fromUtf8("LengthGroup"));
        LengthGroup->setGeometry(QRect(450, 0, 150, 200));
        MinuteBox = new QSpinBox(LengthGroup);
        MinuteBox->setObjectName(QString::fromUtf8("MinuteBox"));
        MinuteBox->setEnabled(false);
        MinuteBox->setGeometry(QRect(20, 80, 50, 20));
        MinuteBox->setMinimum(1);
        MinuteBox->setMaximum(120);
        MinuteBox->setValue(1);
        MeasureBox = new QSpinBox(LengthGroup);
        MeasureBox->setObjectName(QString::fromUtf8("MeasureBox"));
        MeasureBox->setGeometry(QRect(20, 140, 50, 20));
        MeasureBox->setMinimum(10);
        MeasureBox->setMaximum(10000);
        Measures = new QLabel(LengthGroup);
        Measures->setObjectName(QString::fromUtf8("Measures"));
        Measures->setGeometry(QRect(80, 140, 61, 20));
        QFont font;
        font.setPointSize(9);
        Measures->setFont(font);
        Minutes = new QLabel(LengthGroup);
        Minutes->setObjectName(QString::fromUtf8("Minutes"));
        Minutes->setGeometry(QRect(80, 80, 47, 20));
        Minutes->setFont(font);
        MinuteCheck = new QCheckBox(LengthGroup);
        MinuteCheck->setObjectName(QString::fromUtf8("MinuteCheck"));
        MinuteCheck->setGeometry(QRect(25, 40, 100, 20));
        TimeGroup = new QGroupBox(centralwidget);
        TimeGroup->setObjectName(QString::fromUtf8("TimeGroup"));
        TimeGroup->setGeometry(QRect(300, 0, 150, 200));
        TimeBox = new QSpinBox(TimeGroup);
        TimeBox->setObjectName(QString::fromUtf8("TimeBox"));
        TimeBox->setGeometry(QRect(35, 90, 40, 20));
        TimeBox->setMinimum(2);
        TimeBox->setMaximum(16);
        TimeBox->setValue(4);
        Time = new QLabel(TimeGroup);
        Time->setObjectName(QString::fromUtf8("Time"));
        Time->setGeometry(QRect(80, 90, 40, 20));
        QFont font1;
        font1.setPointSize(12);
        Time->setFont(font1);
        ButtonGroup = new QGroupBox(centralwidget);
        ButtonGroup->setObjectName(QString::fromUtf8("ButtonGroup"));
        ButtonGroup->setGeometry(QRect(200, 210, 200, 50));
        StartBut = new QPushButton(ButtonGroup);
        StartBut->setObjectName(QString::fromUtf8("StartBut"));
        StartBut->setGeometry(QRect(0, 0, 100, 50));
        StopBut = new QPushButton(ButtonGroup);
        StopBut->setObjectName(QString::fromUtf8("StopBut"));
        StopBut->setGeometry(QRect(100, 0, 100, 50));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(5, 210, 191, 50));
        Output = new QLabel(groupBox);
        Output->setObjectName(QString::fromUtf8("Output"));
        Output->setGeometry(QRect(0, 20, 191, 13));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 21, 13));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(25, 0, 47, 13));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(90, 0, 21, 13));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(140, 0, 21, 13));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 600, 21));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        SpeedGroup->setTitle(QCoreApplication::translate("MainWindow", "Speed", nullptr));
        KeyGroup->setTitle(QCoreApplication::translate("MainWindow", "Key", nullptr));
        D->setText(QCoreApplication::translate("MainWindow", "D", nullptr));
        Eb->setText(QCoreApplication::translate("MainWindow", "Eb", nullptr));
        Gb->setText(QCoreApplication::translate("MainWindow", "Gb", nullptr));
        F->setText(QCoreApplication::translate("MainWindow", "F", nullptr));
        G->setText(QCoreApplication::translate("MainWindow", "G", nullptr));
        Ab->setText(QCoreApplication::translate("MainWindow", "Ab", nullptr));
        E->setText(QCoreApplication::translate("MainWindow", "E", nullptr));
        A->setText(QCoreApplication::translate("MainWindow", "A", nullptr));
        C->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        Db->setText(QCoreApplication::translate("MainWindow", "Db", nullptr));
        Bb->setText(QCoreApplication::translate("MainWindow", "Bb", nullptr));
        B->setText(QCoreApplication::translate("MainWindow", "B", nullptr));
        KeyDrop->setItemText(0, QCoreApplication::translate("MainWindow", "C", nullptr));
        KeyDrop->setItemText(1, QCoreApplication::translate("MainWindow", "Db", nullptr));
        KeyDrop->setItemText(2, QCoreApplication::translate("MainWindow", "D", nullptr));
        KeyDrop->setItemText(3, QCoreApplication::translate("MainWindow", "Eb", nullptr));
        KeyDrop->setItemText(4, QCoreApplication::translate("MainWindow", "E", nullptr));
        KeyDrop->setItemText(5, QCoreApplication::translate("MainWindow", "F", nullptr));
        KeyDrop->setItemText(6, QCoreApplication::translate("MainWindow", "Gb", nullptr));
        KeyDrop->setItemText(7, QCoreApplication::translate("MainWindow", "G", nullptr));
        KeyDrop->setItemText(8, QCoreApplication::translate("MainWindow", "Ab", nullptr));
        KeyDrop->setItemText(9, QCoreApplication::translate("MainWindow", "A", nullptr));
        KeyDrop->setItemText(10, QCoreApplication::translate("MainWindow", "Bb", nullptr));
        KeyDrop->setItemText(11, QCoreApplication::translate("MainWindow", "B", nullptr));

        LengthGroup->setTitle(QCoreApplication::translate("MainWindow", "Length", nullptr));
        Measures->setText(QCoreApplication::translate("MainWindow", "Measures", nullptr));
        Minutes->setText(QCoreApplication::translate("MainWindow", "Minutes", nullptr));
        MinuteCheck->setText(QCoreApplication::translate("MainWindow", "Play for Minutes", nullptr));
        TimeGroup->setTitle(QCoreApplication::translate("MainWindow", "Time Signature", nullptr));
        Time->setText(QCoreApplication::translate("MainWindow", "/4", nullptr));
        ButtonGroup->setTitle(QString());
        StartBut->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        StopBut->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        groupBox->setTitle(QString());
        Output->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "Key", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Measures", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "BPM", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Time", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
