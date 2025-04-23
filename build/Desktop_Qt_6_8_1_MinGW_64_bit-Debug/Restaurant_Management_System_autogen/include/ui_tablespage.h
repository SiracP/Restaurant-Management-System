/********************************************************************************
** Form generated from reading UI file 'tablespage.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLESPAGE_H
#define UI_TABLESPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TablesPage
{
public:
    QVBoxLayout *mainLayout;
    QSplitter *splitterMain;
    QFrame *frameLeft;
    QVBoxLayout *layoutLeft;
    QLabel *labelHeader;
    QGridLayout *gridLayoutTables;
    QFrame *frameRight;
    QVBoxLayout *layoutRight;
    QPushButton *buttonCloseRightPanel;
    QLabel *labelSelectedTable;
    QTableWidget *tableOrders;
    QHBoxLayout *layoutButtons;
    QPushButton *buttonAddOrder;
    QPushButton *buttonCheckout;

    void setupUi(QWidget *TablesPage)
    {
        if (TablesPage->objectName().isEmpty())
            TablesPage->setObjectName("TablesPage");
        TablesPage->resize(871, 527);
        mainLayout = new QVBoxLayout(TablesPage);
        mainLayout->setObjectName("mainLayout");
        splitterMain = new QSplitter(TablesPage);
        splitterMain->setObjectName("splitterMain");
        splitterMain->setOrientation(Qt::Orientation::Horizontal);
        frameLeft = new QFrame(splitterMain);
        frameLeft->setObjectName("frameLeft");
        frameLeft->setMinimumSize(QSize(300, 0));
        layoutLeft = new QVBoxLayout(frameLeft);
        layoutLeft->setObjectName("layoutLeft");
        labelHeader = new QLabel(frameLeft);
        labelHeader->setObjectName("labelHeader");
        labelHeader->setAlignment(Qt::AlignmentFlag::AlignCenter);

        layoutLeft->addWidget(labelHeader);

        gridLayoutTables = new QGridLayout();
        gridLayoutTables->setObjectName("gridLayoutTables");

        layoutLeft->addLayout(gridLayoutTables);

        splitterMain->addWidget(frameLeft);
        frameRight = new QFrame(splitterMain);
        frameRight->setObjectName("frameRight");
        frameRight->setMinimumSize(QSize(250, 0));
        layoutRight = new QVBoxLayout(frameRight);
        layoutRight->setObjectName("layoutRight");
        buttonCloseRightPanel = new QPushButton(frameRight);
        buttonCloseRightPanel->setObjectName("buttonCloseRightPanel");

        layoutRight->addWidget(buttonCloseRightPanel);

        labelSelectedTable = new QLabel(frameRight);
        labelSelectedTable->setObjectName("labelSelectedTable");
        labelSelectedTable->setAlignment(Qt::AlignmentFlag::AlignCenter);

        layoutRight->addWidget(labelSelectedTable);

        tableOrders = new QTableWidget(frameRight);
        tableOrders->setObjectName("tableOrders");

        layoutRight->addWidget(tableOrders);

        layoutButtons = new QHBoxLayout();
        layoutButtons->setObjectName("layoutButtons");
        buttonAddOrder = new QPushButton(frameRight);
        buttonAddOrder->setObjectName("buttonAddOrder");

        layoutButtons->addWidget(buttonAddOrder);

        buttonCheckout = new QPushButton(frameRight);
        buttonCheckout->setObjectName("buttonCheckout");

        layoutButtons->addWidget(buttonCheckout);


        layoutRight->addLayout(layoutButtons);

        splitterMain->addWidget(frameRight);

        mainLayout->addWidget(splitterMain);


        retranslateUi(TablesPage);

        QMetaObject::connectSlotsByName(TablesPage);
    } // setupUi

    void retranslateUi(QWidget *TablesPage)
    {
        labelHeader->setText(QCoreApplication::translate("TablesPage", "Select a table", nullptr));
        buttonCloseRightPanel->setText(QCoreApplication::translate("TablesPage", "\342\234\226 Close", nullptr));
        labelSelectedTable->setText(QCoreApplication::translate("TablesPage", "Selected Table: None", nullptr));
        buttonAddOrder->setText(QCoreApplication::translate("TablesPage", "Add Order", nullptr));
        buttonCheckout->setText(QCoreApplication::translate("TablesPage", "Checkout", nullptr));
        (void)TablesPage;
    } // retranslateUi

};

namespace Ui {
    class TablesPage: public Ui_TablesPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLESPAGE_H
