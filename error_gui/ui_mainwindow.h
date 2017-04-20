/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab_hello;
    QPlainTextEdit *plainTextEdit;
    QPushButton *nextButton1;
    QWidget *tab_option_menu;
    QFrame *frame;
    QGridLayout *gridLayout_6;
    QLabel *label_2;
    QPushButton *pushButton_stop;
    QPushButton *playButton;
    QGroupBox *groupBox;
    QLabel *label;
    QLineEdit *user_name_field;
    QGroupBox *groupBox_3;
    QCheckBox *speed_checkBox;
    QCheckBox *direction_checkBox;
    QCheckBox *size_checkBox;
    QWidget *tab_calib;
    QGroupBox *groupBox_2;
    QPlainTextEdit *plainTextEdit_2;
    QPushButton *Button_startCalib;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1175, 604);
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        MainWindow->setAutoFillBackground(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setProperty("tabBarAutoHide", QVariant(true));
        tab_hello = new QWidget();
        tab_hello->setObjectName(QString::fromUtf8("tab_hello"));
        plainTextEdit = new QPlainTextEdit(tab_hello);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(9, 9, 681, 261));
        QFont font;
        font.setPointSize(14);
        plainTextEdit->setFont(font);
        plainTextEdit->setReadOnly(true);
        nextButton1 = new QPushButton(tab_hello);
        nextButton1->setObjectName(QString::fromUtf8("nextButton1"));
        nextButton1->setGeometry(QRect(260, 340, 85, 31));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(nextButton1->sizePolicy().hasHeightForWidth());
        nextButton1->setSizePolicy(sizePolicy1);
        nextButton1->setFocusPolicy(Qt::NoFocus);
        tabWidget->addTab(tab_hello, QString());
        tab_option_menu = new QWidget();
        tab_option_menu->setObjectName(QString::fromUtf8("tab_option_menu"));
        frame = new QFrame(tab_option_menu);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 1161, 481));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(5);
        sizePolicy2.setVerticalStretch(5);
        sizePolicy2.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy2);
        frame->setAutoFillBackground(true);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_6 = new QGridLayout(frame);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(500, -1, 0, 60);
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font1;
        font1.setPointSize(12);
        label_2->setFont(font1);

        gridLayout_6->addWidget(label_2, 3, 1, 1, 1);

        pushButton_stop = new QPushButton(frame);
        pushButton_stop->setObjectName(QString::fromUtf8("pushButton_stop"));

        gridLayout_6->addWidget(pushButton_stop, 7, 2, 1, 1);

        playButton = new QPushButton(frame);
        playButton->setObjectName(QString::fromUtf8("playButton"));
        playButton->setFocusPolicy(Qt::NoFocus);

        gridLayout_6->addWidget(playButton, 7, 1, 1, 1);

        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));

        gridLayout_6->addWidget(groupBox, 2, 1, 1, 1);

        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        gridLayout_6->addWidget(label, 1, 1, 1, 1);

        user_name_field = new QLineEdit(frame);
        user_name_field->setObjectName(QString::fromUtf8("user_name_field"));
        //user_name_field->setClearButtonEnabled(false);

        gridLayout_6->addWidget(user_name_field, 0, 2, 3, 1);

        groupBox_3 = new QGroupBox(frame);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setAlignment(Qt::AlignCenter);
        speed_checkBox = new QCheckBox(groupBox_3);
        speed_checkBox->setObjectName(QString::fromUtf8("speed_checkBox"));
        speed_checkBox->setGeometry(QRect(30, 30, 151, 17));
        speed_checkBox->setFont(font1);
        direction_checkBox = new QCheckBox(groupBox_3);
        direction_checkBox->setObjectName(QString::fromUtf8("direction_checkBox"));
        direction_checkBox->setGeometry(QRect(30, 50, 141, 17));
        direction_checkBox->setFont(font1);
        size_checkBox = new QCheckBox(groupBox_3);
        size_checkBox->setObjectName(QString::fromUtf8("size_checkBox"));
        size_checkBox->setGeometry(QRect(30, 70, 70, 17));
        size_checkBox->setFont(font1);

        gridLayout_6->addWidget(groupBox_3, 3, 2, 1, 1);

        tabWidget->addTab(tab_option_menu, QString());
        tab_calib = new QWidget();
        tab_calib->setObjectName(QString::fromUtf8("tab_calib"));
        groupBox_2 = new QGroupBox(tab_calib);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(0, 0, 601, 201));
        plainTextEdit_2 = new QPlainTextEdit(groupBox_2);
        plainTextEdit_2->setObjectName(QString::fromUtf8("plainTextEdit_2"));
        plainTextEdit_2->setGeometry(QRect(20, 40, 421, 131));
        Button_startCalib = new QPushButton(tab_calib);
        Button_startCalib->setObjectName(QString::fromUtf8("Button_startCalib"));
        Button_startCalib->setGeometry(QRect(570, 360, 121, 23));
        tabWidget->addTab(tab_calib, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1175, 27));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        plainTextEdit->setPlainText(QApplication::translate("MainWindow", "Hello, \n"
"welcome to the Error-Detector, \n"
"in the next window you will need to choose \n"
"the configuration for that session.\n"
"to continue click 'NEXT'. ", 0, QApplication::UnicodeUTF8));
        nextButton1->setText(QApplication::translate("MainWindow", "NEXT", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_hello), QApplication::translate("MainWindow", "Hello", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Choose your configurations:", 0, QApplication::UnicodeUTF8));
        pushButton_stop->setText(QApplication::translate("MainWindow", "STOP", 0, QApplication::UnicodeUTF8));
        playButton->setText(QApplication::translate("MainWindow", "play", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        label->setText(QApplication::translate("MainWindow", "Enter Your name please:", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "options", 0, QApplication::UnicodeUTF8));
        speed_checkBox->setText(QApplication::translate("MainWindow", "speed ", 0, QApplication::UnicodeUTF8));
        direction_checkBox->setText(QApplication::translate("MainWindow", "Direction", 0, QApplication::UnicodeUTF8));
        size_checkBox->setText(QApplication::translate("MainWindow", "Size", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_option_menu), QApplication::translate("MainWindow", "Coniguration", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QString());
        plainTextEdit_2->setPlainText(QApplication::translate("MainWindow", "KOSTA You are about to start a calibration operation -\n"
"Follow the orders on the screen.\n"
"To start hit the button below.!!!!!", 0, QApplication::UnicodeUTF8));
        Button_startCalib->setText(QApplication::translate("MainWindow", "Start calibration", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_calib), QApplication::translate("MainWindow", "Calibration", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
