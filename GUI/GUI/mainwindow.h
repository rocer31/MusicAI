#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_SpeedDial_valueChanged(int value);
    void on_SpeedBox_valueChanged(int value);
    void on_KeySlide_valueChanged(int value);
    void on_KeyDrop_activated(int value);
    void on_MinuteCheck_toggled(bool checked);
    void on_MinuteBox_valueChanged();
    void on_TimeBox_valueChanged();
    void updateMeasures(bool checked);
    void on_StartBut_clicked();
    void on_StopBut_clicked();
    void stop();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
