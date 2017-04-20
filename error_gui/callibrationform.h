#ifndef CALLIBRATIONFROM_H
#define CALLIBRATIONFROM_H

#include <QDialog>
#include "./JoystickCalibrationFiles/JoystickCalib.h"


std::string CALIB_DATA_FILE("../Text_Data/JoystickCalibData");

namespace Ui {
class CallibrationFrom;
}

class CallibrationFrom : public QDialog
{
    Q_OBJECT

public:
    explicit CallibrationFrom(QWidget *parent = 0);
    ~CallibrationFrom();

private slots:
    void on_pushButton_starCalib_clicked();

private:
    Ui::CallibrationFrom *ui;
};

#endif // CALLIBRATIONFROM_H
