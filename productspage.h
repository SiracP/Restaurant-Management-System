#ifndef PRODUCTSPAGE_H
#define PRODUCTSPAGE_H

#include <QWidget>
#include "restaurant.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ProductsPage; }
QT_END_NAMESPACE

/**
 * @brief Displays all products in a scrollable grid, each as a “card.”
 *
 * Responsibilities:
 *  - Build and tear down its own UI (separation of concerns).
 *  - Query Restaurant singleton for the catalog (dependency injection could be added later).
 *  - Render each product in a consistent card layout.
 */
class ProductsPage : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructer.
     */
    explicit ProductsPage(QWidget *parent = nullptr);

    /**
     * @brief Destructor.
     */
    ~ProductsPage() override;

private:
    Ui::ProductsPage *ui;

    /**
     * @brief Fetches the latest product list and rebuilds the grid.
     *
     * - Clears any existing cards to avoid duplicates.
     * - Iterates `Restaurant::getCatalog()` and calls createProductCard().
     */
    void refreshProducts();

    /**
     * @brief Inserts a single product card widget into the grid.
     * @param product The product to display (price, name, image).
     * @param row Zero‑based grid row index.
     * @param col Zero‑based grid column index.
     */
    void createProductCard(const Product* product, int row, int col);
};

#endif
