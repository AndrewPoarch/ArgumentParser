#pragma once

#include <string>
#include <vector>
#include "Argument.h"


namespace ArgumentParser {

//class FlagArgument: public BaseArgument {
//  public:
//    FlagArgument(char short_name, const std::string& long_name, bool value)
//        : short_name_(short_name), long_name_(std::move(long_name)), value_(value) {}
//
//    FlagArgument(char short_name, const std::string& long_name, const std::string& instructions)
//        : short_name_(short_name), long_name_(std::move(long_name)), help_instructions_(std::move(instructions)) {}
//
//    FlagArgument(const std::string& long_name, const std::string& instructions)
//        : long_name_(std::move(long_name)), help_instructions_(std::move(instructions)) {}
//
//    FlagArgument(char short_name, const std::string& long_name)
//        : short_name_(short_name), long_name_(std::move(long_name)) {}
//
//    explicit FlagArgument(const std::string& long_name)
//        : long_name_(std::move(long_name)) {}
//
//    explicit FlagArgument(char short_name)
//        : short_name_(short_name) {}
//
//    [[nodiscard]] std::string GetLongName() const {
//        return long_name_;
//    }
//
//    [[nodiscard]] bool GetValue() const {
//        return value_;
//    }
//
//    [[nodiscard]] char GetShortName() const {
//        return short_name_;
//    }
//
//    [[nodiscard]] bool GetValueFromValues(int index) const {
//        return flag_values_[index];
//    }
//
//    [[nodiscard]] std::string GetInstructions() const {
//        return help_instructions_;
//    }
//
//    [[nodiscard]] bool GetDefault() const {
//        return value_;
//    }
//
//    FlagArgument& SetValue(bool value);
//
//    FlagArgument& Default(bool value);
//
//    FlagArgument& StoreValue(bool& destination);
//
//    std::string type = "flag";
//
//  private:
//    char short_name_{};
//    std::string long_name_{};
//    bool value_ = false;
//    bool is_stored_ = false;
//    bool* store_pointer_{};
//    std::vector<bool> flag_values_{};
//    std::string help_instructions_{};
//};
}