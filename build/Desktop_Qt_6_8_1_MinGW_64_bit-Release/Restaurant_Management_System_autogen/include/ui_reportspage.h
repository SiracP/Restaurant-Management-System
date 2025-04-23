/********************************************************************************
** Form generated from reading UI file 'reportspage.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPORTSPAGE_H
#define UI_REPORTSPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReportsPage
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTotalSales;
    QLabel *labelTopProduct;
    QComboBox *comboChartType;
    QFrame *frameChart;
    QVBoxLayout *chartLayout;
    QTableWidget *tableBreakdown;

    void setupUi(QWidget *ReportsPage)
    {
        if (ReportsPage->objectName().isEmpty())
            ReportsPage->setObjectName("ReportsPage");
        ReportsPage->resize(650, 615);
        verticalLayout = new QVBoxLayout(ReportsPage);
        verticalLayout->setObjectName("verticalLayout");
        labelTotalSales = new QLabel(ReportsPage);
        labelTotalSales->setObjectName("labelTotalSales");
        labelTotalSales->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(labelTotalSales);

        labelTopProduct = new QLabel(ReportsPage);
        labelTopProduct->setObjectName("labelTopProduct");
        labelTopProduct->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(labelTopProduct);

        comboChartType = new QComboBox(ReportsPage);
        comboChartType->addItem(QString());
        comboChartType->addItem(QString());
        comboChartType->setObjectName("comboChartType");

        verticalLayout->addWidget(comboChartType);

        frameChart = new QFrame(ReportsPage);
        frameChart->setObjectName("frameChart");
        chartLayout = new QVBoxLayout(frameChart);
        chartLayout->setObjectName("chartLayout");

        verticalLayout->addWidget(frameChart);

        tableBreakdown = new QTableWidget(ReportsPage);
        if (tableBreakdown->columnCount() < 2)
            tableBreakdown->setColumnCount(2);
        tableBreakdown->setObjectName("tableBreakdown");
        tableBreakdown->setColumnCount(2);

        verticalLayout->addWidget(tableBreakdown);


        retranslateUi(ReportsPage);

        QMetaObject::connectSlotsByName(ReportsPage);
    } // setupUi

    void retranslateUi(QWidget *ReportsPage)
    {
        labelTotalSales->setStyleSheet(QCoreApplication::translate("ReportsPage", "font-size: 16px; font-weight: bold;", nullptr));
        labelTotalSales->setText(QCoreApplication::translate("ReportsPage", "Total Sales: 0 \342\202\272", nullptr));
        labelTopProduct->setStyleSheet(QCoreApplication::translate("ReportsPage", "font-size: 14px; font-style: italic;", nullptr));
        labelTopProduct->setText(QCoreApplication::translate("ReportsPage", "Top Product: \342\200\224", nullptr));
        comboChartType->setItemText(0, QCoreApplication::translate("ReportsPage", "Revenue Distribution", nullptr));
        comboChartType->setItemText(1, QCoreApplication::translate("ReportsPage", "Units Sold", nullptr));

        tableBreakdown->setProperty("horizontalHeaderLabels", QVariant(QStringList{
            QCoreApplication::translate("ReportsPage", "Product", nullptr),
            QCoreApplication::translate("ReportsPage", "Units Sold", nullptr)}));
        (void)ReportsPage;
    } // retranslateUi

};

namespace Ui {
    class ReportsPage: public Ui_ReportsPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPORTSPAGE_H
