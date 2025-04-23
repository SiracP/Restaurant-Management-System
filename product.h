#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>
#include <QPixmap>

/**
 * @class Product
 * @brief Represents a menu item with a name, price, and associated image.
 * Instances of this class are stored in the ProductCatalog and referenced by orders.
 */

class Product {
private:
    int price;
    QString name;
    QPixmap image;

public:
    /**
     *@brief Constructer.
     *@param price The unit price (must be non-negative).
     *@param name  The display name.
     *@param image The product image; defaults to a null QPixmap.
     */
    explicit Product(int price, const QString& name, const QPixmap& image = QPixmap());

    /**
     * @brief Returns the unit price.
     * @return Current price value.
     */
    int getPrice() const;

    /**
     * @brief Returns the product’s display name.
     * @return Const reference to the internal QString.
     */
    const QString& getName() const;

    /**
     * @brief Returns the product’s image.
     * @return Const reference to the internal QPixmap.
     */
    const QPixmap& getImage() const;

    /**
     * @brief Sets a new unit price.
     * @param price The new price (should be non-negative).
     */
    void setPrice(int price);

    /**
     * @brief Renames the product.
     * @param name The new display name.
     */
    void setName(const QString& name);

    /**
     * @brief Updates the product’s image.
     * @param image New QPixmap to associate with this product.
     */
    void setImage(const QPixmap& image);
};

#endif
