/********************************************************************************
** Form generated from reading UI file 'callibrationform.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALLIBRATIONFORM_H
#define UI_CALLIBRATIONFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CallibrationFrom
{
public:
    QPushButton *pushButton_starCalib;
    QProgressBar *progressBar_calib;
    QLabel *label;

    void setupUi(QDialog *CallibrationFrom)
    {
        if (CallibrationFrom->objectName().isEmpty())
            CallibrationFrom->setObjectName(QString::fromUtf8("CallibrationFrom"));
        CallibrationFrom->resize(400, 300);
        pushButton_starCalib = new QPushButton(CallibrationFrom);
        pushButton_starCalib->setObjectName(QString::fromUtf8("pushButton_starCalib"));
        pushButton_starCalib->setGeometry(QRect(120, 220, 161, 31));
        progressBar_calib = new QProgressBar(CallibrationFrom);
        progressBar_calib->setObjectName(QString::fromUtf8("progressBar_calib"));
        progressBar_calib->setGeometry(QRect(70, 100, 321, 31));
        QFont font;
        font.setPointSize(22);
        progressBar_calib->setFont(font);
        progressBar_calib->setValue(0);
        label = new QLabel(CallibrationFrom);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(140, 40, 261, 51));
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);
        label->setLineWidth(10);

        retranslateUi(CallibrationFrom);

        QMetaObject::connectSlotsByName(CallibrationFrom);
    } // setupUi

    void retranslateUi(QDialog *CallibrationFrom)
    {
        CallibrationFrom->setWindowTitle(QApplication::translate("CallibrationFrom", "Dialog", 0, QApplication::UnicodeUTF8));
        pushButton_starCalib->setText(QApplication::translate("CallibrationFrom", "Start Calibration", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CallibrationFrom", "Push Start", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CallibrationFrom: public Ui_CallibrationFrom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALLIBRATIONFORM_H
