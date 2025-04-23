#ifndef PRODUCTCATALOG_H
#define PRODUCTCATALOG_H

#include "product.h"

#include <QString>
#include <QPixmap>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <unordered_map>
#include <vector>
#include <memory>

/**
 * @struct QStringHash
 * @brief Functor to allow using QString as a key in std::unordered_map.
 *
 * Uses Qt's qHash under the hood to produce a size_t hash value.
 */
struct QStringHash {
    /**
     * @brief Compute hash code for a QString.
     * @param s The string to hash.
     * @return A size_t hash value.
     */
    size_t operator()(const QString& s) const noexcept {
        return static_cast<size_t>(qHash(s));
    }
};

/**
 * @class ProductCatalog
 * @brief Central registry of available products for the restaurant.
 *
 * Allows:
 *  - Adding and overwriting products by name.
 *  - Looking up a Product by its name.
 *  - Retrieving the full list of products for display or iteration.
 *  - Loading products in bulk from a JSON resource file.
 *
 * Internally stores unique_ptr<Product> to manage product lifetimes.
 */
class ProductCatalog {
public:
    /**
     * @brief Default constructor.
     * Initializes an empty product catalog.
     */
    ProductCatalog() = default;

    /**
     * @brief Destructor.
     * Releases any owned Product instances.
     */
    ~ProductCatalog() = default;

    /**
     * @brief Add or overwrite a product entry in the catalog.
     * @param price The unit price of the product (should be >= 0).
     * @param name  Unique identifier for the product; used as lookup key.
     * @param image Product image; this QPixmap will be moved into storage.
     *
     * If an entry with the same name already exists, it is replaced.
     */
    void addProduct(int price, const QString& name, QPixmap image);

    /**
     * @brief Look up a product by its name.
     * @param name The exact name of the product to find.
     * @return Pointer to the Product if found, or nullptr if not present.
     * @note Returned pointer remains valid until this catalog is destroyed
     *       or the product is overwritten/removed.
     */
    const Product* findByName(const QString& name) const;

    /**
     * @brief Get a list of all products currently in the catalog.
     * @return std::vector of raw Product pointers; order is unspecified.
     *
     * Useful for populating UI lists or iterating through available offerings.
     */
    std::vector<const Product*> getAllProducts() const;

    /**
     * @brief Bulk-load products from a JSON resource file.
     * @param resourcePath Path to the JSON file in the Qt resource system,
     *                     e.g. ":/data/menu.json".
     * @param imagePrefix  Prefix to prepend to each image filename,
     *                     e.g. ":/images/imageFile/".
     *
     * Expects the JSON document to be an array of objects, each containing:
     *   - "name"  : QString
     *   - "price" : integer
     *   - "image" : QString (filename, without prefix)
     *
     * Invalid entries are logged via qWarning and skipped.
     */
    void loadFromJson(const QString& resourcePath,
                      const QString& imagePrefix = ":/images/imageFile/");

    /**
     * @brief Load the built‑in menu from the default resource path.
     *
     * Wraps loadFromJson(":/data/menu.json", ":/images/imageFile/").
     * Called typically at application startup to seed the catalog.
     */
    void loadDefaultProducts();

private:
    /**
     * @brief Maps each product name to its owned Product instance.
     * Uses QStringHash for hashing and unique_ptr for exclusive ownership.
     */
    std::unordered_map<QString,
                       std::unique_ptr<Product>,
                       QStringHash> products;
};

#endif
