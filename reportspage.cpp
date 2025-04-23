#include "reportspage.h"
#include "ui_reportspage.h"

#include <QtCharts/QChart>
#include <QBarSet>
#include <QVBoxLayout>
#include <QHeaderView>
#include <algorithm>

// ------------------------------------------------------------------------------------------------
// Constructor
// ------------------------------------------------------------------------------------------------
ReportsPage::ReportsPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ReportsPage)
    , chartView(new QChartView(this))
    , pieSeries(new QPieSeries(this))
    , barSeries(new QBarSeries(this))
{
    ui->setupUi(this);

    // Cache pointers to UI widgets
    labelTotalSales = ui->labelTotalSales;
    labelTopProduct = ui->labelTopProduct;
    comboChartType  = ui->comboChartType;
    tableBreakdown  = ui->tableBreakdown;

    // Insert our QChartView into the placeholder frame
    auto *lyt = qobject_cast<QVBoxLayout*>(ui->frameChart->layout());
    lyt->addWidget(chartView);

    // Configure base QChart
    auto *chart = new QChart();
    chart->legend()->setAlignment(Qt::AlignRight);
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Stretch table columns
    tableBreakdown->horizontalHeader()
        ->setSectionResizeMode(QHeaderView::Stretch);

    // Wire up chart‐type switcher
    connect(comboChartType,
            QOverload<int>::of(&QComboBox::currentIndexChanged),
            this,
            &ReportsPage::updateChartType);

    // Initial load
    refreshReports();
}

// ------------------------------------------------------------------------------------------------
// Destructor
// ------------------------------------------------------------------------------------------------
ReportsPage::~ReportsPage()
{
    delete ui;
}

// ------------------------------------------------------------------------------------------------
// refreshReports()
// Reloads data from Restaurant singleton, updates labels + table + chart.
// ------------------------------------------------------------------------------------------------
void ReportsPage::refreshReports()
{
    auto &rest = Restaurant::getInstance();

    // Total revenue
    int totalSales = rest.getTotalSales();
    labelTotalSales->setText(
        tr("Total Sales: %1 ₺").arg(totalSales)
        );

    // Per‑product units sold
    auto salesByProduct = rest.getSalesByProduct();
    populateTable(salesByProduct);

    // Compute best product by revenue
    QString bestName;
    int    bestRevenue = 0;
    for (auto it = salesByProduct.constBegin(); it != salesByProduct.constEnd(); ++it) {
        const QString &name = it.key();
        int units = it.value();
        // Look up price from catalog
        if (auto *prod = rest.getCatalog().findByName(name)) {
            int revenue = units * prod->getPrice();
            if (revenue > bestRevenue) {
                bestRevenue = revenue;
                bestName = name;
            }
        }
    }
    if (!bestName.isEmpty()) {
        labelTopProduct->setText(
            tr("Top Product: %1 (%2 ₺)")
                .arg(bestName)
                .arg(bestRevenue)
            );
    } else {
        labelTopProduct->setText(tr("Top Product: —"));
    }

    // Rebuild chart based on current selection
    updateChartType(comboChartType->currentIndex());
}

// ------------------------------------------------------------------------------------------------
// updateChartType()
// Switches between pie (revenue%) and bar (units sold).
// ------------------------------------------------------------------------------------------------
void ReportsPage::updateChartType(int index)
{
    auto &rest = Restaurant::getInstance();
    int totalSales = rest.getTotalSales();
    auto salesByProduct = rest.getSalesByProduct();

    auto *chart = chartView->chart();
    // Remove any existing series
    for (auto *s : chart->series()) {
        chart->removeSeries(s);
    }

    if (index == 0) {
        // Revenue distribution pie
        buildRevenuePie(salesByProduct, totalSales);
        chart->addSeries(pieSeries);
        chart->createDefaultAxes();
        chart->setTitle(tr("Revenue Distribution"));
        chart->legend()->show();
    } else {
        // Units‑sold bar chart
        buildUnitsBar(salesByProduct);
        chart->addSeries(barSeries);
        // Categories are product names
        QStringList categories;
        for (auto it = salesByProduct.constBegin(); it != salesByProduct.constEnd(); ++it) {
            categories << it.key();
        }
        auto *axisX = new QBarCategoryAxis();
        axisX->append(categories);
        chart->addAxis(axisX, Qt::AlignBottom);
        barSeries->attachAxis(axisX);

        // Y axis from 0 to max units
        int maxUnits = 0;
        for (auto units : salesByProduct.values()) {
            maxUnits = std::max(maxUnits, units);
        }
        auto *axisY = new QValueAxis();
        axisY->setRange(0, maxUnits);
        chart->addAxis(axisY, Qt::AlignLeft);
        barSeries->attachAxis(axisY);

        chart->setTitle(tr("Units Sold per Product"));
        chart->legend()->hide();
    }
}

// ------------------------------------------------------------------------------------------------
// populateTable()
// Clears and refills the breakdown table with (product, units sold).
// ------------------------------------------------------------------------------------------------
void ReportsPage::populateTable(const QMap<QString,int>& salesByProduct)
{
    tableBreakdown->clearContents();
    tableBreakdown->setRowCount(0);

    for (auto it = salesByProduct.constBegin(); it != salesByProduct.constEnd(); ++it) {
        int row = tableBreakdown->rowCount();
        tableBreakdown->insertRow(row);
        tableBreakdown->setItem(row, 0,
                                new QTableWidgetItem(it.key()));
        tableBreakdown->setItem(row, 1,
                                new QTableWidgetItem(QString::number(it.value())));
    }
}

// ------------------------------------------------------------------------------------------------
// buildRevenuePie()
// Populates pieSeries so each slice is (product name, % of total revenue).
// ------------------------------------------------------------------------------------------------
void ReportsPage::buildRevenuePie(const QMap<QString,int>& salesByProduct,
                                  int totalSales)
{
    pieSeries->clear();
    auto &rest = Restaurant::getInstance();

    for (auto it = salesByProduct.constBegin(); it != salesByProduct.constEnd(); ++it) {
        const QString &name = it.key();
        int units = it.value();
        if (auto *prod = rest.getCatalog().findByName(name)) {
            int revenue = units * prod->getPrice();
            if (totalSales > 0) {
                qreal percent = qreal(revenue) / totalSales * 100.0;
                auto slice = pieSeries->append(name, percent);
                slice->setLabelVisible(true);
            }
        }
    }
}

// ------------------------------------------------------------------------------------------------
// buildUnitsBar()
// Populates barSeries so each category is one product, with its units sold.
// ------------------------------------------------------------------------------------------------
void ReportsPage::buildUnitsBar(const QMap<QString,int>& salesByProduct)
{
    barSeries->clear();
    // one set containing all values, for simple single‐bar grouping
    QBarSet *set = new QBarSet(tr("Units Sold"));
    for (auto units : salesByProduct.values()) {
        *set << units;
    }
    barSeries->append(set);
}
