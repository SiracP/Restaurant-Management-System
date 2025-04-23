/********************************************************************************
** Form generated from reading UI file 'orderpage.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDERPAGE_H
#define UI_ORDERPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OrderPage
{
public:
    QVBoxLayout *layoutMain;
    QLabel *labelTitle;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayoutProducts;
    QLabel *labelTotal;
    QHBoxLayout *layoutButtons;
    QSpacerItem *spacerLeft;
    QPushButton *buttonBack;
    QPushButton *buttonConfirmOrder;
    QSpacerItem *spacerRight;

    void setupUi(QWidget *OrderPage)
    {
        if (OrderPage->objectName().isEmpty())
            OrderPage->setObjectName("OrderPage");
        OrderPage->resize(800, 600);
        layoutMain = new QVBoxLayout(OrderPage);
        layoutMain->setObjectName("layoutMain");
        labelTitle = new QLabel(OrderPage);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setAlignment(Qt::AlignHCenter);

        layoutMain->addWidget(labelTitle);

        scrollArea = new QScrollArea(OrderPage);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        gridLayoutProducts = new QGridLayout(scrollAreaWidgetContents);
        gridLayoutProducts->setObjectName("gridLayoutProducts");
        scrollArea->setWidget(scrollAreaWidgetContents);

        layoutMain->addWidget(scrollArea);

        labelTotal = new QLabel(OrderPage);
        labelTotal->setObjectName("labelTotal");
        labelTotal->setAlignment(Qt::AlignRight);

        layoutMain->addWidget(labelTotal);

        layoutButtons = new QHBoxLayout();
        layoutButtons->setObjectName("layoutButtons");
        spacerLeft = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        layoutButtons->addItem(spacerLeft);

        buttonBack = new QPushButton(OrderPage);
        buttonBack->setObjectName("buttonBack");

        layoutButtons->addWidget(buttonBack);

        buttonConfirmOrder = new QPushButton(OrderPage);
        buttonConfirmOrder->setObjectName("buttonConfirmOrder");

        layoutButtons->addWidget(buttonConfirmOrder);

        spacerRight = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        layoutButtons->addItem(spacerRight);


        layoutMain->addLayout(layoutButtons);


        retranslateUi(OrderPage);

        QMetaObject::connectSlotsByName(OrderPage);
    } // setupUi

    void retranslateUi(QWidget *OrderPage)
    {
        labelTitle->setText(QCoreApplication::translate("OrderPage", "\360\237\247\276 Add Products to Table", nullptr));
        labelTitle->setStyleSheet(QCoreApplication::translate("OrderPage", "font-size: 18px; font-weight: bold; color: #2c7be5;", nullptr));
        labelTotal->setText(QCoreApplication::translate("OrderPage", "Total: 0 \342\202\272", nullptr));
        labelTotal->setStyleSheet(QCoreApplication::translate("OrderPage", "font-size: 14px; font-weight: bold;", nullptr));
        buttonBack->setText(QCoreApplication::translate("OrderPage", "\342\206\220 Back", nullptr));
        buttonConfirmOrder->setText(QCoreApplication::translate("OrderPage", "\342\234\224 Confirm Order", nullptr));
        buttonConfirmOrder->setStyleSheet(QCoreApplication::translate("OrderPage", "font-weight: bold; background-color: #2ecc71; color: white;", nullptr));
        (void)OrderPage;
    } // retranslateUi

};

namespace Ui {
    class OrderPage: public Ui_OrderPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDERPAGE_H
