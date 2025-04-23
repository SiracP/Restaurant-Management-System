#include "mainwindow.h"
#include "ui_mainwindow.h"

// ------------------------------------------------------------------------------------------------
// Constructor / Destructor
// ------------------------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // create and register all pages
    initPages();

    // wire up sidebar clicks
    initNavigation();

    // wire up inter‑page signals (e.g. Tables→Order)
    initPageTransitions();

    // show the home menu by default
    showHomePage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ------------------------------------------------------------------------------------------------
// Create each page and add to the stacked widget
// ------------------------------------------------------------------------------------------------
void MainWindow::initPages()
{
    // Parent = this ensures pages are deleted with the window
    homePage    = new HomePage(this);
    tablesPage  = new TablesPage(this);
    orderPage   = new OrderPage(this);
    checkoutPage= new CheckoutPage(this);
    productsPage= new ProductsPage(this);
    reportsPage = new ReportsPage(this);

    // Add pages to the stacked widget in the desired order
    ui->stackedPages->addWidget(homePage);
    ui->stackedPages->addWidget(tablesPage);
    ui->stackedPages->addWidget(orderPage);
    ui->stackedPages->addWidget(checkoutPage);
    ui->stackedPages->addWidget(productsPage);
    ui->stackedPages->addWidget(reportsPage);
}

// ------------------------------------------------------------------------------------------------
// Connect sidebar labels to switch pages
// ------------------------------------------------------------------------------------------------
void MainWindow::initNavigation()
{
    // Pair each label with its target page
    struct NavEntry { ClickableLabel* label; QWidget* page; };
    const std::vector<NavEntry> entries = {
        { ui->labelNavHome,     homePage    },
        { ui->labelNavTables,   tablesPage  },
        { ui->labelNavProducts, productsPage},
        { ui->labelNavReports,  reportsPage }
    };
    for (const auto& e : entries) {
        // Guard against missing UI elements
        if (!e.label) continue;

        // When label clicked, highlight it and show the corresponding page
        connect(e.label, &ClickableLabel::clicked, this, [this, e]() {
            setActiveSection(e.label);
            if (e.page) ui->stackedPages->setCurrentWidget(e.page);
        });
    }
}

// ------------------------------------------------------------------------------------------------
// Connect page‑to‑page transitions
// ------------------------------------------------------------------------------------------------
void MainWindow::initPageTransitions()
{
    // Tables → Order
    connect(tablesPage, &TablesPage::goToOrderPage,
            this,       &MainWindow::showOrderPage);
    // Tables → Checkout
    connect(tablesPage, &TablesPage::goToCheckoutPage,
            this,       &MainWindow::showCheckoutPage);
    // Order → Tables (back)
    connect(orderPage, &OrderPage::backRequested,
            this,      &MainWindow::showTablesPage);
    // Checkout → Tables (back)
    connect(checkoutPage, &CheckoutPage::backToTables,
            this,          &MainWindow::showTablesPage);


     // After payment, update Reports, Tables, and Home dashboards
    connect(checkoutPage, &CheckoutPage::paymentProcessed,
            reportsPage, &ReportsPage::refreshReports);

    connect(checkoutPage, &CheckoutPage::paymentProcessed,
            tablesPage,  &TablesPage::refreshCurrentTable);

    connect(checkoutPage, &CheckoutPage::paymentProcessed,
            homePage,    &HomePage::refreshHome);

    // After order update, refresh Home dashboard immediately
    connect(orderPage,    &OrderPage::orderUpdated,
            homePage,    &HomePage::refreshHome);
}

// ------------------------------------------------------------------------------------------------
// Page display helpers
// ------------------------------------------------------------------------------------------------
void MainWindow::showHomePage()
{
    // Ensure dashboard shows fresh data
    homePage->refreshHome();
    setActiveSection(ui->labelNavHome);
    ui->stackedPages->setCurrentWidget(homePage);
}

void MainWindow::showTablesPage()
{
    // Refresh current table view
    tablesPage->refreshCurrentTable();
    setActiveSection(ui->labelNavTables);
    ui->stackedPages->setCurrentWidget(tablesPage);
}

void MainWindow::showOrderPage(Table* table)
{
    // Load the selected table into OrderPage
    orderPage->setTable(table);
    setActiveSection(ui->labelNavTables);
    ui->stackedPages->setCurrentWidget(orderPage);
}

void MainWindow::showCheckoutPage(Table* table)
{
    // Load the selected table into CheckoutPage
    checkoutPage->setTable(table);
    setActiveSection(ui->labelNavTables);
    ui->stackedPages->setCurrentWidget(checkoutPage);
}

// ------------------------------------------------------------------------------------------------
// Sidebar label styling
// ------------------------------------------------------------------------------------------------
void MainWindow::setActiveSection(ClickableLabel* activeLabel)
{
    // List of all nav labels
    const std::array<ClickableLabel*,4> labels = {
        ui->labelNavHome,
        ui->labelNavTables,
        ui->labelNavProducts,
        ui->labelNavReports
    };

    // Apply active/inactive styles
    for (auto* lbl : labels) {
        if (!lbl) continue;
        lbl->setStyleSheet(lbl == activeLabel
                               ? activeStyle()
                               : inactiveStyle());
    }
}

QString MainWindow::activeStyle() const
{
    // Use the application's highlight palette
    QColor bg = palette().highlight().color();
    QColor fg = palette().highlightedText().color();
    return QStringLiteral(
               "background-color: %1;"
               "color: %2;"
               "padding: 10px 15px;"
               "border-radius: 6px;"
               ).arg(bg.name(), fg.name());
}

QString MainWindow::inactiveStyle() const
{
    // Transparent background with default text color
    QColor text = palette().text().color();
    return QStringLiteral(
               "background-color: transparent;"
               "color: %1;"
               "padding: 10px 15px;"
               "border-radius: 6px;"
               ).arg(text.name());
}
