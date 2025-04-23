#ifndef CHECKOUTPAGE_H
#define CHECKOUTPAGE_H

#include <QWidget>
#include "restaurant.h"
#include <vector>
#include <utility>

QT_BEGIN_NAMESPACE
namespace Ui { class CheckoutPage; }
QT_END_NAMESPACE

/**
 * @class CheckoutPage
 * @brief Manages the payment/checkout flow for a selected table.
 *
 * Displays the current orders (and any leftover "remaining" amount),
 * lets the user select specific items via checkboxes or enter a custom
 * payment amount, and applies the appropriate deductions on the Table.
 */
class CheckoutPage : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     */
    explicit CheckoutPage(QWidget *parent = nullptr);

    /**
     * @brief Destructor.
     */
    ~CheckoutPage();

    /**
     * @brief Assigns the Table whose orders will be displayed/processed.
     * @param table The Table to work on.
     *
     * Triggers a full refresh of the UI to reflect the table's state.
     */
    void setTable(Table* table);

signals:
    /**
     * @brief Emitted when the user wants to go back to the tables list.
     */
    void backToTables();

    /**
     * @brief Emitted right after we finish applying a payment.
     */
    void paymentProcessed();

private slots:
    /**
     * @brief Invoked when the user clicks the “Pay” button.
     *
     * First tries checkbox‐based payments, then custom manual payment if
     * none are checked.
     */
    void handlePayment();

    /**
     * @brief Invoked whenever any checkbox changes.
     *
     * Updates the payment input to sum the checked lines, and toggles
     * readonly state.
     */
    void updatePaymentInput();

private:
    Ui::CheckoutPage *ui;
    Table* currentTable = nullptr; /// @brief The table being checked out

    /**
    * @brief Clears all rows and checkboxes from the table widget.
    */
    void clearTable();

    /**
    * @brief Returns the current orders sorted by unit price descending.
    */
    std::vector<std::pair<const Product*,int>> sortedOrders() const;

    /**
     * @brief Populates a row in the table widget for each product.
     * @param rows Sorted (product, quantity) pairs.
     */
    void populateProductRows(const std::vector<std::pair<const Product*,int>>& rows);

    /**
     * @brief Adds an extra “Remaining” row if there is a leftover amount.
     * @param rem The remaining (partial) payment amount.
     */
    void populateRemainingRow(int rem);

    /**
     * @brief Updates the “Total: … ₺” label to show the current amount due.
     * @param totalSum The computed total (products + remaining).
     */
    void updateTotalDue(int totalSum);

    /**
     * @brief Tries to remove items according to which checkboxes are ticked.
     * @return True if any checkbox‐driven removals were performed.
     *
     * Records each removed product as a sale in Restaurant.
     */
    bool handleCheckboxPayment();

    /**
     * @brief Deducts from the table’s remaining and product list based on a custom amount.
     * @param pay The manually entered payment amount.
     *
     * First applies leftover, then removes as many full‐price items from
     * highest to lowest price, handling any final partial as a new leftover.
     *
     * Records each removed product as a sale in Restaurant.
     */
    void handleManualPayment(int pay);

    /**
     * @brief Clears and repopulates the entire checkout table widget.
     *
     * Invokes clearTable(), then
     * • populateProductRows(...)
     * • populateRemainingRow(...) (if needed)
     * • updateTotalDue(...)
     * • prepares the payment QLineEdit.
     */
    void refreshOrderList();
};

#endif
