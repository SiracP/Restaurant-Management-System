#ifndef REPORTSPAGE_H
#define REPORTSPAGE_H

#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QComboBox>

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

#include "restaurant.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ReportsPage; }
QT_END_NAMESPACE

/**
 * @class ReportsPage
 * @brief Displays aggregated sales metrics and interactive charts.
 *
 * Responsibilities:
 *  - Show overall total revenue and top‐selling product.
 *  - Provide a breakdown table (product → units sold).
 *  - Render either a pie chart of revenue percentages or a bar chart of units sold.
 *  - Allow switching chart type via combo box.
 *
 * Data source: Restaurant singleton (real‐time snapshot).
 */
class ReportsPage : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     */
    explicit ReportsPage(QWidget *parent = nullptr);

    /**
     * @brief Destructor.
     */
    ~ReportsPage() override;

public slots:
    /**
     * @brief Reloads all data and refreshes both table and chart.
     *
     * Called when underlying sales data may have changed.
     * Fetches:
     *  - totalSales, salesByProduct from Restaurant.
     *  - Updates labels, calls populateTable() and appropriate build*Chart().
     */
    void refreshReports();

private slots:
    /**
     * @brief Responds to chart‐type selection changes.
     * @param index Index in comboChartType (0 = Pie, 1 = Bar).
     *
     * Clears previous series and rebuilds the selected chart.
     */
    void updateChartType(int index);

private:
    Ui::ReportsPage* ui;
    QChartView* chartView;        /// @brief Displays the current chart.
    QPieSeries* pieSeries;        /// @brief Holds revenue distribution slices.
    QBarSeries* barSeries;        /// @brief Holds units‐sold bars.

    QLabel* labelTotalSales;        /// @brief Shows “Total Sales: X ₺”.
    QLabel* labelTopProduct;        /// @brief Shows “Top Product: Name (Y ₺)”.
    QComboBox* comboChartType;      /// @brief Selector between “Pie” and “Bar” charts.
    QTableWidget* tableBreakdown;   /// @brief Tabular view of product→units sold.

    /**
     * @brief Fills the breakdown table widget.
     * @param salesByProduct Map of product names to total units sold.
     *
     * - Clears existing rows.
     * - Inserts one row per product with name and units.
     */
    void populateTable(const QMap<QString,int>& salesByProduct);

    /**
     * @brief Prepares the pieSeries to reflect revenue share by product.
     * @param salesByProduct Map of product names to units sold.
     * @param totalSales Total revenue (for calculating percentages).
     *
     * - Converts units × price → revenue per product.
     * - Adds each as a slice labelled “Name (₺rev)”.
     */
    void buildRevenuePie(const QMap<QString,int>& salesByProduct,
                         int totalSales);

    /**
     * @brief Prepares the barSeries to reflect units sold by product.
     * @param salesByProduct Map of product names to units sold.
     *
     * - Adds one QBarSet containing all unit counts.
     * - Configures category axis with product names.
     */
    void buildUnitsBar(const QMap<QString,int>& salesByProduct);
};

#endif
