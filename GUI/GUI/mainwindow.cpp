#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "main.cpp"
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->SpeedDial = findChild<QDial*>("SpeedDial");

    ui->SpeedBox = findChild<QSpinBox*>("SpeedBox");

    ui->KeyDrop = findChild<QComboBox*>("KeyDrop");

    ui->KeySlide = findChild<QSlider*>("KeySlide");

    ui->Output = findChild<QLabel*>("Output");

    ui->MinuteBox = findChild<QSpinBox*>("MinuteBox");

    ui->MeasureBox = findChild<QSpinBox*>("MeasureBox");

    setWindowTitle(tr("MusicAI"));

}

void MainWindow::on_SpeedDial_valueChanged(int value)
{
    ui->SpeedBox->setValue(value);
}

void MainWindow::on_SpeedBox_valueChanged(int value)
{
    ui->SpeedDial->setValue(value);
    updateMeasures(ui->MinuteCheck->isChecked());
}

void MainWindow::on_KeySlide_valueChanged(int tick)
{
    ui->KeyDrop->setCurrentIndex(tick);
    updateMeasures(ui->MinuteCheck->isChecked());
}
void MainWindow::on_KeyDrop_activated(int index)
{
    ui->KeySlide->setValue(index);
    updateMeasures(ui->MinuteCheck->isChecked());
}

void MainWindow::on_TimeBox_valueChanged()
{
    updateMeasures(ui->MinuteCheck->isChecked());
}

void MainWindow::on_MinuteCheck_toggled(bool checked)
{
    updateMeasures(ui->MinuteCheck->isChecked());
    if(checked)
    {
        ui->MinuteBox->setEnabled(true);
        ui->MeasureBox->setEnabled(false);
    }
    else
    {
        ui->MinuteBox->setEnabled(false);
        ui->MeasureBox->setEnabled(true);
    }
}

void MainWindow::on_MinuteBox_valueChanged()
{
    updateMeasures(ui->MinuteCheck->isChecked());
}

void MainWindow::updateMeasures(bool checked)
{
    if(checked)
    {
        int bpm = ui->SpeedBox->value();
        int time = ui->TimeBox->value();
        int mins = ui->MinuteBox->value();
        ui->MeasureBox->setValue(bpm/time*mins);
    }

}

void MainWindow::on_StartBut_clicked()
{
    stop();
    int beats = ui->SpeedBox->value();
    int time = ui->TimeBox->value();
    int measures = ui->MeasureBox->value();
    QString key = ui->KeyDrop->currentText();

    QString out = key + "\t" + QString::number(measures) + "\t" + QString::number(beats) + "\t" + QString::number(time);

    ui->Output->setText(out);

    string argString = "cd .. && cd .. && cd .. && cd chordgen && python midiplayer.py -k " + key.toStdString() + " -l " + std::to_string(measures) + " -t " + std::to_string(beats) + " -b " + std::to_string(time);
    //string argString = "cd .. && cd .. && cd .. && dir > ./out.txt";
    cout << argString << endl;
    system(argString.c_str());
}

void MainWindow::on_StopBut_clicked()
{
    stop();
}

void MainWindow::stop()
{
    ui->Output->setText("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

