/********************************************************************************
** Form generated from reading UI file 'Simulator.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULATOR_H
#define UI_SIMULATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimulatorClass
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SimulatorClass)
    {
        if (SimulatorClass->objectName().isEmpty())
            SimulatorClass->setObjectName("SimulatorClass");
        SimulatorClass->resize(1468, 776);
        centralWidget = new QWidget(SimulatorClass);
        centralWidget->setObjectName("centralWidget");
        SimulatorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SimulatorClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1468, 22));
        SimulatorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SimulatorClass);
        mainToolBar->setObjectName("mainToolBar");
        SimulatorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SimulatorClass);
        statusBar->setObjectName("statusBar");
        SimulatorClass->setStatusBar(statusBar);

        retranslateUi(SimulatorClass);

        QMetaObject::connectSlotsByName(SimulatorClass);
    } // setupUi

    void retranslateUi(QMainWindow *SimulatorClass)
    {
        SimulatorClass->setWindowTitle(QCoreApplication::translate("SimulatorClass", "Simulator", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SimulatorClass: public Ui_SimulatorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULATOR_H
