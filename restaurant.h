#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "productcatalog.h"
#include "table.h"
#include <vector>
#include <QMap>
#include <QString>
#include <QStringList>

/**
 * @class Restaurant
 * @brief Central singleton managing tables, menu, and sales history.
 *
 * Responsibilities:
 *  - Initialize and store Table objects (occupied status, orders, balances).
 *  - Load and expose the ProductCatalog (menu of available items).
 *  - Record completed sales to drive reporting (total revenue, per‑product breakdown).
 *  - Maintain a rolling list of textual “recent activities” for UI dashboards.
 *
 * Usage:
 *  - Call getInstance() to retrieve the sole global instance.
 *  - Interact via getTable(), getCatalog(), recordSale(), recordActivity(), etc.
 */
class Restaurant {
private:
    /**
     *  @brief Enforce singleton: private constructor.
     **/
    Restaurant();

    std::vector<Table> tables;          /// @brief Tables numbered 1..N, stored zero‑based.
    ProductCatalog catalog;             /// @brief Full menu: product definitions and lookup.
    int totalSales = 0;                /// @brief Sum of all recorded sale revenues (₺).
    QMap<QString,int> salesByProduct;  /// @brief Units sold per product name.
    QStringList recentActivities;      /// @brief Last N textual events (newest at back).

public:
    /**
     * @brief Retrieve the global Restaurant instance.
     * @return Reference to the singleton Restaurant.
     *
     * On first invocation, constructs the instance; subsequent calls return it.
     */
    static Restaurant& getInstance() {
        static Restaurant instance;
        return instance;
    }

    /**
     * @brief Access a specific table by its 1‑based number.
     * @param tableNumber Number of the table (1..getTableCount()).
     * @return Pointer to Table if valid, nullptr otherwise.
     */
    Table* getTable(int tableNumber);

    /**
     * @brief Access the menu of available products.
     * @return Reference to the ProductCatalog.
     */
    ProductCatalog& getCatalog();

    /**
     * @brief Number of tables currently configured.
     * @return Size of the internal tables vector.
     */
    int getTableCount() const;

    /**
     * @brief (Re)initialize the set of tables.
     * @param count Desired number of tables (default 16).
     *
     * Clears existing tables and creates `count` new Table objects.
     */
    void initializeTables(int count = 16);

    /**
     * @brief Record a completed sale transaction.
     * @param product  The product sold.
     * @param quantity Number of units sold.
     *
     * Updates totalRevenue_, increments units in salesByProduct_,
     * and logs a timestamped entry via recordActivity().
     */
    void recordSale(const Product& product, int quantity);

    /**
     * @brief Get cumulative revenue to date.
     * @return Sum of (price × quantity) over all recordSale() calls.
     */
    int getTotalSales() const;

    /**
     * @brief Get units‑sold breakdown by product name.
     * @return Map from product name to total units sold.
     */
    QMap<QString,int> getSalesByProduct() const;

    /**
     * @brief Log a free‑form event in the recent activities list.
     * @param event Arbitrary descriptive text (e.g. "Paid 2×Coffee for Table 3").
     *
     * Maintains up to a fixed maximum count; drops oldest entries when exceeded.
     */
    void recordActivity(const QString& event);

    /**
     * @brief Retrieve the list of recent activity strings.
     * @return Copy of the internal recentActivities_ list.
     *
     * Newest entries appear at the end of the returned QStringList.
     */
    QStringList getRecentActivities() const;

    /// Prevent copying or moving: enforce singleton semantics
    Restaurant(const Restaurant&) = delete;
    Restaurant& operator=(const Restaurant&) = delete;
    Restaurant(Restaurant&&) = delete;
    Restaurant& operator=(Restaurant&&) = delete;

    /**
     * @brief Destructor.
     */
    ~Restaurant();
};

#endif
