#include "restaurant.h"
#include <QDateTime>

// ------------------------------------------------------------------------------------------------
// Constructor
// ------------------------------------------------------------------------------------------------
Restaurant::Restaurant()
{
    initializeTables();
    catalog.loadDefaultProducts();

    totalSales = 0;
    salesByProduct.clear();
    recentActivities.clear();
}

// ------------------------------------------------------------------------------------------------
// Destructor
// ------------------------------------------------------------------------------------------------
Restaurant::~Restaurant() = default;

// ------------------------------------------------------------------------------------------------
// getTable()
// Return a pointer to table #tableNumber (1-based), or nullptr if out of range.
// ------------------------------------------------------------------------------------------------
Table* Restaurant::getTable(int tableNumber)
{
    if (tableNumber < 1 || tableNumber > static_cast<int>(tables.size()))
        return nullptr;
    return &tables[tableNumber - 1];
}

// ------------------------------------------------------------------------------------------------
// getCatalog()
// Give direct access to the menu/catalog.
// ------------------------------------------------------------------------------------------------
ProductCatalog& Restaurant::getCatalog()
{
    return catalog;
}

// ------------------------------------------------------------------------------------------------
// getTableCount()
// How many tables are configured.
// ------------------------------------------------------------------------------------------------
int Restaurant::getTableCount() const
{
    return static_cast<int>(tables.size());
}

// ------------------------------------------------------------------------------------------------
// initializeTables()
// Reinitialize the set of tables (clears old, then creates count new ones).
// ------------------------------------------------------------------------------------------------
void Restaurant::initializeTables(int count)
{
    tables.clear();
    tables.reserve(count);
    for (int i = 1; i <= count; ++i) {
        tables.emplace_back(i);
    }
}

// ------------------------------------------------------------------------------------------------
// recordSale()
// Record a sale of `quantity` units of `product`:
//  - update total revenue,
//  - increment per-product count,
//  - append a timestamped text entry to the recent activities.
// ------------------------------------------------------------------------------------------------
void Restaurant::recordSale(const Product& product, int quantity)
{
    int revenue = product.getPrice() * quantity;

    totalSales += revenue;
    salesByProduct[product.getName()] += quantity;

    QString timestamp = QDateTime::currentDateTime().toString("HH:mm");
    QString event = QString("[%1] Sold %2×%3 for %4 ₺")
                        .arg(timestamp)
                        .arg(quantity)
                        .arg(product.getName())
                        .arg(revenue);

    recordActivity(event);
}

// ------------------------------------------------------------------------------------------------
// getTotalSales()
// Return cumulative revenue.
// ------------------------------------------------------------------------------------------------
int Restaurant::getTotalSales() const
{
    return totalSales;
}

// ------------------------------------------------------------------------------------------------
// getSalesByProduct()
// Return a map of units sold per product.
// ------------------------------------------------------------------------------------------------
QMap<QString,int> Restaurant::getSalesByProduct() const
{
    return salesByProduct;
}

// ------------------------------------------------------------------------------------------------
// recordActivity()
// Append a free-form activity string; keep only the most recent 35.
// ------------------------------------------------------------------------------------------------
void Restaurant::recordActivity(const QString& event)
{
    recentActivities.append(event);
    constexpr int kMaxEvents = 35;
    while (recentActivities.size() > kMaxEvents) {
        recentActivities.removeFirst();
    }
}

// ------------------------------------------------------------------------------------------------
// getRecentActivities()
// Return a copy of the recent-activities list.
// ------------------------------------------------------------------------------------------------
QStringList Restaurant::getRecentActivities() const
{
    return recentActivities;
}
