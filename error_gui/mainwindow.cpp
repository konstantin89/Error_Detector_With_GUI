#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "callibrationform.h"
#include <iostream>
#include <errno.h>
#include <string>

FILE* g_hErrorDetector = NULL;
std::string PARAM_FILE_NAME_STR("./Parameters");


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(TestParameters::paramFileExists(PARAM_FILE_NAME_STR.c_str()))
    {
         this->testParams.readParamsFromFile(PARAM_FILE_NAME_STR.c_str());
         setUIParams();
    }
    ui->tabWidget->setCurrentIndex(0);
    QDesktopWidget p;
    //QRect rec = //QApplication::desktop()screenGeometry();
    //this->setFixedSize(p.width(), p.height());
    this->resize(p.width(), p.height());
    p.hide();//
}

void MainWindow::setUIParams(){
    ui->user_name_field->insert((QString)testParams.playerName.c_str());
    ui->direction_checkBox->setChecked(testParams.directionChange);
    ui->size_checkBox->setChecked(testParams.rectSize);
    ui->speed_checkBox->setChecked(testParams.seedChange);
}

void MainWindow::setFileParams()
{

    testParams.playerName = ui->user_name_field->text().toStdString();
    testParams.directionChange = ui->direction_checkBox->checkState();
    testParams.rectSize = ui->size_checkBox->checkState();
    testParams.seedChange = ui->speed_checkBox->checkState();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_nextButton1_clicked()
{
    ui->tabWidget->setCurrentIndex(1);

}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    switch (arg1) {
    case 1:

        break;
    default:
        break;
    }
}

void MainWindow::on_playButton_clicked()
{
    //initial game
    MainWindow::updateFields();
    setFileParams();

    testParams.writeParamsToFile(PARAM_FILE_NAME_STR.c_str());
    std::cout << userName.toUtf8().constData() <<",speed: " << speedChange <<",dir: "<<directionChange<<
                 ", size: "<< sizeChange << std::endl;


    std::string runGameCommand;
    runGameCommand += "/home/pi/FinalProject/ErrorDetector/ObjsAndExecs/errorDetector";
    runGameCommand += " ";
    runGameCommand += std::string(userName.toUtf8().constData());
    runGameCommand += " ";
    runGameCommand += std::to_string(directionChange);
    runGameCommand += " ";
    runGameCommand += std::to_string(sizeChange);
    runGameCommand += " ";
    runGameCommand += std::to_string(speedChange);
    runGameCommand += " ";

    g_hErrorDetector = popen(runGameCommand.c_str(), "r");
    if(g_hErrorDetector == NULL)
    {
        std::cout << "Failed to start process" << std::endl;
        //std::cout << "Errno:" << errno << std::endl;
    }
    else
    {
        std::cout << "Error detector process running." << std::endl;

    }




}

void MainWindow::on_speed_checkBox_stateChanged(int arg1)
{
    speedChange = arg1;
}

bool MainWindow::saveSettings()
{
    MainWindow::updateFields();
    userName = ui->user_name_field->text();
    directionChange = ui->direction_checkBox->checkState();
    sizeChange = ui->size_checkBox->checkState();
    speedChange = ui->speed_checkBox->checkState();
}

void MainWindow::updateFields()
{
    userName = ui->user_name_field->text();
    directionChange = ui->direction_checkBox->checkState();
    sizeChange = ui->size_checkBox->checkState();
    speedChange = ui->speed_checkBox->checkState();
}

void MainWindow::on_Button_startCalib_clicked()
{
    CallibrationFrom cForm;
    cForm.setModal(true);
    cForm.exec();
}

void MainWindow::on_pushButton_stop_clicked()
{
     popen("kill -9 $(pidof errorDetector)", "r");
}
