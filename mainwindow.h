#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clickablelabel.h"
#include "homepage.h"
#include "productspage.h"
#include "reportspage.h"
#include "tablespage.h"
#include "orderpage.h"
#include "checkoutpage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief The main application window containing a sidebar and stacked pages.
 *
 * Manages six core pages:
 *  - HomePage      : display dashboard with daily summaries and recent activities.
 *  - TablesPage    : select a table and view its current orders.
 *  - OrderPage     : add or edit orders for a selected table.
 *  - CheckoutPage  : process payment and clear the table.
 *  - ProductsPage  : browse product catalog.
 *  - ReportsPage   : generate and view sales and activity reports.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructer.
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor.
     */
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    HomePage* homePage  = nullptr;          /// @page to home
    TablesPage* tablesPage    = nullptr;    /// @page to select tables
    OrderPage* orderPage     = nullptr;     /// @page to add/edit orders
    CheckoutPage* checkoutPage  = nullptr;  /// @page to process payments
    ProductsPage* productsPage = nullptr;   /// @page to products
    ReportsPage* reportsPage  = nullptr;    /// @page to reports

    // --- Setup methods called from constructor ---
    /**
     * @brief Instantiate pages and add them to the QStackedWidget.
     */
    void initPages();

    /**
     * @brief Connect sidebar labels to page‐switching slots.
     */
    void initNavigation();

    /**
     * @brief Wire up signals between pages (e.g. TablesPage → OrderPage transition).
     */
    void initPageTransitions();

    /**
     * @brief Show the home (landing) page in the main stack.
     */
    void showHomePage();

    // --- Page display helpers ---
    /**
     * @brief Switchs to the TablesPage.
     */
    void showTablesPage();

    /**
     * @brief Switch to the OrderPage for a given table
     * @param table The Table to work on.
     */
    void showOrderPage(Table* table);

    /**
     * @brief Switch to the CheckoutPage for a given table
     * @param table The Table to work on.
     */
    void showCheckoutPage(Table* table);

    // --- Sidebar styling ---
    /**
     * @brief Highlights the active sidebar label and resets others.
     * @param activeLabel The label to highlight.
     */
    void setActiveSection(ClickableLabel* activeLabel);

    /**
     * @brief Returns the CSS stylesheet to apply to a sidebar label when it is active.
     * @return The stylesheet string for the active sidebar label
     */
    QString activeStyle() const;

    /**
     * @brief Returns the CSS stylesheet to apply to a sidebar label when it is inactive.
     * @return The stylesheet string for inactive sidebar labels
     */
    QString inactiveStyle() const;
};

#endif
