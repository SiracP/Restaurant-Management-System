#include "orderpage.h"
#include "ui_orderpage.h"

#include <QLayoutItem>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

// ------------------------------------------------------------------------------------------------
// Constructor & Destructor
// ------------------------------------------------------------------------------------------------
OrderPage::OrderPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::OrderPage)
{
    ui->setupUi(this);

    // Wire up Back and Confirm buttons
    connect(ui->buttonBack, &QPushButton::clicked, this, &OrderPage::on_buttonBack_clicked);
}

OrderPage::~OrderPage()
{
    delete ui;
}

// ------------------------------------------------------------------------------------------------
// setTable()
// Set current table
// initialize draft from the existing table orders
// rebuild the UI cards to reflect the draft
// ------------------------------------------------------------------------------------------------
void OrderPage::setTable(Table *table)
{
    currentTable = table;
    loadDraftFromTable();
    refreshDisplay();
}

// ------------------------------------------------------------------------------------------------
// refreshDisplay()
// Refresh Order page
// ------------------------------------------------------------------------------------------------
void OrderPage::refreshDisplay()
{
    // Clear old widgets from the grid
    clearLayout(ui->gridLayoutProducts);

    // Create one card per product
    const auto& products = Restaurant::getInstance().getCatalog().getAllProducts();
    int row = 0, col = 0;
    for (const Product* product : products) {
        createProductCard(product, row, col);
        if (++col >= 3) {
            col = 0;
            ++row;
        }
    }

    // Update the Total label
    updateTotal();
}

// ------------------------------------------------------------------------------------------------
// loadDraftFromTable()
// First clear draft
// Copy existing orders into our draft map
// ------------------------------------------------------------------------------------------------
void OrderPage::loadDraftFromTable()
{
    orderDraft.clear();
    if (!currentTable) return;

    for (auto const& entry : currentTable->getOrderList()) {
        orderDraft[entry.first] = entry.second;
    }
}

// ------------------------------------------------------------------------------------------------
// clearLayout()
// Clear a Layout Safely
// Prevents memory leaks by deleting child widgets and sub-layouts.
// ------------------------------------------------------------------------------------------------
void OrderPage::clearLayout(QLayout* layout)
{
    while (auto* item = layout->takeAt(0)) {
        if (auto* widget = item->widget()) {
            layout->removeWidget(widget);
            delete widget;
        }
        if (auto* childLayout = item->layout()) {
            clearLayout(childLayout);
            delete childLayout;
        }
        delete item;
    }
}

// ------------------------------------------------------------------------------------------------
// createProductCard()
// Create one product “card” in the grid
// ------------------------------------------------------------------------------------------------
void OrderPage::createProductCard(const Product* product, int row, int column)
{
    // Container with a title
    auto* box = new QGroupBox(product->getName(), this);
    box->setMinimumSize(150, 150);

    // Vertical layout inside the box
    auto* vbox = new QVBoxLayout(box);

    // Product image
    auto* imageLabel = new QLabel(box);
    imageLabel->setPixmap(product->getImage()
                              .scaled(100,100, Qt::KeepAspectRatio));
    imageLabel->setAlignment(Qt::AlignCenter);

    // Unit price
    auto* priceLabel = new QLabel(QString("₺%1").arg(product->getPrice()), box);
    priceLabel->setAlignment(Qt::AlignCenter);

    // Quantity label (draft)
    auto* countLabel = new QLabel(QString::number(orderDraft[product]), box);
    countLabel->setAlignment(Qt::AlignCenter);

    // Plus / minus buttons
    auto* plusBtn  = new QPushButton("+", box);
    auto* minusBtn = new QPushButton("–", box);

    // Increment handler
    connect(plusBtn, &QPushButton::clicked, this, [=]() {
        orderDraft[product]++;
        countLabel->setText(QString::number(orderDraft[product]));
        updateTotal();
    });

    // Decrement handler
    connect(minusBtn, &QPushButton::clicked, this, [=]() {
        if (orderDraft.contains(product)) {
            orderDraft[product]--;
            if (orderDraft[product] <= 0)
                orderDraft.remove(product);
        }
        countLabel->setText(QString::number(orderDraft.value(product, 0)));
        updateTotal();
    });

    // Add widgets
    auto* hbox = new QHBoxLayout;
    hbox->addWidget(minusBtn);
    hbox->addWidget(countLabel);
    hbox->addWidget(plusBtn);

    vbox->addWidget(imageLabel);
    vbox->addWidget(priceLabel);
    vbox->addLayout(hbox);

     // Place the card in the grid
    ui->gridLayoutProducts->addWidget(box, row, column);
}

// ------------------------------------------------------------------------------------------------
// updateTotal()
// Update the Total at the bottom
// ------------------------------------------------------------------------------------------------
void OrderPage::updateTotal()
{
    int total = 0;
    for (auto it = orderDraft.begin(); it != orderDraft.end(); ++it) {
        total += it.key()->getPrice() * it.value();
    }
    ui->labelTotal->setText(QString("Total: %1 ₺").arg(total));
}

// ------------------------------------------------------------------------------------------------
// "Back" button
// Back to tables page.
// ------------------------------------------------------------------------------------------------
void OrderPage::on_buttonBack_clicked()
{
    emit backRequested();
}

// ------------------------------------------------------------------------------------------------
// "Confirm Order" button
// Confirm orders and back to tables page.
// ------------------------------------------------------------------------------------------------
void OrderPage::on_buttonConfirmOrder_clicked()
{
    if (!currentTable) return;

    // Overwrite the table’s order list with our draft
    currentTable->setOrderList(orderDraft);

    // Record a descriptive activity for ReportsPage and HomePage
    QStringList parts;
    int total = 0;
    for (auto it = orderDraft.constBegin(); it != orderDraft.constEnd(); ++it) {
        int qty   = it.value();
        int price = it.key()->getPrice();
        total += qty * price;
        parts << tr("%1×%2").arg(qty).arg(it.key()->getName());
    }

    // Grab current time as [hour:minute]
    QString timestamp = QDateTime::currentDateTime().toString("HH:mm");

    // Log it via recordActivity, including the timestamp prefix
    Restaurant::getInstance().recordActivity(
        QString("[%1] New order on Table %2: [%3] totaling ₺%4")
            .arg(timestamp)
            .arg(currentTable->getTableNo())
            .arg(parts.join(", "))
            .arg(total)
        );


    // Notify table update and payment
    emit orderUpdated(currentTable->getTableNo());

    // Notify order processed
    emit orderProcessed();

    // Go back to tables page
    emit backRequested();
}
