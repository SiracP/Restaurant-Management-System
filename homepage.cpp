#include "homepage.h"
#include "ui_homepage.h"

#include <QDateTime>
#include <QListWidgetItem>
#include <QLocale>

// ------------------------------------------------------------------------------------------------
// Constructor
// ------------------------------------------------------------------------------------------------
HomePage::HomePage(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::HomePage),
      clockTimer(new QTimer(this))   // Create a timer owned by this widget
{
    ui->setupUi(this);

    // Start clock: connect QTimer to our slot and fire every 1000 ms
    connect(clockTimer, &QTimer::timeout,
            this,       &HomePage::updateDateTime);
    clockTimer->start(1000);

    // Immediately show the current time once at startup
    updateDateTime();

    // Initial data load for all home widgets
    refreshHome();
}

// ------------------------------------------------------------------------------------------------
// Destructor
// ------------------------------------------------------------------------------------------------
HomePage::~HomePage()
{
    delete ui;
}

// ------------------------------------------------------------------------------------------------
// updateDateTime()
// Update the header clock every second.
// ------------------------------------------------------------------------------------------------
void HomePage::updateDateTime()
{
    // Use the locale’s short date‐time format (e.g. "dd.MM.yyyy hh:mm")
    const QString fmt = QLocale().dateTimeFormat(QLocale::ShortFormat);
    QString now = QDateTime::currentDateTime().toString(fmt);

    // Display in the top‐right label
    ui->labelDateTime->setText(now);
}

// ------------------------------------------------------------------------------------------------
// refreshHome()
// Pull latest data and update all sections.
// ------------------------------------------------------------------------------------------------
void HomePage::refreshHome()
{
    // Refresh the clock display
    updateDateTime();

    // Refresh the summary cards: daily sales, active tables, top product
    updateSummaries();

    // Refresh the recent activities list
    updateRecentActivities();
}

// ------------------------------------------------------------------------------------------------
// updateSummaries()
// Fill Daily Sales, Active Tables, and Top Product cards.
// ------------------------------------------------------------------------------------------------
void HomePage::updateSummaries()
{
    auto &restaurant = Restaurant::getInstance();

    // Daily Sales
    int totalRevenue = restaurant.getTotalSales();
    ui->valueDailySales->setText(QString("%1 ₺").arg(totalRevenue));

    // Active Tables (occupied/total)
    int occupiedCount = 0;
    int tableCount    = restaurant.getTableCount();
    for (int i = 1; i <= tableCount; ++i) {
        if (auto *table = restaurant.getTable(i); table && table->isOccupied()) {
            ++occupiedCount;
        }
    }
    ui->valueActiveTables->setText(
        QString("%1/%2").arg(occupiedCount).arg(tableCount)
        );

    // Top Product by revenue
    auto salesMap = restaurant.getSalesByProduct();
    QString bestProduct;
    int bestRevenue = 0;
    for (auto it = salesMap.constBegin(); it != salesMap.constEnd(); ++it) {
        const QString &name = it.key();
        int unitsSold       = it.value();
        if (auto *product = restaurant.getCatalog().findByName(name)) {
            int revenue = product->getPrice() * unitsSold;
            if (revenue > bestRevenue) {
                bestRevenue   = revenue;
                bestProduct   = name;
            }
        }
    }

    if (!bestProduct.isEmpty()) {
        ui->valueTopProduct->setText(
            QString("%1 (%2 ₺)").arg(bestProduct).arg(bestRevenue)
            );
    } else {
        // No sales yet
        ui->valueTopProduct->setText("—");
    }
}

// ------------------------------------------------------------------------------------------------
// updateRecentActivities()
// Show last activities recorded via Restaurant::recordActivity()
// ------------------------------------------------------------------------------------------------
void HomePage::updateRecentActivities()
{
    ui->listRecent->clear();

    auto activities = Restaurant::getInstance().getRecentActivities();
    if (activities.isEmpty()) {
        // Show placeholder when no activity recorded
        ui->listRecent->addItem(new QListWidgetItem(tr("No recent activity")));
    } else {
        // Append each activity line
        for (const auto &entry : activities) {
            ui->listRecent->addItem(new QListWidgetItem(entry));
        }
    }
}
