#ifndef PRODUCTHASHER_H
#define PRODUCTHASHER_H

#include "product.h"
#include <functional>

namespace std {
template <>
struct hash<Product> {
    std::size_t operator()(const Product& p) const {
        std::hash<std::string> str_hash;
        std::hash<int> int_hash;

        return str_hash(p.getName()) ^ (int_hash(p.getPrice()) << 1);
    }
};
}

#endif // PRODUCTHASHER_H
