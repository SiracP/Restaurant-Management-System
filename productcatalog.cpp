// productcatalog.cpp

#include "productcatalog.h"
#include <QDebug>

// ------------------------------------------------------------------------------------------------
// addProduct()
// Adds or overwrites a Product in the catalog.
// ------------------------------------------------------------------------------------------------
void ProductCatalog::addProduct(int price, const QString& name, QPixmap image)
{
    products[name] = std::make_unique<Product>(price, name, std::move(image));
}

// ------------------------------------------------------------------------------------------------
// findByName()
// Lookup a Product by name in O(1) average time.
// Returns nullptr if no matching entry is found.
// ------------------------------------------------------------------------------------------------
const Product* ProductCatalog::findByName(const QString& name) const
{
    auto it = products.find(name);
    if (it == products.end())
        return nullptr;
    return it->second.get();
}

// ------------------------------------------------------------------------------------------------
// getAllProducts()
// Returns a vector of raw pointers to all Products in the catalog.
// The order of iteration is unspecified (hash-based).
// ------------------------------------------------------------------------------------------------
std::vector<const Product*> ProductCatalog::getAllProducts() const
{
    std::vector<const Product*> out;
    out.reserve(products.size());  // avoid reallocations

    for (const auto& pair : products) {
        // pair.second == unique_ptr<Product>
        out.push_back(pair.second.get());
    }
    return out;
}

// ------------------------------------------------------------------------------------------------
// loadFromJson()
// Reads a JSON file from the given resourcePath (e.g. ":/data/menu.json").
// Expects the JSON to be an array of objects with keys:
//   "name"  : string
//   "price" : integer > 0
//   "image" : filename (relative to imagePrefix)
// Filters out any invalid entries or images that fail to load.
// ------------------------------------------------------------------------------------------------
void ProductCatalog::loadFromJson(const QString& resourcePath,
                                  const QString& imagePrefix)
{
    // Open the resource file for reading
    QFile file(resourcePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "[ProductCatalog] Cannot open" << resourcePath;
        return;
    }

    // Read all bytes and parse the JSON
    QByteArray rawData = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(rawData, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "[ProductCatalog] JSON parse error in"
                   << resourcePath << ":" << parseError.errorString();
        return;
    }

    if (!doc.isArray()) {
        qWarning() << "[ProductCatalog] Expected JSON array in"
                   << resourcePath;
        return;
    }

    // Iterate over each entry in the JSON array
    QJsonArray array = doc.array();
    for (const QJsonValue& val : array) {
        if (!val.isObject()) {
            // Skip non-object entries
            continue;
        }

        QJsonObject obj = val.toObject();

        // Extract and validate fields
        QString name      = obj.value("name").toString().trimmed();
        int     price     = obj.value("price").toInt(-1);
        QString imageFile = obj.value("image").toString().trimmed();

        if (name.isEmpty() || price <= 0 || imageFile.isEmpty()) {
            qWarning() << "[ProductCatalog] Skipping invalid entry:" << obj;
            continue;
        }

        // Build the full path to the image resource
        QString fullImagePath = imagePrefix + imageFile;
        QPixmap pixmap(fullImagePath);
        if (pixmap.isNull()) {
            qWarning() << "[ProductCatalog] Failed to load image:" << fullImagePath;
            continue;
        }

        // Add the product to the catalog
        addProduct(price, name, std::move(pixmap));
    }
}

// ------------------------------------------------------------------------------------------------
// loadDefaultProducts()
// Convenience wrapper to load the built-in menu.json from ":/data/menu.json"
// with images under ":/images/imageFile/" resource directory.
// ------------------------------------------------------------------------------------------------
void ProductCatalog::loadDefaultProducts()
{
    loadFromJson(":/data/menu.json", ":/images/imageFile/");
}
