#include "product.h"

// ------------------------------------------------------------------------------------------------
// Constructor / Destructor
// ------------------------------------------------------------------------------------------------

Product::Product(int price, const QString& name, const QPixmap& image)
    : price(price)
    , name(name)
    , image(image)
{}

// ------------------------------------------------------------------------------------------------
// Accessors
// ------------------------------------------------------------------------------------------------

int Product::getPrice() const {
    return price;
}

const QString& Product::getName() const {
    return name;
}

const QPixmap& Product::getImage() const {
    return image;
}


// ------------------------------------------------------------------------------------------------
// Mutators
// ------------------------------------------------------------------------------------------------

void Product::setPrice(int newPrice) {
    price = newPrice;
}

void Product::setName(const QString& newName) {
    name = newName;
}

void Product::setImage(const QPixmap& newImage) {
    image = newImage;
}
