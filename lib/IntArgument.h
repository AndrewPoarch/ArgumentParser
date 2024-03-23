#pragma once

#include <string>
#include <vector>
#include "Argument.h"

namespace ArgumentParser {

//class IntArgument: public BaseArgument {
//  public:
//    IntArgument(char short_name, const std::string& long_name, int value)
//        : short_name_(short_name), long_name_(std::move(long_name)), value_(value) {
//        is_defined_ = true;
//    }
//
//    IntArgument(char short_name, const std::string& long_name)
//        : short_name_(short_name), long_name_(std::move(long_name)) {}
//
//    explicit IntArgument(const std::string& long_name)
//        : long_name_(std::move(long_name)) {}
//
//    IntArgument(const std::string& long_name, const std::string& instructions)
//        : long_name_(std::move(long_name)), help_instructions_(std::move(instructions)) {}
//
//    explicit IntArgument(char short_name)
//        : short_name_(short_name) {}
//
//    [[nodiscard]] std::string GetLongName() const {
//        return long_name_;
//    }
//
//    [[nodiscard]] int GetValue() const {
//        return value_;
//    }
//
//    [[nodiscard]] char GetShortName() const {
//        return short_name_;
//    }
//
//    [[nodiscard]] bool IsDefined() const {
//        return is_defined_;
//    }
//
//    [[nodiscard]] int GetValueFromValues(int index) const {
//        return int_values_[index];
//    }
//
//    [[nodiscard]] std::vector<int> GetIntValues() const {
//        return int_values_;
//    }
//
//    [[nodiscard]] int GetMulti() const {
//        return min_amount_of_values_;
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
//    [[nodiscard]] int GetDefault() const {
//        return value_;
//    }
//
//    [[nodiscard]] bool GetPositional() const {
//        return is_positional_;
//    }
//
//    IntArgument& SetValue(int value);
//
//    IntArgument& MultiValue();
//
//    IntArgument& MultiValue(size_t amount);
//
//    IntArgument& StoreValues(std::vector<int>& destination);
//
//    IntArgument& Positional();
//
//    std::string type = "int";
//
//  private:
//    char short_name_ = '\r';
//    std::string long_name_{};
//    int value_{};
//    bool is_defined_ = false;
//    bool is_stored_ = false;
//    bool is_multi_value = false;
//    bool is_positional_ = false;
//    int* store_pointer_{};
//    std::vector<int>* values_pointer_{};
//    int min_amount_of_values_ = -1;
//    std::vector<int> int_values_{};
//    std::string help_instructions_{};
//};
}