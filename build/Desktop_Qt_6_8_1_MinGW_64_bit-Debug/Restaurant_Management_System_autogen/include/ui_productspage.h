/********************************************************************************
** Form generated from reading UI file 'productspage.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRODUCTSPAGE_H
#define UI_PRODUCTSPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProductsPage
{
public:
    QVBoxLayout *mainLayout;
    QLabel *labelHeader;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayoutProducts;

    void setupUi(QWidget *ProductsPage)
    {
        if (ProductsPage->objectName().isEmpty())
            ProductsPage->setObjectName("ProductsPage");
        ProductsPage->resize(696, 541);
        mainLayout = new QVBoxLayout(ProductsPage);
        mainLayout->setObjectName("mainLayout");
        labelHeader = new QLabel(ProductsPage);
        labelHeader->setObjectName("labelHeader");
        labelHeader->setAlignment(Qt::AlignmentFlag::AlignCenter);

        mainLayout->addWidget(labelHeader);

        scrollArea = new QScrollArea(ProductsPage);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 676, 491));
        gridLayoutProducts = new QGridLayout(scrollAreaWidgetContents);
        gridLayoutProducts->setObjectName("gridLayoutProducts");
        scrollArea->setWidget(scrollAreaWidgetContents);

        mainLayout->addWidget(scrollArea);


        retranslateUi(ProductsPage);

        QMetaObject::connectSlotsByName(ProductsPage);
    } // setupUi

    void retranslateUi(QWidget *ProductsPage)
    {
        labelHeader->setStyleSheet(QCoreApplication::translate("ProductsPage", "font-size: 18px; font-weight: bold;", nullptr));
        labelHeader->setText(QCoreApplication::translate("ProductsPage", "\360\237\215\275 Products", nullptr));
        (void)ProductsPage;
    } // retranslateUi

};

namespace Ui {
    class ProductsPage: public Ui_ProductsPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRODUCTSPAGE_H
