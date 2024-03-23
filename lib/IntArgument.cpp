#include "IntArgument.h"

namespace ArgumentParser {
IntArgument& IntArgument::SetValue(int value) {
    if (is_multi_value) {
        int_values_.push_back(value);
        if (is_stored_) {
            *values_pointer_ = int_values_;
        }
    } else {
        value_ = value;
        if (is_stored_) {
            *store_pointer_ = value_;
        }
    }

    return *this;
}

IntArgument& IntArgument::MultiValue() {
    is_multi_value = true;

    return *this;
}

IntArgument& IntArgument::MultiValue(size_t amount) {
    is_multi_value = true;
    min_amount_of_values_ = amount;

    return *this;
}

IntArgument& IntArgument::StoreValues(std::vector<int>& destination) {
    is_stored_ = true;
    values_pointer_ = &destination;

    return *this;
}

IntArgument& IntArgument::Positional() {
    is_positional_ = true;

    return *this;
}
}