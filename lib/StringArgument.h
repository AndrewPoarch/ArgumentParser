#pragma once

#include <string>
#include <vector>
#include "ArgParser.h"

namespace ArgumentParser {
//class StringArgument: public BaseArgument  {
//  public:
//    StringArgument(char short_name, const std::string& long_name, const std::string& instructions)
//        : short_name_(short_name), long_name_(std::move(long_name)), help_instructions_(std::move(instructions)) {}
//
//    StringArgument(char short_name, const std::string& long_name)
//        : short_name_(short_name), long_name_(std::move(long_name)) {}
//
//    explicit StringArgument(const std::string& long_name)
//        : long_name_(std::move(long_name)) {}
//
//    explicit StringArgument(char short_name)
//        : short_name_(short_name) {}
//
//    StringArgument SetValue(std::string_view value) {
//        value_ = value;
//        if (is_stored_) {
//            *store_pointer_ = value;
//        }
//
//        return *this;
//    }
//
//    [[nodiscard]] std::string GetLongName() const {
//        return long_name_;
//    }
//
//    [[nodiscard]] std::string GetValue() const{
//        return value_;
//    }
//
//    [[nodiscard]] char GetShortName() const {
//        return short_name_;
//    }
//
//    [[nodiscard]] std::string GetInstructions() const {
//        return help_instructions_;
//    }
//
//    [[nodiscard]] int GetMultiValue() const {
//        return min_amount_of_values_;
//    }
//
//    [[nodiscard]] std::string GetDefault() const {
//        return value_;
//    }
//
//    [[nodiscard]] bool GetPositional() const {
//        return is_positional_;
//    }
//
//    StringArgument Default(const std::string& value);
//
//    StringArgument StoreValue(std::string& destination);
//
//    StringArgument MultiValue(int amount);
//
//    StringArgument Positional();
//
//    std::string type = "str";
//
//  private:
//    char short_name_{};
//    std::string long_name_;
//    std::string value_;
//    bool is_stored_ = false;
//    bool is_positional_ = false;
//    int min_amount_of_values_ = -1;
//    std::string* store_pointer_{};
//    std::string help_instructions_;
//};
}