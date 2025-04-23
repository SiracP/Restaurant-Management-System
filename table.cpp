#include "table.h"

// ------------------------------------------------------------------------------------------------
// Constructor
// ------------------------------------------------------------------------------------------------
Table::Table(int tableNo)
    : tableNo(tableNo),
    occupied(false),
    remainingAmount(0),
    orderList()
{}

// ------------------------------------------------------------------------------------------------
// getTableNo()
// Return the 1-based table number
// ------------------------------------------------------------------------------------------------
int Table::getTableNo() const
{
    return tableNo;
}

// ------------------------------------------------------------------------------------------------
// isOccupied()
// Occupied flag reflects whether there are any orders or a remaining balance
// ------------------------------------------------------------------------------------------------
bool Table::isOccupied() const
{
    return occupied;
}

// ------------------------------------------------------------------------------------------------
// getRemainingAmount()
// Return the outstanding unpaid remainder
// ------------------------------------------------------------------------------------------------
int Table::getRemainingAmount() const
{
    return remainingAmount;
}

// ------------------------------------------------------------------------------------------------
// getOrderList()
// Access the underlying map of Product* → quantity
// ------------------------------------------------------------------------------------------------
const std::unordered_map<const Product*, int>& Table::getOrderList() const
{
    return orderList;
}

// ------------------------------------------------------------------------------------------------
// getCheckSum()
// Sum up price × quantity for all ordered items (ignores remainingAmount)
// ------------------------------------------------------------------------------------------------
int Table::getCheckSum() const
{
    int sum = 0;
    for (const auto& entry : orderList) {
        sum += entry.first->getPrice() * entry.second;
    }
    return sum;
}

// ------------------------------------------------------------------------------------------------
// addToOrderList()
// Add (or subtract, if count is negative) items to the order.
// Erase the product when its qty falls to zero or below.
// Then update occupied.
// ------------------------------------------------------------------------------------------------
void Table::addToOrderList(const Product& product, int count)
{
    int& qty = orderList[&product];
    qty += count;

    if (qty <= 0) {
        orderList.erase(&product);
    }

    // occupied if any orders remain or there's a leftover balance
    occupied = !orderList.empty() || remainingAmount > 0;
}

// ------------------------------------------------------------------------------------------------
// removeFromOrderList()
// Remove a given quantity (non-negative) of a product.
// Behaves like addToOrderList(product, –count).
// ------------------------------------------------------------------------------------------------
void Table::removeFromOrderList(const Product& product, int count)
{
    auto it = orderList.find(&product);
    if (it == orderList.end()) {
        return;
    }

    it->second -= count;
    if (it->second <= 0) {
        orderList.erase(it);
    }

    occupied = !orderList.empty() || remainingAmount > 0;
}

// ------------------------------------------------------------------------------------------------
// setOrderList()
// Replace the entire order list from a QMap.
// Only keeps entries with positive quantities.
// ------------------------------------------------------------------------------------------------
void Table::setOrderList(const QMap<const Product*, int>& newOrders)
{
    orderList.clear();
    for (auto it = newOrders.constBegin(); it != newOrders.constEnd(); ++it) {
        if (it.value() > 0) {
            orderList[it.key()] = it.value();
        }
    }
    occupied = !orderList.empty() || remainingAmount > 0;
}

// ------------------------------------------------------------------------------------------------
// setRemainingAmount()
// Set the remaining unpaid amount and update occupied accordingly
// ------------------------------------------------------------------------------------------------
void Table::setRemainingAmount(int amount)
{
    remainingAmount = amount;
    occupied = !orderList.empty() || remainingAmount > 0;
}

// ------------------------------------------------------------------------------------------------
// resetTable()
// Clear all orders and any remaining balance; mark as unoccupied
// ------------------------------------------------------------------------------------------------
void Table::resetTable()
{
    orderList.clear();
    remainingAmount = 0;
    occupied = false;
}

// ------------------------------------------------------------------------------------------------
// setOccupied()
// Manual override of the occupied flag
// ------------------------------------------------------------------------------------------------
void Table::setOccupied(bool occupied)
{
    occupied = occupied;
}
