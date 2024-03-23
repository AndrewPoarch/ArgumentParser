#include "StringArgument.h"

namespace ArgumentParser {
StringArgument StringArgument::Default(const std::string& value) {
    value_ = std::move(value);
    if (is_stored_) {
        *store_pointer_ = value_;
    }

    return *this;
}

StringArgument StringArgument::StoreValue(std::string& destination) {
    is_stored_ = true;
    store_pointer_ = &destination;

    return *this;
}

StringArgument StringArgument::MultiValue(int amount) {
    min_amount_of_values_ = amount;

    return *this;
}

StringArgument StringArgument::Positional() {
    is_positional_ = true;
    return *this;
}
}