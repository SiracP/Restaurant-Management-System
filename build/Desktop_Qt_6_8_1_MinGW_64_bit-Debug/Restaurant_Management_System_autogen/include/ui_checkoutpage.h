/********************************************************************************
** Form generated from reading UI file 'checkoutpage.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKOUTPAGE_H
#define UI_CHECKOUTPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CheckoutPage
{
public:
    QVBoxLayout *verticalLayoutMain;
    QLabel *labelTitle;
    QTableWidget *tableCheckout;
    QLabel *labelTotalDue;
    QHBoxLayout *layoutPayment;
    QLineEdit *lineEditPayment;
    QPushButton *buttonPay;
    QPushButton *buttonBack;

    void setupUi(QWidget *CheckoutPage)
    {
        if (CheckoutPage->objectName().isEmpty())
            CheckoutPage->setObjectName("CheckoutPage");
        CheckoutPage->resize(538, 452);
        verticalLayoutMain = new QVBoxLayout(CheckoutPage);
        verticalLayoutMain->setObjectName("verticalLayoutMain");
        labelTitle = new QLabel(CheckoutPage);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setAlignment(Qt::AlignmentFlag::AlignHCenter);

        verticalLayoutMain->addWidget(labelTitle);

        tableCheckout = new QTableWidget(CheckoutPage);
        tableCheckout->setObjectName("tableCheckout");

        verticalLayoutMain->addWidget(tableCheckout);

        labelTotalDue = new QLabel(CheckoutPage);
        labelTotalDue->setObjectName("labelTotalDue");
        labelTotalDue->setAlignment(Qt::AlignmentFlag::AlignRight);

        verticalLayoutMain->addWidget(labelTotalDue);

        layoutPayment = new QHBoxLayout();
        layoutPayment->setObjectName("layoutPayment");
        lineEditPayment = new QLineEdit(CheckoutPage);
        lineEditPayment->setObjectName("lineEditPayment");

        layoutPayment->addWidget(lineEditPayment);

        buttonPay = new QPushButton(CheckoutPage);
        buttonPay->setObjectName("buttonPay");

        layoutPayment->addWidget(buttonPay);


        verticalLayoutMain->addLayout(layoutPayment);

        buttonBack = new QPushButton(CheckoutPage);
        buttonBack->setObjectName("buttonBack");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonBack->sizePolicy().hasHeightForWidth());
        buttonBack->setSizePolicy(sizePolicy);

        verticalLayoutMain->addWidget(buttonBack);


        retranslateUi(CheckoutPage);

        QMetaObject::connectSlotsByName(CheckoutPage);
    } // setupUi

    void retranslateUi(QWidget *CheckoutPage)
    {
        labelTitle->setStyleSheet(QCoreApplication::translate("CheckoutPage", "font-size: 18px; font-weight: bold;", nullptr));
        labelTitle->setText(QCoreApplication::translate("CheckoutPage", "\360\237\222\263 Checkout", nullptr));
        labelTotalDue->setStyleSheet(QCoreApplication::translate("CheckoutPage", "font-weight: bold;", nullptr));
        labelTotalDue->setText(QCoreApplication::translate("CheckoutPage", "Total: 0 \342\202\272", nullptr));
        lineEditPayment->setPlaceholderText(QCoreApplication::translate("CheckoutPage", "Payment amount", nullptr));
        buttonPay->setText(QCoreApplication::translate("CheckoutPage", "Pay", nullptr));
        buttonBack->setText(QCoreApplication::translate("CheckoutPage", "\342\254\205 Back", nullptr));
        (void)CheckoutPage;
    } // retranslateUi

};

namespace Ui {
    class CheckoutPage: public Ui_CheckoutPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECKOUTPAGE_H
