#pragma once

#include "IntArgument.h"
//#include "StringArgument.h"
#include "FlagArgument.h"
#include "Argument.h"

#include <utility>
#include <vector>
#include <variant>

namespace ArgumentParser {

class BaseArgument {
  public:
    std::string type = "base";
    char short_name_;
    std::string long_name_;
    std::string value_;
    std::string help_instructions_;
};

class StringArgument: public BaseArgument  {
  public:
    StringArgument(char short_name, const std::string& long_name, const std::string& instructions)
        : short_name_(short_name), long_name_(std::move(long_name)), help_instructions_(std::move(instructions)) {type = "str";}

    StringArgument(char short_name, const std::string& long_name)
        : short_name_(short_name), long_name_(std::move(long_name)) {type = "str";}

    explicit StringArgument(const std::string& long_name)
        : long_name_(std::move(long_name)) {type = "str";}

    explicit StringArgument(char short_name)
        : short_name_(short_name) {type = "str";}

    StringArgument SetValue(std::string_view value) {
        value_ = value;
        if (is_stored_) {
            *store_pointer_ = value;
        }

        return *this;
    }

    [[nodiscard]] std::string GetLongName() const {
        return long_name_;
    }

    [[nodiscard]] std::string GetValue() const{
        return value_;
    }

    [[nodiscard]] char GetShortName() const {
        return short_name_;
    }

    [[nodiscard]] std::string GetInstructions() const {
        return help_instructions_;
    }

    [[nodiscard]] int GetMultiValue() const {
        return min_amount_of_values_;
    }

    [[nodiscard]] std::string GetDefault() const {
        return value_;
    }

    [[nodiscard]] bool GetPositional() const {
        return is_positional_;
    }

    StringArgument Default(const std::string& value);

    StringArgument StoreValue(std::string& destination);

    StringArgument MultiValue(int amount);

    StringArgument Positional();

    std::string type = "str";

    char short_name_{};
    std::string long_name_;
    std::string value_;
    bool is_stored_ = false;
    bool is_positional_ = false;
    int min_amount_of_values_ = -1;
    std::string* store_pointer_{};
    std::string help_instructions_;
};

class IntArgument: public BaseArgument {
  public:
    IntArgument(char short_name, const std::string& long_name, int value)
        : short_name_(short_name), long_name_(std::move(long_name)), value_(value) {
        is_defined_ = true;
    }

    IntArgument(char short_name, const std::string& long_name)
        : short_name_(short_name), long_name_(std::move(long_name)) {}

    explicit IntArgument(const std::string& long_name)
        : long_name_(std::move(long_name)) {}

    IntArgument(const std::string& long_name, const std::string& instructions)
        : long_name_(std::move(long_name)), help_instructions_(std::move(instructions)) {}

    explicit IntArgument(char short_name)
        : short_name_(short_name) {}

    [[nodiscard]] std::string GetLongName() const {
        return long_name_;
    }

    [[nodiscard]] int GetValue() const {
        return value_;
    }

    [[nodiscard]] char GetShortName() const {
        return short_name_;
    }

    [[nodiscard]] bool IsDefined() const {
        return is_defined_;
    }

    [[nodiscard]] int GetValueFromValues(int index) const {
        return int_values_[index];
    }

    [[nodiscard]] std::vector<int> GetIntValues() const {
        return int_values_;
    }

    [[nodiscard]] int GetMulti() const {
        return min_amount_of_values_;
    }

    [[nodiscard]] std::string GetInstructions() const {
        return help_instructions_;
    }

    [[nodiscard]] int GetMultiValue() const {
        return min_amount_of_values_;
    }

    [[nodiscard]] int GetDefault() const {
        return value_;
    }

    [[nodiscard]] bool GetPositional() const {
        return is_positional_;
    }

    IntArgument& SetValue(int value);

    IntArgument& MultiValue();

    IntArgument& MultiValue(size_t amount);

    IntArgument& StoreValues(std::vector<int>& destination);

    IntArgument& Positional();

    std::string type = "int";

    char short_name_ = '\r';
    std::string long_name_{};
    int value_{};
    bool is_defined_ = false;
    bool is_stored_ = false;
    bool is_multi_value = false;
    bool is_positional_ = false;
    int* store_pointer_{};
    std::vector<int>* values_pointer_{};
    int min_amount_of_values_ = -1;
    std::vector<int> int_values_{};
    std::string help_instructions_{};
};

class FlagArgument: public BaseArgument {
  public:
    FlagArgument(char short_name, const std::string& long_name, bool value)
        : short_name_(short_name), long_name_(std::move(long_name)), value_(value) {}

    FlagArgument(char short_name, const std::string& long_name, const std::string& instructions)
        : short_name_(short_name), long_name_(std::move(long_name)), help_instructions_(std::move(instructions)) {}

    FlagArgument(const std::string& long_name, const std::string& instructions)
        : long_name_(std::move(long_name)), help_instructions_(std::move(instructions)) {}

    FlagArgument(char short_name, const std::string& long_name)
        : short_name_(short_name), long_name_(std::move(long_name)) {}

    explicit FlagArgument(const std::string& long_name)
        : long_name_(std::move(long_name)) {}

    explicit FlagArgument(char short_name)
        : short_name_(short_name) {}

    [[nodiscard]] std::string GetLongName() const {
        return long_name_;
    }

    [[nodiscard]] bool GetValue() const {
        return value_;
    }

    [[nodiscard]] char GetShortName() const {
        return short_name_;
    }

    [[nodiscard]] bool GetValueFromValues(int index) const {
        return flag_values_[index];
    }

    [[nodiscard]] std::string GetInstructions() const {
        return help_instructions_;
    }

    [[nodiscard]] bool GetDefault() const {
        return value_;
    }

    FlagArgument& SetValue(bool value);

    FlagArgument& Default(bool value);

    FlagArgument& StoreValue(bool& destination);

    std::string type = "flag";

    char short_name_{};
    std::string long_name_{};
    bool value_ = false;
    bool is_stored_ = false;
    bool* store_pointer_{};
    std::vector<bool> flag_values_{};
    std::string help_instructions_{};
};

class HelpArgument : BaseArgument {
  public:
    HelpArgument() = default;

    HelpArgument(char short_name, const std::string& long_name, const std::string& instructions):
    short_name_(short_name), long_name_(std::move(long_name)), instructions_(std::move(instructions))
    {}

    std::string GetInstructions() {
        return instructions_;
    }

    char short_name_{};
    std::string long_name_;
    std::string instructions_;
};

class ArgParser {
  public:
    explicit ArgParser(const std::string& parser_name)
        : parser_name_(std::move(parser_name)) {}

    ~ArgParser() = default;

    bool Parse(const std::vector<std::string>& arguments);

    bool Parse(bool argc, char** argv);

    StringArgument& AddStringArgument(char short_name);

    StringArgument& AddStringArgument(const std::string& long_name);

    StringArgument& AddStringArgument(char short_name, const std::string& long_name);

    StringArgument& AddStringArgument(char short_name, const std::string& long_name, const std::string& value);

    [[nodiscard]] std::string GetStringValue(const std::string& long_name) const;

    [[nodiscard]] std::string GetStringValue(char short_name) const;

    IntArgument& AddIntArgument(const std::string& long_name);

    IntArgument& AddIntArgument(char short_name, const std::string& long_name);

    IntArgument& AddIntArgument(const std::string& long_name, const std::string& some_number);

    IntArgument& AddIntArgument(char short_name);

    [[nodiscard]] int GetIntValue(const std::string& long_name) const;

    [[nodiscard]] int GetIntValue(char short_name) const;

    [[nodiscard]] int GetIntValue(char short_name, int index) const;

    [[nodiscard]] int GetIntValue(const std::string& long_name, int index) const;

    FlagArgument& AddFlag(const std::string& long_name);

    FlagArgument& AddFlag(const std::string& long_name, const std::string& instructions);

    FlagArgument& AddFlag(char short_name, const std::string& long_name);

    FlagArgument& AddFlag(char short_name, const std::string& long_name, const std::string& some_logic);

    FlagArgument& AddFlag(char short_name);

    [[nodiscard]] bool GetFlag(const std::string& long_name) const;

    [[nodiscard]] bool GetFlag(char short_name) const;

    [[nodiscard]] bool GetFlag(char short_name, int index) const;

    [[nodiscard]] bool GetFlag(const std::string& long_name, int index) const;

    HelpArgument& AddHelp(char short_name, const std::string& long_name, const std::string& instructions);

    bool Help();

    std::string HelpDescription();

    std::string parser_name_{};
    bool help_flag_ = false;
    IntArgument* int_positional = nullptr;
    StringArgument* str_positional = nullptr;
    std::vector<std::string> arguments_{};
    std::vector<BaseArgument*> all_arguments_{};
//    std::vector<StringArgument> string_arguments_{};
//    std::vector<IntArgument> int_arguments_{};
//    std::vector<FlagArgument> flag_arguments_{};
    std::vector<HelpArgument> help_arguments_{};
    std::string help_description_{};
};
} // namespace ArgumentParser
