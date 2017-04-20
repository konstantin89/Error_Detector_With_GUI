#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>

#include "../ErrorDetector/Error_Detector/LogModule.h"
#include "../ErrorDetector/Error_Detector/TestParameters.h"
#include <iostream>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_nextButton1_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_playButton_clicked();

    void on_speed_checkBox_stateChanged(int arg1);

    void on_Button_startCalib_clicked();

    void on_pushButton_stop_clicked();



private:
    Ui::MainWindow *ui;
    bool speedChange = false;
    bool sizeChange = false;
    bool directionChange = false;
    TestParameters testParams;
    QString userName = "";
    bool saveSettings();
    void updateFields();
    void setUIParams();
    void setFileParams();

};

#endif // MAINWINDOW_H
