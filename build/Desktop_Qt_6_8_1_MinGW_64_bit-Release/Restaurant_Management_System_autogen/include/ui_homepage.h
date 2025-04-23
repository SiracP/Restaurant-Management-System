/********************************************************************************
** Form generated from reading UI file 'homepage.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOMEPAGE_H
#define UI_HOMEPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HomePage
{
public:
    QVBoxLayout *mainLayout;
    QFrame *headerFrame;
    QHBoxLayout *headerLayout;
    QLabel *labelRestaurantAutomation;
    QSpacerItem *horizontalSpacer;
    QLabel *labelDateTime;
    QGridLayout *summaryGrid;
    QFrame *frameDailySales;
    QVBoxLayout *vboxLayout;
    QLabel *titleDailySales;
    QLabel *valueDailySales;
    QFrame *frameActiveTables;
    QVBoxLayout *vboxLayout1;
    QLabel *titleActiveTables;
    QLabel *valueActiveTables;
    QFrame *frameTopProduct;
    QVBoxLayout *vboxLayout2;
    QLabel *titleTopProduct;
    QLabel *valueTopProduct;
    QHBoxLayout *contentLayout;
    QFrame *frameRecent;
    QVBoxLayout *vboxLayout3;
    QLabel *titleRecent;
    QListWidget *listRecent;
    QFrame *framePhoto;
    QVBoxLayout *vboxLayout4;
    QLabel *labelPhoto;
    QLabel *labelFooter;

    void setupUi(QWidget *HomePage)
    {
        if (HomePage->objectName().isEmpty())
            HomePage->setObjectName("HomePage");
        HomePage->resize(900, 650);
        HomePage->setMinimumSize(QSize(900, 650));
        mainLayout = new QVBoxLayout(HomePage);
        mainLayout->setObjectName("mainLayout");
        headerFrame = new QFrame(HomePage);
        headerFrame->setObjectName("headerFrame");
        headerLayout = new QHBoxLayout(headerFrame);
        headerLayout->setSpacing(20);
        headerLayout->setObjectName("headerLayout");
        labelRestaurantAutomation = new QLabel(headerFrame);
        labelRestaurantAutomation->setObjectName("labelRestaurantAutomation");

        headerLayout->addWidget(labelRestaurantAutomation);

        horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        headerLayout->addItem(horizontalSpacer);

        labelDateTime = new QLabel(headerFrame);
        labelDateTime->setObjectName("labelDateTime");
        labelDateTime->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        headerLayout->addWidget(labelDateTime);


        mainLayout->addWidget(headerFrame);

        summaryGrid = new QGridLayout();
        summaryGrid->setObjectName("summaryGrid");
        frameDailySales = new QFrame(HomePage);
        frameDailySales->setObjectName("frameDailySales");
        vboxLayout = new QVBoxLayout(frameDailySales);
        vboxLayout->setObjectName("vboxLayout");
        titleDailySales = new QLabel(frameDailySales);
        titleDailySales->setObjectName("titleDailySales");

        vboxLayout->addWidget(titleDailySales);

        valueDailySales = new QLabel(frameDailySales);
        valueDailySales->setObjectName("valueDailySales");

        vboxLayout->addWidget(valueDailySales);


        summaryGrid->addWidget(frameDailySales, 0, 0, 1, 1);

        frameActiveTables = new QFrame(HomePage);
        frameActiveTables->setObjectName("frameActiveTables");
        vboxLayout1 = new QVBoxLayout(frameActiveTables);
        vboxLayout1->setObjectName("vboxLayout1");
        titleActiveTables = new QLabel(frameActiveTables);
        titleActiveTables->setObjectName("titleActiveTables");

        vboxLayout1->addWidget(titleActiveTables);

        valueActiveTables = new QLabel(frameActiveTables);
        valueActiveTables->setObjectName("valueActiveTables");

        vboxLayout1->addWidget(valueActiveTables);


        summaryGrid->addWidget(frameActiveTables, 0, 1, 1, 1);

        frameTopProduct = new QFrame(HomePage);
        frameTopProduct->setObjectName("frameTopProduct");
        vboxLayout2 = new QVBoxLayout(frameTopProduct);
        vboxLayout2->setObjectName("vboxLayout2");
        titleTopProduct = new QLabel(frameTopProduct);
        titleTopProduct->setObjectName("titleTopProduct");

        vboxLayout2->addWidget(titleTopProduct);

        valueTopProduct = new QLabel(frameTopProduct);
        valueTopProduct->setObjectName("valueTopProduct");

        vboxLayout2->addWidget(valueTopProduct);


        summaryGrid->addWidget(frameTopProduct, 0, 2, 1, 1);


        mainLayout->addLayout(summaryGrid);

        contentLayout = new QHBoxLayout();
        contentLayout->setSpacing(16);
        contentLayout->setObjectName("contentLayout");
        frameRecent = new QFrame(HomePage);
        frameRecent->setObjectName("frameRecent");
        vboxLayout3 = new QVBoxLayout(frameRecent);
        vboxLayout3->setObjectName("vboxLayout3");
        titleRecent = new QLabel(frameRecent);
        titleRecent->setObjectName("titleRecent");

        vboxLayout3->addWidget(titleRecent);

        listRecent = new QListWidget(frameRecent);
        listRecent->setObjectName("listRecent");

        vboxLayout3->addWidget(listRecent);


        contentLayout->addWidget(frameRecent);

        framePhoto = new QFrame(HomePage);
        framePhoto->setObjectName("framePhoto");
        vboxLayout4 = new QVBoxLayout(framePhoto);
        vboxLayout4->setObjectName("vboxLayout4");
        labelPhoto = new QLabel(framePhoto);
        labelPhoto->setObjectName("labelPhoto");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelPhoto->sizePolicy().hasHeightForWidth());
        labelPhoto->setSizePolicy(sizePolicy);
        labelPhoto->setPixmap(QPixmap(QString::fromUtf8(":/images/imageFile/modern_interior.jpg")));
        labelPhoto->setScaledContents(true);

        vboxLayout4->addWidget(labelPhoto);


        contentLayout->addWidget(framePhoto);


        mainLayout->addLayout(contentLayout);

        labelFooter = new QLabel(HomePage);
        labelFooter->setObjectName("labelFooter");
        labelFooter->setAlignment(Qt::AlignmentFlag::AlignCenter);

        mainLayout->addWidget(labelFooter);


        retranslateUi(HomePage);

        QMetaObject::connectSlotsByName(HomePage);
    } // setupUi

    void retranslateUi(QWidget *HomePage)
    {
        headerFrame->setStyleSheet(QCoreApplication::translate("HomePage", "\n"
"        QFrame { background: transparent; padding: 12px; }\n"
"        /* Title: big, bold, accent gold on dark semi\342\200\221transparent */\n"
"        QLabel#labelRestaurantAutomation {\n"
"          font-size: 26px;\n"
"          font-weight: bold;\n"
"          color: #f7c04a;\n"
"          background: rgba(0,0,0,0.5);\n"
"          padding: 6px;\n"
"          border-radius: 4px;\n"
"        }\n"
"        /* Clock: white bold on dark semi\342\200\221transparent */\n"
"        QLabel#labelDateTime {\n"
"          font-size: 20px;\n"
"          font-weight: bold;\n"
"          color: #ffffff;\n"
"          background: rgba(0,0,0,0.4);\n"
"          padding: 4px;\n"
"          border-radius: 4px;\n"
"        }\n"
"      ", nullptr));
        labelRestaurantAutomation->setText(QCoreApplication::translate("HomePage", "Restaurant Automation", nullptr));
        labelDateTime->setText(QCoreApplication::translate("HomePage", "00.00.0000\302\240\302\240\302\24000:00", nullptr));
        frameDailySales->setStyleSheet(QCoreApplication::translate("HomePage", "\n"
"          QFrame { background: #2c7be5; border-radius:8px; }\n"
"          QLabel { color: white; }\n"
"        ", nullptr));
        titleDailySales->setText(QCoreApplication::translate("HomePage", "Daily Sales", nullptr));
        valueDailySales->setText(QCoreApplication::translate("HomePage", "0 \342\202\272", nullptr));
        frameActiveTables->setStyleSheet(QCoreApplication::translate("HomePage", "\n"
"          QFrame { background: #28a745; border-radius:8px; }\n"
"          QLabel { color: white; }\n"
"        ", nullptr));
        titleActiveTables->setText(QCoreApplication::translate("HomePage", "Active Tables", nullptr));
        valueActiveTables->setText(QCoreApplication::translate("HomePage", "0/0", nullptr));
        frameTopProduct->setStyleSheet(QCoreApplication::translate("HomePage", "\n"
"          QFrame { background: #f7c04a; border-radius:8px; }\n"
"          QLabel { color: #333; }\n"
"        ", nullptr));
        titleTopProduct->setText(QCoreApplication::translate("HomePage", "Top Product", nullptr));
        valueTopProduct->setText(QCoreApplication::translate("HomePage", "\342\200\224", nullptr));
        frameRecent->setStyleSheet(QCoreApplication::translate("HomePage", "\n"
"          QFrame { background: rgba(0,0,0,0.6); border-radius:8px; padding:12px; }\n"
"          QLabel#titleRecent {\n"
"            font-size:16px; font-weight:bold; color: #f7c04a; margin-bottom:8px;\n"
"          }\n"
"          QListWidget {\n"
"            border:none; background:transparent; color:#eee;\n"
"          }\n"
"        ", nullptr));
        titleRecent->setText(QCoreApplication::translate("HomePage", "Recent Activities", nullptr));
        framePhoto->setStyleSheet(QCoreApplication::translate("HomePage", "QFrame { background: transparent; }", nullptr));
        labelFooter->setStyleSheet(QCoreApplication::translate("HomePage", "color:#aaa; font-size:10px; background:transparent;", nullptr));
        labelFooter->setText(QString());
        (void)HomePage;
    } // retranslateUi

};

namespace Ui {
    class HomePage: public Ui_HomePage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMEPAGE_H
