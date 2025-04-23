#ifndef TABLE_H
#define TABLE_H

#include "product.h"
#include <unordered_map>
#include <QMap>

/**
 * @class Table
 * @brief Manages orders and partial payments for a single restaurant table.
 *
 * Each Table object tracks:
 *  - Its numeric identifier (tableNo_)
 *  - A map of products to their ordered quantities (orderList_)
 *  - A remaining unpaid amount if partial payment occurred (remainingAmount_)
 *  - Whether the table is currently occupied (occupied_)
 *
 * Provides operations to add or remove quantities of products,
 * set the entire order list from UI data, and handle
 * “remaining” amounts from non‐exact payments.
 */
class Table {
public:
    /**
     * @brief Constructs a new Table with the specified number.
     * @param tableNo 1-based numeric ID of the table.
     */
    explicit Table(int tableNo);

    /**
     * @brief Get the table’s numeric identifier.
     * @return The 1-based table number.
     */
    int getTableNo() const;

    /**
     * @brief Check if the table is currently occupied.
     *
     * A table is occupied if it has any orders or a remaining unpaid amount.
     *
     * @return true if occupied, false otherwise.
     */
    bool isOccupied() const;

    /**
     * @brief Get the partial unpaid remainder from custom payments.
     *
     * When a user pays an amount that does not evenly cover item prices,
     * the difference is stored as a remaining amount.
     *
     * @return The outstanding remainder (≥ 0).
     */
    int getRemainingAmount() const;

    /**
     * @brief Retrieve the current order list.
     *
     * @return Constant reference to an unordered_map mapping Product pointers
     *         to quantities ordered.
     */
    const std::unordered_map<const Product*, int>& getOrderList() const;

    /**
     * @brief Calculate the total cost of all current orders.
     *
     * Does not include any remainingAmount_; only sums (price × quantity).
     *
     * @return Total price of ordered items.
     */
    int getCheckSum() const;

    /**
     * @brief Increase or decrease quantity of a product in the order.
     *
     * If the resulting quantity becomes ≤ 0, the product is removed from the order.
     * Also updates occupied_ flag automatically.
     *
     * @param product Reference to the Product being added/removed.
     * @param count Number of items to add (positive) or subtract (negative).
     */
    void addToOrderList(const Product& product, int count);

    /**
     * @brief Decrease quantity of a product in the order.
     *
     * If the resulting quantity becomes ≤ 0, the product is removed.
     * Updates occupied_ flag accordingly.
     *
     * @param product Reference to the Product being removed.
     * @param count Number of items to remove.
     */
    void removeFromOrderList(const Product& product, int count);

    /**
     * @brief Replace the order list from a Qt‑style map.
     *
     * Converts QMap entries into the internal unordered_map,
     * ignoring non-positive quantities. Updates occupied_ flag.
     *
     * @param newOrders QMap of Product pointers to quantities.
     */
    void setOrderList(const QMap<const Product*, int>& newOrders);

    /**
     * @brief Set the remaining unpaid amount after a custom payment.
     *
     * Marks the table occupied if there is any unpaid remainder
     * or existing orders.
     *
     * @param amount The amount remaining (≥ 0).
     */
    void setRemainingAmount(int amount);

    /**
     * @brief Clear all orders and any remaining unpaid amount.
     *
     * Resets the table to an unoccupied, pristine state.
     */
    void resetTable();

    /**
     * @brief Explicitly set the occupied flag.
     *
     * Rarely needed since occupied_ is managed automatically,
     * but provided for manual override.
     *
     * @param occupied true to mark occupied, false to free the table.
     */
    void setOccupied(bool occupied);

private:
    int tableNo;                                           /// @brief Unique table identifier (1-based).
    bool occupied;                                         /// @brief True if there are orders or a remainder.
    int remainingAmount;                                   /// @brief Partial payment remainder (if any).
    std::unordered_map<const Product*, int> orderList;     /// @brief Map from Product pointer to ordered quantity.
};

#endif
