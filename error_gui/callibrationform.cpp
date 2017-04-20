#include "callibrationform.h"
#include "ui_callibrationform.h"


#include <vector>
#include <chrono>
#include <thread>

#include<iostream>

CallibrationFrom::CallibrationFrom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CallibrationFrom)
{
    ui->setupUi(this);
}

CallibrationFrom::~CallibrationFrom()
{
    delete ui;
}

void CallibrationFrom::on_pushButton_starCalib_clicked()
{
    ui->label->text() = "sdfsd";
    //ui->progressBar_calib->

    std::vector<std::string> calibCommands;
    calibCommands.push_back(std::string("Press Up"));
    calibCommands.push_back(std::string("Press Down"));
    calibCommands.push_back(std::string("Press Left"));
    calibCommands.push_back(std::string("Press Right"));

    int sampleCounter = 0;
    int sampleSum = 0;
    for(std::string command : calibCommands)
    {
        ui->label->setText(command.c_str());
        sampleSum = 0;

        std::string calibProcCommand("../ErrorDetector/ObjsAndExecs/joysticCalibration 120 40000");
        auto calibProc = popen(calibProcCommand.c_str(), "r");
        {
            if(!calibProc)
            {
                std::cout << "Failed to open calibration proc." << std::endl;
            }
        }

        for(sampleCounter = 1; sampleCounter <= 100; sampleCounter++)
        {
           char buf[50];
           if( fgets(buf, sizeof(buf), calibProc) != NULL)
           {
               std::string str(buf, 49);
               //std::cout << str << std::endl;

                auto index = str.find_first_of("\n");
                std::string samples = str.substr(0,index);
                std::cout << samples << std::endl;
           }

            std::this_thread::sleep_for(std::chrono::milliseconds(4*10));
            ui->progressBar_calib->setValue(sampleCounter);
        }
        fclose(calibProc);
    }
    /*CHECK FOR ERROR IN VALUES*/
    ui->label->setText("Calibration Done");

}
