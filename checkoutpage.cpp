#include "checkoutpage.h"
#include "ui_checkoutpage.h"

#include <QTableWidgetItem>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <algorithm>

// ------------------------------------------------------------------------------------------------
// Constructor
// ------------------------------------------------------------------------------------------------
CheckoutPage::CheckoutPage(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::CheckoutPage)
{
    ui->setupUi(this);

    // Navigate back to tables on “Back” click
    connect(ui->buttonBack, &QPushButton::clicked,
            this, &CheckoutPage::backToTables);

    // Trigger payment processing on “Pay” click
    connect(ui->buttonPay, &QPushButton::clicked,
            this, &CheckoutPage::handlePayment);
}

// ------------------------------------------------------------------------------------------------
// Destructor
// ------------------------------------------------------------------------------------------------
CheckoutPage::~CheckoutPage()
{
    delete ui;
}

// ------------------------------------------------------------------------------------------------
// CheckoutPage::setTable()
// Assigns the table to work on and refreshes the order list.
// ------------------------------------------------------------------------------------------------
void CheckoutPage::setTable(Table *table)
{
    currentTable = table;
    refreshOrderList();
}

// ------------------------------------------------------------------------------------------------
// CheckoutPage::clearTable()
// Removes and deletes checkbox widgets to prevent leaks, clears all rows.
// ------------------------------------------------------------------------------------------------
void CheckoutPage::clearTable()
{
    // Delete any checkbox containers to avoid leaks
    int rows = ui->tableCheckout->rowCount();
    for (int r = 0; r < rows; ++r) {
        if (auto *container = ui->tableCheckout->cellWidget(r, 0)) {
            ui->tableCheckout->removeCellWidget(r, 0);
            delete container;
        }
    }
    // Clear all items and reset to zero rows
    ui->tableCheckout->clearContents();
    ui->tableCheckout->setRowCount(0);
}

// ------------------------------------------------------------------------------------------------
// CheckoutPage::sortedOrders()
// Returns a vector of current orders sorted by descending unit price.
// ------------------------------------------------------------------------------------------------
std::vector<std::pair<const Product*,int>> CheckoutPage::sortedOrders() const
{
    // Copy and sort current orders by descending unit price
    auto map = currentTable->getOrderList();
    std::vector<std::pair<const Product*,int>> vec(map.begin(), map.end());
    std::sort(vec.begin(), vec.end(),
              [](auto &a, auto &b){
                  return a.first->getPrice() > b.first->getPrice();
              });
    return vec;
}

// ------------------------------------------------------------------------------------------------
// CheckoutPage::populateProductRows()
// Inserts rows with checkboxes and product detail items for each order.
// ------------------------------------------------------------------------------------------------
void CheckoutPage::populateProductRows(
    const std::vector<std::pair<const Product*,int>>& rows)
{
    for (int row = 0; row < static_cast<int>(rows.size()); ++row) {
        const auto &[product, qty] = rows[row];
        int unit     = product->getPrice();
        int subtotal = unit * qty;

        ui->tableCheckout->insertRow(row);

        // --- Checkbox cell ---
        QWidget *container = new QWidget;
        auto *hl = new QHBoxLayout(container);
        hl->setContentsMargins(0, 0, 0, 0);
        hl->setAlignment(Qt::AlignCenter);

        auto *cb = new QCheckBox(container);
        connect(cb, &QCheckBox::checkStateChanged,
                this, &CheckoutPage::updatePaymentInput);
        hl->addWidget(cb);
        container->setLayout(hl);

        ui->tableCheckout->setCellWidget(row, 0, container);

        // --- Product details cells ---
        ui->tableCheckout->setItem(row, 1,
                                   new QTableWidgetItem(product->getName()));
        ui->tableCheckout->setItem(row, 2,
                                   new QTableWidgetItem(QString::number(qty)));
        ui->tableCheckout->setItem(row, 3,
                                   new QTableWidgetItem(QString::number(unit)));
        ui->tableCheckout->setItem(row, 4,
                                   new QTableWidgetItem(QString("%1 ₺").arg(subtotal)));
    }
}

// ------------------------------------------------------------------------------------------------
// CheckoutPage::populateRemainingRow()
// Inserts a row representing any remaining balance with a checkbox.
// ------------------------------------------------------------------------------------------------
void CheckoutPage::populateRemainingRow(int rem)
{
    int row = ui->tableCheckout->rowCount();
    ui->tableCheckout->insertRow(row);

    // Checkbox for paying the remaining balance
    QWidget *container = new QWidget;
    auto *hl = new QHBoxLayout(container);
    hl->setContentsMargins(0, 0, 0, 0);
    hl->setAlignment(Qt::AlignCenter);

    auto *cb = new QCheckBox(container);
    connect(cb, &QCheckBox::checkStateChanged,
            this, &CheckoutPage::updatePaymentInput);
    hl->addWidget(cb);
    container->setLayout(hl);
    ui->tableCheckout->setCellWidget(row, 0, container);

    // “Remaining” label, non-editable
    auto *itemLabel = new QTableWidgetItem("Remaining");
    itemLabel->setFlags(itemLabel->flags() & ~Qt::ItemIsEditable);
    ui->tableCheckout->setItem(row, 1, itemLabel);

    // Blank placeholders for quantity/price columns
    ui->tableCheckout->setItem(row, 2, new QTableWidgetItem(QString()));
    ui->tableCheckout->setItem(row, 3, new QTableWidgetItem(QString()));

    // Remaining amount cell, centered and non-editable
    auto *amtItem = new QTableWidgetItem(QString("%1 ₺").arg(rem));
    amtItem->setFlags(amtItem->flags() & ~Qt::ItemIsEditable);
    amtItem->setTextAlignment(Qt::AlignCenter);
    ui->tableCheckout->setItem(row, 4, amtItem);
}

// ------------------------------------------------------------------------------------------------
// CheckoutPage::updateTotalDue()
// Updates the label at the bottom to show the total amount due.
// ------------------------------------------------------------------------------------------------
void CheckoutPage::updateTotalDue(int totalSum)
{
    ui->labelTotalDue->setText(
        QString("Total: %1 ₺").arg(totalSum)
        );
}

// ------------------------------------------------------------------------------------------------
// CheckoutPage::handleCheckboxPayment()
// Processes checked rows as payments; returns true if any were handled.
// ------------------------------------------------------------------------------------------------
bool CheckoutPage::handleCheckboxPayment()
{
    bool anyChecked = false;
    int rows = ui->tableCheckout->rowCount();

    for (int r = 0; r < rows; ++r) {
        if (auto *container = ui->tableCheckout->cellWidget(r, 0)) {
            if (auto *cb = container->findChild<QCheckBox*>(); cb && cb->isChecked()) {
                anyChecked = true;
                auto *nameItem = ui->tableCheckout->item(r, 1);
                if (!nameItem) continue;
                QString name = nameItem->text();

                if (name == "Remaining") {
                    // Clear the remaining balance
                    currentTable->setRemainingAmount(0);
                } else {
                    // Remove all units of this product
                    int qty = ui->tableCheckout->item(r, 2)->text().toInt();
                    const Product *prod = Restaurant::getInstance()
                                              .getCatalog()
                                              .findByName(name);
                    if (prod && qty > 0) {
                        Restaurant::getInstance().recordSale(*prod, qty);
                        currentTable->removeFromOrderList(*prod, qty);
                    }
                }
            }
        }
    }
    return anyChecked;
}

// ------------------------------------------------------------------------------------------------
// CheckoutPage::handleManualPayment()
// Applies a manual payment amount across remaining and product rows.
// ------------------------------------------------------------------------------------------------
void CheckoutPage::handleManualPayment(int pay)
{
    int remainingPay = pay;

    // Apply against any prior remaining balance
    int prevRem = currentTable->getRemainingAmount();
    if (prevRem > 0) {
        int applied = std::min(prevRem, remainingPay);
        prevRem      -= applied;
        remainingPay -= applied;
        currentTable->setRemainingAmount(prevRem);
    }
    if (remainingPay <= 0) return;

    // Apply across products in descending price order
    auto orders = sortedOrders();
    for (auto &[prod, qty] : orders) {
        if (remainingPay <= 0) break;
        int unit = prod->getPrice();
        int can  = std::min(qty, remainingPay / unit);
        if (can > 0) {
            Restaurant::getInstance().recordSale(*prod, can);
            currentTable->removeFromOrderList(*prod, can);
            remainingPay -= can * unit;
        }
    }

    // Any small leftover becomes a new Remaining balance
    if (remainingPay > 0) {
        // Take one cheapest product for the final partial, if exists
        auto orders2 = sortedOrders();
        if (!orders2.empty()) {
            auto *prod = orders2.back().first;
            int unit   = prod->getPrice();
            Restaurant::getInstance().recordSale(*prod, 1);
            currentTable->removeFromOrderList(*prod, 1);
            currentTable->setRemainingAmount(unit - remainingPay);
        }
    }
}

// ------------------------------------------------------------------------------------------------
// CheckoutPage::updatePaymentInput()
// Adjusts the payment QLineEdit based on checked rows or manual entry.
// ------------------------------------------------------------------------------------------------
void CheckoutPage::updatePaymentInput()
{
    int sumChecked = 0;
    bool anyChecked = false;
    int rows = ui->tableCheckout->rowCount();

    for (int r = 0; r < rows; ++r) {
        if (auto *container = ui->tableCheckout->cellWidget(r, 0)) {
            if (auto *cb = container->findChild<QCheckBox*>(); cb && cb->isChecked()) {
                anyChecked = true;
                // Strip currency suffix and parse integer
                QString txt = ui->tableCheckout->item(r, 4)->text();
                sumChecked += txt.left(txt.indexOf(' ')).toInt();
            }
        }
    }

    if (anyChecked) {
        ui->lineEditPayment->setText(QString::number(sumChecked));
        ui->lineEditPayment->setReadOnly(true);
    } else {
        ui->lineEditPayment->setReadOnly(false);
        int rem = currentTable ? currentTable->getRemainingAmount() : 0;
        ui->lineEditPayment->setText(rem > 0
                                         ? QString::number(rem)
                                         : QString("0"));
    }
}

// ------------------------------------------------------------------------------------------------
// CheckoutPage::handlePayment()
// Entry point for “Pay” button: attempts checkbox logic, then manual payment.
// ------------------------------------------------------------------------------------------------
void CheckoutPage::handlePayment()
{
    if (!currentTable) return;

    bool ok = false;
    int pay = ui->lineEditPayment->text().toInt(&ok);
    if (!ok || pay <= 0) return;

    // First try checkbox-driven payments
    bool used = handleCheckboxPayment();

    // Otherwise fall back to manual payment logic
    if (!used) {
        handleManualPayment(pay);
    }

    // Update UI to reflect new state
    refreshOrderList();

    emit paymentProcessed();

    // If table is fully cleared, mark as free and return to tables
    if (currentTable->getOrderList().empty()
        && currentTable->getRemainingAmount() == 0)
    {
        currentTable->setOccupied(false);
        emit backToTables();
    }
}

// ------------------------------------------------------------------------------------------------
// CheckoutPage::refreshOrderList()
// Clears and rebuilds the checkout table: sets headers, adds rows, and updates input.
// ------------------------------------------------------------------------------------------------
void CheckoutPage::refreshOrderList()
{
    clearTable();
    if (!currentTable) return;

    // Configure table columns
    ui->tableCheckout->setColumnCount(5);
    ui->tableCheckout->setHorizontalHeaderLabels(
        {"", "Product", "Quantity", "Unit Price", "Total"});
    ui->tableCheckout->horizontalHeader()
        ->setSectionResizeMode(QHeaderView::Stretch);

    // Gather sorted orders and compute total
    auto orders = sortedOrders();
    int totalSum = 0;
    for (auto &[p, q] : orders) {
        totalSum += p->getPrice() * q;
    }

    // Populate product rows
    populateProductRows(orders);

    // Handle any leftover remaining amount
    int rem = currentTable->getRemainingAmount();
    if (rem > 0) {
        totalSum += rem;
        populateRemainingRow(rem);
    }

    updateTotalDue(totalSum);

    // Prepare the payment input field
    ui->lineEditPayment->setReadOnly(false);
    ui->lineEditPayment->setText(rem > 0
                                     ? QString::number(rem)
                                     : QString("0"));
}
