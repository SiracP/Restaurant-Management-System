#ifndef ORDERPAGE_H
#define ORDERPAGE_H

#include "restaurant.h"
#include <QWidget>
#include <QMap>
#include <QLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class OrderPage; }
QT_END_NAMESPACE

/**
 * @class OrderPage
 * @brief Allows adding/removing products to a table's order.
 *
 * Displays every product in the catalog as a card with image, price, and +/– buttons.
 * Maintains an in‑memory draft (orderDraft) initialized from the Table's existing orders.
 * On confirmation, overwrites the Table’s order list and emits an update signal.
 */
class OrderPage : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructer.
     */
    explicit OrderPage(QWidget *parent = nullptr);

    /**
     * @brief Destructor.
     */
    ~OrderPage();

    /**
     * @brief Assigns the Table to edit and loads its current orders.
     * @param table Pointer to the Table whose orders will be modified.
     */
    void setTable(Table* table);

signals:
    /**
     * @brief Emitted when the user clicks Back.
     *
     * Informs MainWindow to switch back to the tables list without saving.
     */
    void backRequested();

    /**
     * @brief Emitted after the user confirms the draft order.
     * @param tableNo The number of the table whose order was updated.
     *
     * Allows the table button color to update, etc.
     */
    void orderUpdated(int tableNo);

    /**
    * @brief Emitted after the user confirms an order, to let other pages
    *        (e.g. HomePage) refresh immediately.
    */
    void orderProcessed();

private slots:
    /**
     * @brief Handles the Back button click.
     *
     * Emits backRequested(); no changes are persisted.
     */
    void on_buttonBack_clicked();

    /**
     * @brief Handles the Confirm Order button click.
     *
     * Writes orderDraft back into the Table, emits orderUpdated(), then backRequested().
     */
    void on_buttonConfirmOrder_clicked();

private:
    Ui::OrderPage* ui;
    Table* currentTable = nullptr; /// @brief Currently editing Table
    QMap<const Product*,int> orderDraft; /// @brief In‑memory map of Product→quantity

    // --- Layout management helpers ---

    /**
     * @brief Recursively clears and deletes all widgets/items in a layout.
     * @param layout The layout to clear.
     *
     * Prevents memory leaks by deleting child widgets before removing items.
     */
    void clearLayout(QLayout* layout);

    /**
     * @brief Copies the Table’s current orders into the draft map.
     *
     * Called at setTable() to initialize orderDraft.
     */
    void loadDraftFromTable();

    /**
     * @brief Rebuilds the entire product grid and updates the total.
     *
     * Clears previous cards, creates one card per catalog product via createProductCard(),
     * and then calls updateTotal().
     */
    void refreshDisplay();

    /**
     * @brief Creates a single product card widget at the specified grid position.
     * @param product The Product to display.
     * @param row Grid row index.
     * @param column Grid column index.
     *
     * Card consists of:
     * - Image QLabel
     * - Price QLabel
     * - Count QLabel showing orderDraft[product]
     * - '+' and '–' buttons wired to increase/decrease in orderDraft and updateTotal().
     */
    void createProductCard(const Product* product, int row, int column);

    /**
     * @brief Recalculates the draft’s total price and updates the UI label.
     */
    void updateTotal();
};

#endif
