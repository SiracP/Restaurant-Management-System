#ifndef TABLESPAGE_H
#define TABLESPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QMap>
#include "restaurant.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TablesPage; }
QT_END_NAMESPACE

/**
 * @class TablesPage
 * @brief UI page showing restaurant tables and their orders.
 *
 * This widget displays:
 *  - A grid of buttons representing each table on the left.
 *  - When a table is selected, a right‐hand panel shows its current orders.
 *  - Controls to add new orders or proceed to checkout for the selected table.
 */
class TablesPage : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     * @param parent Optional parent widget for ownership.
     *
     * Initializes the UI, configures the splitter behavior, and populates table buttons.
     */
    explicit TablesPage(QWidget *parent = nullptr);

    /**
     * @brief Destructor cleans up the auto-generated UI object.
     */
    ~TablesPage() override;

    /**
     * @brief Refresh the display for the currently selected table.
     *
     * Call this after returning from the Order or Checkout pages to
     * ensure that any changes (new orders, payments) are shown.
     */
    void refreshCurrentTable();

signals:
    /**
     * @brief Emitted when the user clicks "Add Order".
     * @param table Pointer to the Table for which orders should be edited.
     */
    void goToOrderPage(Table* table);

    /**
     * @brief Emitted when the user clicks "Checkout".
     * @param table Pointer to the Table to be checked out.
     */
    void goToCheckoutPage(Table* table);

private slots:
    /**
     * @brief Slot invoked when one of the table buttons is clicked.
     * @param tableNo The 1-based table number that was selected.
     *
     * Loads and displays the orders for the selected table.
     */
    void handleTableClicked(int tableNo);

    /**
     * @brief Slot for the "Add Order" button in the right panel.
     *
     * Triggers navigation to the OrderPage for the current table.
     */
    void on_buttonAddOrder_clicked();

    /**
     * @brief Slot for the "Checkout" button in the right panel.
     *
     * Triggers navigation to the CheckoutPage for the current table.
     */
    void on_buttonCheckout_clicked();

    /**
     * @brief Slot for the "Close" button in the right panel.
     *
     * Hides the right panel and clears the current table selection.
     */
    void on_buttonCloseRightPanel_clicked();

private:
    Ui::TablesPage* ui;                /// @brief Pointer to the auto-generated UI form.
    QMap<int, QPushButton*> buttons;   /// @brief Map of table numbers to their QPushButton.
    Table* currentTable = nullptr;     /// @brief Currently selected Table, or nullptr.

    /**
     * @brief Perform one‐time UI configuration.
     *
     *  - Hides the right panel initially.
     *  - Configures the splitter so the left side never collapses below a minimum width.
     *  - Sets up the tableOrders widget for stretch‐to‐fit columns.
     */
    void initializeUi();

    /**
     * @brief Create and arrange a QPushButton for each table in the restaurant.
     *
     * Uses Restaurant::getInstance().getTableCount() to determine count.
     * Connects each button's clicked signal to handleTableClicked().
     */
    void populateTableButtons();

    /**
     * @brief Show or hide the right‐hand order details panel.
     * @param visible true to show, false to hide.
     */
    void showRightPanel(bool visible);

    /**
     * @brief Update the header label to reflect the selected table number.
     */
    void displayTableInfo();

    /**
     * @brief Clear and repopulate the order list widget with the current table's orders.
     *
     * If no orders exist, shows a single "No orders yet" row.
     * Otherwise, displays each product, its quantity, and line total.
     */
    void updateOrderListDisplay();

    /**
     * @brief Apply color styling to a table button.
     * @param tableNo 1-based index of the table.
     *
     * Colors green if the table is empty, red if occupied.
     */
    void applyButtonStyle(int tableNo);

    /**
     * @brief Remove all existing rows from the QTableWidget.
     */
    void clearOrderTable();
};

#endif
