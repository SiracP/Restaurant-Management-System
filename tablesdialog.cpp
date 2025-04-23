#include "tablesdialog.h"
#include "ui_tablesdialog.h"
#include <QDebug>
#include <QHeaderView>

TablesDialog::TablesDialog(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::TablesDialog)
{
    ui->setupUi(this);

    setRightPanelVisible(false);

    int tableCount = Restaurant::getInstance().getTableCount();
    createTableButtons(tableCount);

    ui->tableOrders->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

TablesDialog::~TablesDialog()
{
    delete ui;
}

void TablesDialog::createTableButtons(int count, int columns)
{
    QGridLayout* layout = ui->gridLayoutTables;
    if (!layout) return;

    for (int i = 0; i < count; ++i) {
        int tableNo = i + 1;
        QPushButton* btn = new QPushButton(QString("Table %1").arg(tableNo));
        btn->setMinimumSize(100, 80);

        layout->addWidget(btn, i / columns, i % columns);
        tableButtons[tableNo] = btn;

        updateButtonStyle(tableNo);

        connect(btn, &QPushButton::clicked, this, [=]() {
            handleTableClicked(tableNo);
        });
    }
}

void TablesDialog::handleTableClicked(int tableNo)
{
    currentTable = Restaurant::getInstance().getTable(tableNo);
    if (!currentTable) return;

    showTableInfo(tableNo);
    populateOrderList();
    updateButtonStyle(tableNo);
    setRightPanelVisible(true);
}

void TablesDialog::showTableInfo(int tableNo)
{
    ui->labelSelectedTable->setText(QString("Selected Table: %1").arg(tableNo));
}

void TablesDialog::populateOrderList()
{
    ui->tableOrders->clearContents();
    ui->tableOrders->setRowCount(0);
    ui->tableOrders->setColumnCount(3);
    QStringList headers = { "Product", "Quantity", "Total" };
    ui->tableOrders->setHorizontalHeaderLabels(headers);

    if (!currentTable) return;

    const auto& orders = currentTable->getOrderList();
    for (auto it = orders.begin(); it != orders.end(); ++it) {
        int row = ui->tableOrders->rowCount();
        ui->tableOrders->insertRow(row);

        QString name = it->first->getName();
        int quantity = it->second;
        int total = it->first->getPrice() * quantity;

        ui->tableOrders->setItem(row, 0, new QTableWidgetItem(name));
        ui->tableOrders->setItem(row, 1, new QTableWidgetItem(QString::number(quantity)));
        ui->tableOrders->setItem(row, 2, new QTableWidgetItem(QString::number(total) + " ₺"));
    }

    ui->tableOrders->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void TablesDialog::updateButtonStyle(int tableNo)
{
    Table* table = Restaurant::getInstance().getTable(tableNo);
    if (!table || !tableButtons.contains(tableNo)) return;

    QString color = table->isTableOccupied() ? "red" : "green";
    tableButtons[tableNo]->setStyleSheet(
        QString("background-color: %1; color: white; font-weight: bold;").arg(color));
}

void TablesDialog::setRightPanelVisible(bool visible)
{
    ui->frameRight->setVisible(visible);
}

void TablesDialog::on_buttonCloseRightPanel_clicked()
{
    setRightPanelVisible(false);
    currentTable = nullptr;
}

void TablesDialog::on_buttonAddOrder_clicked()
{
    if (!currentTable) return;
    qDebug() << "Add Order clicked for table" << currentTable->getTableNo();
}

void TablesDialog::on_buttonCheckout_clicked()
{
    if (!currentTable) return;
    qDebug() << "Checkout clicked for table" << currentTable->getTableNo();
}

