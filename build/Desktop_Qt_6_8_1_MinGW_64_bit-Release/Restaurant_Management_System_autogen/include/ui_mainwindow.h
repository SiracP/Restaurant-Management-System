/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "clickablelabel.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *layoutMain;
    QFrame *frameSideBar;
    QVBoxLayout *layoutSideBar;
    ClickableLabel *labelNavTables;
    ClickableLabel *labelNavProducts;
    ClickableLabel *labelNavReports;
    QSpacerItem *spacer1;
    ClickableLabel *labelNavHome;
    QStackedWidget *stackedPages;
    QWidget *pageMenu;
    QVBoxLayout *layoutMenu;
    QLabel *labelWelcome;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        layoutMain = new QHBoxLayout(centralwidget);
        layoutMain->setObjectName("layoutMain");
        frameSideBar = new QFrame(centralwidget);
        frameSideBar->setObjectName("frameSideBar");
        frameSideBar->setFrameShape(QFrame::Shape::StyledPanel);
        layoutSideBar = new QVBoxLayout(frameSideBar);
        layoutSideBar->setObjectName("layoutSideBar");
        labelNavTables = new ClickableLabel(frameSideBar);
        labelNavTables->setObjectName("labelNavTables");
        labelNavTables->setAlignment(Qt::AlignmentFlag::AlignCenter);

        layoutSideBar->addWidget(labelNavTables);

        labelNavProducts = new ClickableLabel(frameSideBar);
        labelNavProducts->setObjectName("labelNavProducts");
        labelNavProducts->setAlignment(Qt::AlignmentFlag::AlignCenter);

        layoutSideBar->addWidget(labelNavProducts);

        labelNavReports = new ClickableLabel(frameSideBar);
        labelNavReports->setObjectName("labelNavReports");
        labelNavReports->setAlignment(Qt::AlignmentFlag::AlignCenter);

        layoutSideBar->addWidget(labelNavReports);

        spacer1 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        layoutSideBar->addItem(spacer1);

        labelNavHome = new ClickableLabel(frameSideBar);
        labelNavHome->setObjectName("labelNavHome");
        labelNavHome->setAlignment(Qt::AlignmentFlag::AlignCenter);

        layoutSideBar->addWidget(labelNavHome);


        layoutMain->addWidget(frameSideBar);

        stackedPages = new QStackedWidget(centralwidget);
        stackedPages->setObjectName("stackedPages");
        pageMenu = new QWidget();
        pageMenu->setObjectName("pageMenu");
        layoutMenu = new QVBoxLayout(pageMenu);
        layoutMenu->setObjectName("layoutMenu");
        labelWelcome = new QLabel(pageMenu);
        labelWelcome->setObjectName("labelWelcome");
        labelWelcome->setAlignment(Qt::AlignmentFlag::AlignCenter);

        layoutMenu->addWidget(labelWelcome);

        stackedPages->addWidget(pageMenu);

        layoutMain->addWidget(stackedPages);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        labelNavTables->setText(QCoreApplication::translate("MainWindow", "\360\237\252\221 Tables", nullptr));
        labelNavProducts->setText(QCoreApplication::translate("MainWindow", "\360\237\215\275 Products", nullptr));
        labelNavReports->setText(QCoreApplication::translate("MainWindow", "\360\237\223\212 Reports", nullptr));
        labelNavHome->setText(QCoreApplication::translate("MainWindow", "\360\237\217\240 Home", nullptr));
        labelWelcome->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 20px; color: #444;", nullptr));
        labelWelcome->setText(QString());
        (void)MainWindow;
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
