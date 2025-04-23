#include "productspage.h"
#include "ui_productspage.h"
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>


// ------------------------------------------------------------------------------------------------
// Constructor / Destructor
// ------------------------------------------------------------------------------------------------
ProductsPage::ProductsPage(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::ProductsPage)
{
    ui->setupUi(this);
    refreshProducts();
}

ProductsPage::~ProductsPage()
{
    delete ui;
}

// ------------------------------------------------------------------------------------------------
// refreshProducts()
// Clears any existing product cards, then repopulates the grid from the catalog.
// ------------------------------------------------------------------------------------------------
void ProductsPage::refreshProducts()
{
    // Remove and delete all items/widgets in the grid layout to prevent leaks
    auto *layout = ui->gridLayoutProducts;
    while (auto *item = layout->takeAt(0)) {
        if (auto *w = item->widget()) {
            // Delete the widget (card) and let Qt clean up its layout
            delete w;
        }
        delete item;
    }

    // Query current catalog snapshot
    const auto products = Restaurant::getInstance()
                              .getCatalog()
                              .getAllProducts();

    // Create one card per product, flowing in rows of fixed column count
    const int columns = 3;
    int row = 0, col = 0;
    for (const Product* p : products) {
        createProductCard(p, row, col);
        if (++col >= columns) {
            col = 0;
            ++row;
        }
    }
}

// ------------------------------------------------------------------------------------------------
// createProductCard()
// Builds a single “card” for one product at (row, col):
//  - QGroupBox titled with product name
//  - Centered image scaled smoothly to fit
//  - Centered price label
// ------------------------------------------------------------------------------------------------
void ProductsPage::createProductCard(const Product* product, int row, int col)
{
    // Card container
    auto *box = new QGroupBox(product->getName(), this);
    box->setMinimumSize(150, 150);

    // Vertical layout inside the card
    auto *vbox = new QVBoxLayout(box);
    vbox->setContentsMargins(5, 5, 5, 5);
    vbox->setAlignment(Qt::AlignCenter);

    // Product image (scaled with smooth transformation)
    auto *img = new QLabel(box);
    img->setPixmap(
        product->getImage()
            .scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation)
        );
    img->setAlignment(Qt::AlignCenter);

    // Price label
    auto *price = new QLabel(QString("₺%1").arg(product->getPrice()), box);
    price->setAlignment(Qt::AlignCenter);

    // Assemble card
    vbox->addWidget(img);
    vbox->addWidget(price);

    // Insert into grid
    ui->gridLayoutProducts->addWidget(box, row, col);
}
