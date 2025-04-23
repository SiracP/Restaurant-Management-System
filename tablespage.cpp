#include "tablespage.h"
#include "ui_tablespage.h"

#include <QHeaderView>
#include <QTimer>

// ------------------------------------------------------------------------------------------------
// Constructor
// ------------------------------------------------------------------------------------------------
TablesPage::TablesPage(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::TablesPage)
{
    ui->setupUi(this);

    initializeUi();
    populateTableButtons();
}

// ------------------------------------------------------------------------------------------------
// Destructor
// ------------------------------------------------------------------------------------------------
TablesPage::~TablesPage() {
    delete ui;
}

// ------------------------------------------------------------------------------------------------
// initializeUi()
// Initial splitter, table widget, and panel visibility.
// ------------------------------------------------------------------------------------------------
void TablesPage::initializeUi() {
    // Hide the right panel until a table is clicked
    showRightPanel(false);

    // Stretch tableOrders columns to fill
    ui->tableOrders->horizontalHeader()
        ->setSectionResizeMode(QHeaderView::Stretch);

    // Fix splitter behavior
    ui->splitterMain->setStretchFactor(0, 3);
    ui->splitterMain->setStretchFactor(1, 1);
    ui->splitterMain->setCollapsible(0, false);
    ui->splitterMain->setCollapsible(1, false);

    // Minimum widths to keep left side always larger
    ui->frameLeft->setMinimumWidth(400);
    ui->frameRight->setMaximumWidth(350);

    // Style the header label for visibility
    ui->labelSelectedTable->setStyleSheet(
        "font-size: 18px;"
        "font-weight: bold;"
        "color: #2c7be5;"
        "padding: 8px;"
        );

    // Disable “Checkout” until a table with orders is selected
    ui->buttonCheckout->setEnabled(false);

    // Once the UI is laid out, adjust splitter sizes
    QTimer::singleShot(0, this, [this]() {
        ui->splitterMain->setSizes({700, 300});
    });
}

// ------------------------------------------------------------------------------------------------
// populateTableButtons()
// Creates a numbered QPushButton for each table in Restaurant.
// ------------------------------------------------------------------------------------------------
void TablesPage::populateTableButtons() {
    const int count = Restaurant::getInstance().getTableCount();
    auto* layout = ui->gridLayoutTables;
    if (!layout) return;

    // Reserve space might help if many buttons (not critical here)
    // layout->reserve(count); // QGridLayout has no reserve, just note

    for (int i = 0; i < count; ++i) {
        int tableNo = i + 1;

        // Create and configure the button
        QPushButton* btn = new QPushButton(tr("Table %1").arg(tableNo));
        btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        btn->setMinimumSize(80, 80);

        // Place in the grid (4 columns)
        layout->addWidget(btn, i / 4, i % 4);

        // Store for later style updates
        buttons.insert(tableNo, btn);

        // When clicked, call our slot with the table number
        connect(btn, &QPushButton::clicked, this, [this, tableNo]() {
            handleTableClicked(tableNo);
        });

        // Initial style
        applyButtonStyle(tableNo);
    }
}

// ------------------------------------------------------------------------------------------------
// handleTableClicked()
// Slot: user clicked a table button.
// ------------------------------------------------------------------------------------------------
void TablesPage::handleTableClicked(int tableNo) {
    currentTable = Restaurant::getInstance().getTable(tableNo);
    if (!currentTable) return;

    displayTableInfo();
    updateOrderListDisplay();
    applyButtonStyle(tableNo);

    // Enable checkout only if the table is occupied
    ui->buttonCheckout->setEnabled(currentTable->isOccupied());

    showRightPanel(true);
}

// ------------------------------------------------------------------------------------------------
// displayTableInfo()
// Updates the "Selected Table" label.
// ------------------------------------------------------------------------------------------------
void TablesPage::displayTableInfo() {
    ui->labelSelectedTable->setText(
        tr("📌 Selected Table: %1").arg(currentTable->getTableNo())
        );
}

// ------------------------------------------------------------------------------------------------
// clearOrderTable()
// Remove all rows before repopulating.
// ------------------------------------------------------------------------------------------------
void TablesPage::clearOrderTable() {
    ui->tableOrders->clearContents();
    ui->tableOrders->setRowCount(0);
}

// ------------------------------------------------------------------------------------------------
// updateOrderListDisplay()
// Populates the QTableWidget with the current table's orders.
// ------------------------------------------------------------------------------------------------
void TablesPage::updateOrderListDisplay() {
    clearOrderTable();
    ui->tableOrders->setColumnCount(3);
    ui->tableOrders->setHorizontalHeaderLabels(
        { tr("Product"), tr("Quantity"), tr("Total") }
        );

    const auto& orders = currentTable->getOrderList();
    if (orders.empty()) {
        // Show a single row stating "No orders yet"
        ui->tableOrders->setRowCount(1);
        auto* item = new QTableWidgetItem(tr("No orders yet"));
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableOrders->setItem(0, 0, item);
        ui->tableOrders->setSpan(0, 0, 1, 3);
        return;
    }

    // Fill each order row
    for (auto const& [product, qty] : orders) {
        int row = ui->tableOrders->rowCount();
        ui->tableOrders->insertRow(row);

        // Name cell
        auto* nameItem = new QTableWidgetItem(product->getName());
        nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
        ui->tableOrders->setItem(row, 0, nameItem);

        // Quantity cell
        auto* qtyItem = new QTableWidgetItem(QString::number(qty));
        qtyItem->setFlags(qtyItem->flags() & ~Qt::ItemIsEditable);
        ui->tableOrders->setItem(row, 1, qtyItem);

        // Total cell
        int lineTotal = product->getPrice() * qty;
        auto* totalItem = new QTableWidgetItem(
            QString::number(lineTotal) + " ₺"
            );
        totalItem->setFlags(totalItem->flags() & ~Qt::ItemIsEditable);
        ui->tableOrders->setItem(row, 2, totalItem);
    }
}

// ------------------------------------------------------------------------------------------------
// applyButtonStyle()
// Colors a table button green if empty, red if has orders.
// ------------------------------------------------------------------------------------------------
void TablesPage::applyButtonStyle(int tableNo) {
    auto it = buttons.find(tableNo);
    if (it == buttons.end()) return;

    bool empty = Restaurant::getInstance()
                     .getTable(tableNo)
                     ->getOrderList()
                     .empty();

    QString color = empty ? "green" : "red";
    it.value()->setStyleSheet(
        QStringLiteral(
            "background-color: %1; color: white; font-weight: bold;"
            ).arg(color)
        );
}

// ------------------------------------------------------------------------------------------------
// showRightPanel()
// Show or hide the right column of UI.
// ------------------------------------------------------------------------------------------------
void TablesPage::showRightPanel(bool visible) {
    ui->frameRight->setVisible(visible);
}

// ------------------------------------------------------------------------------------------------
// Close button on right panel.
// ------------------------------------------------------------------------------------------------
void TablesPage::on_buttonCloseRightPanel_clicked() {
    showRightPanel(false);

    // Whenever we close the panel, disable checkout again
    ui->buttonCheckout->setEnabled(false);

    currentTable = nullptr;
}

// ------------------------------------------------------------------------------------------------
// "Add Order" button.
// Signal to switch to order page.
// ------------------------------------------------------------------------------------------------
void TablesPage::on_buttonAddOrder_clicked() {
    if (currentTable) {
        emit goToOrderPage(currentTable);
    }
}

// ------------------------------------------------------------------------------------------------
// "Checkout" button.
// Signal to switch to checkout page.
// ------------------------------------------------------------------------------------------------
void TablesPage::on_buttonCheckout_clicked() {
    if (currentTable) {
        emit goToCheckoutPage(currentTable);
    }
}

// ------------------------------------------------------------------------------------------------
// refreshCurrentTable()
// Called after returning from order/checkout to update the display.
// ------------------------------------------------------------------------------------------------
void TablesPage::refreshCurrentTable() {
    if (!currentTable) return;
    updateOrderListDisplay();
    applyButtonStyle(currentTable->getTableNo());

    // Ensure the Checkout button reflects the current table’s occupied state
    ui->buttonCheckout->setEnabled(currentTable->isOccupied());
}
