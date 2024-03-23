#include "FlagArgument.h"

namespace ArgumentParser {
FlagArgument& FlagArgument::SetValue(bool value) {
    value_ = value;
    if (is_stored_) {
        *store_pointer_ = value_;
    }

    return *this;
}

FlagArgument& FlagArgument::Default(bool value) {
    value_ = value;
    if (is_stored_) {
        *store_pointer_ = value_;
    }

    return *this;
}

FlagArgument& FlagArgument::StoreValue(bool& destination) {
    is_stored_ = true;
    store_pointer_ = &destination;

    return *this;
};
}