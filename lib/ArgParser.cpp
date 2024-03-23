#include "ArgParser.h"

const int kShortNameValueStart = 3;
const int kLongNameStart = 2;

bool IsNumeric(std::string_view const &str) {
    auto it = str.begin();
    while (it != str.end() && std::isdigit(*it)) {
        ++it;
    }

    return !str.empty() && it == str.end();
}

namespace ArgumentParser {

bool ArgParser::Parse(const std::vector<std::string>& arguments) {
    for (auto string_argument : all_arguments_) {
        auto* cur_argument = reinterpret_cast<StringArgument*>(string_argument);
        if (cur_argument->type != "str") {
            continue;
        }
        if (cur_argument->GetPositional()) {
            str_positional = cur_argument;
        }
    }
    for (auto& int_argument : all_arguments_) {
        auto* cur_argument = reinterpret_cast<IntArgument*>(int_argument);
        if (cur_argument->type != "int") {
            continue;
        }
        if (cur_argument->GetPositional()) {
            int_positional = cur_argument;
        }
    }
    for (std::string argument : arguments) {
        if (argument == "--help" || argument == "-h") {
            help_flag_ = true;
            return true;
        }
        if (argument[0] == '-') {
            // add if
            for (auto & string_argument : all_arguments_){
                auto* cur_argument = reinterpret_cast<StringArgument*>(string_argument);
                if (cur_argument->type != "str") {
                    continue;
                }
                if (argument.substr(kLongNameStart, cur_argument->GetLongName().size()) == cur_argument->GetLongName()) {
                    cur_argument->SetValue(argument.substr(kShortNameValueStart + cur_argument->GetLongName().size(), argument.size()));
                    continue;
                }
                if (argument[1] == cur_argument->GetShortName()) {
                    cur_argument->SetValue(argument.substr(kShortNameValueStart, argument.size()));
                    continue;
                }
            }
            for (auto & int_argument : all_arguments_) {
                auto* cur_argument = reinterpret_cast<IntArgument*>(int_argument);
                if (cur_argument->type != "int") {
                    continue;
                }
                if (argument.substr(kLongNameStart, cur_argument->GetLongName().size()) == cur_argument->GetLongName()) {
                    cur_argument->SetValue(std::stoi(argument.substr(kShortNameValueStart + cur_argument->GetLongName().size(), argument.size())));
                    continue;
                }
                if (argument[1] == cur_argument->GetShortName()) {
                    cur_argument->SetValue(std::stoi(argument.substr(kShortNameValueStart, argument.size())));
                    continue;
                }
            }
            for (auto & flag_argument : all_arguments_) {
                auto* cur_argument = reinterpret_cast<FlagArgument*>(flag_argument);
                if (cur_argument->type != "flag") {
                    continue;
                }
                if (argument.substr(kLongNameStart, cur_argument->GetLongName().size()) == cur_argument->GetLongName()) {
                    cur_argument->SetValue(true);
                    continue;
                }
            }
            for (int k = 1; k < argument.size(); ++k) {
                if (argument[k] == '-')
                    break;
                for (auto& flag_argument : all_arguments_) {
                    auto* cur_argument = reinterpret_cast<FlagArgument*>(flag_argument);
                    if (cur_argument->type != "flag") {
                        continue;
                    }
                    if (argument[k] == cur_argument->GetShortName()) {
                        cur_argument->SetValue(true);
                        continue;
                    }
                }
            }
        } else {
            if (argument == arguments[0])
                continue;
            if (int_positional != nullptr && IsNumeric(argument)) {
                int_positional->SetValue(stoi(argument));
            } else if (str_positional != nullptr && !IsNumeric(argument)) {
                str_positional->SetValue(argument);
            }
        }
    }
    for (auto object : all_arguments_) {
        auto* cur_argument = reinterpret_cast<StringArgument*>(object);
        if (cur_argument->type != "str") {
            continue;
        }
        if (cur_argument->GetValue().empty())
            return false;
    }
    for (auto& object : all_arguments_) {
        auto* cur_argument = reinterpret_cast<IntArgument*>(object);
        if (cur_argument->type != "int") {
            continue;
        }
        if (cur_argument->GetMulti() > cur_argument->GetIntValues().size() && cur_argument->GetMulti() != -1)
            return false;
    }
    for (auto& object : all_arguments_) {
        auto* cur_argument = reinterpret_cast<FlagArgument*>(object);
        if (cur_argument->type != "flag") {
            continue;
        }
        if (!cur_argument->GetValue())
            return false;
    }

    return true;
}

bool ArgParser::Parse(bool argc, char** argv) {
    return Parse(std::vector<std::string>(argv, argv + argc));
}

std::string ArgParser::HelpDescription() {
    help_description_ += (this->parser_name_ + '\n');
    help_description_ += (help_arguments_[0].GetInstructions() + "\n\n");
    for (auto object : all_arguments_) {
        auto* cur_argument = reinterpret_cast<StringArgument*>(object);
        if (cur_argument->type != "str") {
            continue;
        }
        if (cur_argument->GetShortName()) {
            help_description_ += '-';
            help_description_ += cur_argument->GetShortName();
            help_description_ += ",  ";
        } else {
            help_description_ += "     ";
        }
        if (!cur_argument->GetLongName().empty()) {
            help_description_ += "--";
            help_description_ += cur_argument->GetLongName();
            help_description_ += "=<string>";
        }
        if (!cur_argument->GetInstructions().empty()) {
            help_description_ += ",  ";
            help_description_ += cur_argument->GetInstructions();
        }
        if (cur_argument->GetMultiValue() > 0) {
            help_description_ += " [repeated, min args = ";
            help_description_ += std::to_string(cur_argument->GetMultiValue());
            help_description_ += ']';
        }
        if (!cur_argument->GetDefault().empty()) {
            help_description_ += " [default = ";
            help_description_ += cur_argument->GetDefault();
            help_description_ += ']';
        }
        help_description_ += '\n';
    }
    for (auto object : all_arguments_) {
        auto* cur_argument = reinterpret_cast<FlagArgument*>(object);
        if (cur_argument->type != "flag") {
            continue;
        }
        if (cur_argument->GetShortName()) {
            help_description_ += '-';
            help_description_ += cur_argument->GetShortName();
            help_description_ += ",  ";
        } else {
            help_description_ += "     ";
        }
        if (!cur_argument->GetLongName().empty()) {
            help_description_ += "--";
            help_description_ += cur_argument->GetLongName();
        }
        if (!cur_argument->GetInstructions().empty()) {
            help_description_ += ",  ";
            help_description_ += cur_argument->GetInstructions();
        }
        if (cur_argument->GetDefault()) {
            help_description_ += " [default = true]";
        }
        help_description_ += '\n';
    }
    for (auto object : all_arguments_) {
        auto* cur_argument = reinterpret_cast<IntArgument*>(object);
        if (cur_argument->type != "int") {
            continue;
        }
        if (cur_argument->GetShortName() != '\r') {
            help_description_ += '-';
            help_description_ += cur_argument->GetShortName();
            help_description_ += ",  ";
        } else {
            help_description_ += "     ";
        }
        if (!cur_argument->GetLongName().empty()) {
            help_description_ += "--";
            help_description_ += cur_argument->GetLongName();
            help_description_ += "=<int>";
        }
        if (!cur_argument->GetInstructions().empty()) {
            help_description_ += ",  ";
            help_description_ += cur_argument->GetInstructions();
        }
        if (cur_argument->GetMultiValue() > 0) {
            help_description_ += " [repeated, min args = ";
            help_description_ += std::to_string(cur_argument->GetMultiValue());
            help_description_ += ']';
        }
        if (cur_argument->IsDefined()) {
            help_description_ += " [default = ";
            help_description_ += std::to_string(cur_argument->GetDefault());
            help_description_ += ']';
        }
        help_description_ += '\n';
    }
    help_description_ += "\n-h, --help Display this help and exit\n";

    return help_description_;
}

StringArgument& ArgParser::AddStringArgument(char short_name) {
    all_arguments_.push_back(new StringArgument(short_name));
    
    StringArgument& arg = *reinterpret_cast<StringArgument*>(all_arguments_.back());
    
    return arg;
}

StringArgument& ArgParser::AddStringArgument(const std::string& long_name) {
    all_arguments_.push_back(new StringArgument(long_name));
    StringArgument& arg = *reinterpret_cast<StringArgument*>(all_arguments_.back());
    
    return arg;
}

StringArgument& ArgParser::AddStringArgument(char short_name, const std::string& long_name) {
    all_arguments_.push_back(new StringArgument(short_name, long_name));
    StringArgument& arg = *reinterpret_cast<StringArgument*>(all_arguments_.back());
    
    return arg;
}

StringArgument& ArgParser::AddStringArgument(char short_name, const std::string& long_name, const std::string& value) {
    all_arguments_.push_back(new StringArgument(short_name, long_name, value));

    
    StringArgument& arg = *reinterpret_cast<StringArgument*>(all_arguments_.back());
    
    return arg;
}

std::string ArgParser::GetStringValue(const std::string& long_name) const{
    for (auto object : all_arguments_) {
        auto* cur_argument = reinterpret_cast<StringArgument*>(object);
        if (cur_argument->GetLongName() == long_name) {
            return cur_argument->GetValue();
        }
    }

    return "";
}

std::string ArgParser::GetStringValue(char short_name) const{
    for (auto object : all_arguments_) {
        auto* cur_argument = reinterpret_cast<StringArgument*>(object);
        if (cur_argument->GetShortName() == short_name) {
            return cur_argument->GetValue();
        }
    }

    return "";
}

IntArgument& ArgParser::AddIntArgument(const std::string& long_name) {
    all_arguments_.push_back(new IntArgument(long_name));


    IntArgument& arg = *reinterpret_cast<IntArgument*>(all_arguments_.back());

    return arg;
}

IntArgument& ArgParser::AddIntArgument(char short_name, const std::string& long_name) {
    all_arguments_.push_back(new IntArgument(short_name, long_name));

        IntArgument& arg = *reinterpret_cast<IntArgument*>(all_arguments_.back());

    return arg;
}

IntArgument& ArgParser::AddIntArgument(const std::string& long_name, const std::string& some_number) {
    all_arguments_.push_back(new IntArgument(long_name, some_number));

        IntArgument& arg = *reinterpret_cast<IntArgument*>(all_arguments_.back());

    return arg;
}

IntArgument& ArgParser::AddIntArgument(char short_name) {
    all_arguments_.push_back(new IntArgument(short_name));

        IntArgument& arg = *reinterpret_cast<IntArgument*>(all_arguments_.back());

    return arg;
}

int ArgParser::GetIntValue(const std::string& long_name) const{
    for (const auto& object : all_arguments_) {
        auto* cur_argument = reinterpret_cast<IntArgument*>(object);
        if (cur_argument->GetLongName() == long_name) {
            return cur_argument->GetValue();
        }
    }

    return 0;
}

int ArgParser::GetIntValue(char short_name) const {
    for (const auto& object : all_arguments_) {
        auto* cur_argument = reinterpret_cast<IntArgument*>(object);
        if (cur_argument->GetShortName() == short_name) {
            return cur_argument->GetValue();
        }
    }

    return 0;
}

int ArgParser::GetIntValue(char short_name, int index) const{
    for (const auto& object : all_arguments_) {
        auto* cur_argument = reinterpret_cast<IntArgument*>(object);
        if (cur_argument->GetShortName() == short_name) {
            return cur_argument->GetValueFromValues(index);
        }
    }

    return 0;
}

int ArgParser::GetIntValue(const std::string& long_name, int index) const{
    for (const auto& object : all_arguments_) {
        auto* cur_argument = reinterpret_cast<IntArgument*>(object);
        if (cur_argument->GetLongName() == long_name) {
            return cur_argument->GetValueFromValues(index);
        }
    }

    return 0;
}

FlagArgument& ArgParser::AddFlag(const std::string& long_name) {
    all_arguments_.push_back(new FlagArgument(long_name));

    FlagArgument& arg = *reinterpret_cast<FlagArgument*>(all_arguments_.back());

    return arg;
}

FlagArgument& ArgParser::AddFlag(const std::string& long_name, const std::string& instructions) {
    all_arguments_.push_back(new FlagArgument(long_name, instructions));

    FlagArgument& arg = *reinterpret_cast<FlagArgument*>(all_arguments_.back());

    return arg;
}

FlagArgument& ArgParser::AddFlag(char short_name, const std::string& long_name) {
    all_arguments_.push_back(new FlagArgument(short_name, long_name));

    FlagArgument& arg = *reinterpret_cast<FlagArgument*>(all_arguments_.back());

    return arg;
}

FlagArgument& ArgParser::AddFlag(char short_name, const std::string& long_name, const std::string& some_logic) {
    all_arguments_.push_back(new FlagArgument(short_name, long_name, some_logic));

    FlagArgument& arg = *reinterpret_cast<FlagArgument*>(all_arguments_.back());

    return arg;
}

FlagArgument& ArgParser::AddFlag(char short_name) {
    all_arguments_.push_back(new FlagArgument(short_name));

    FlagArgument& arg = *reinterpret_cast<FlagArgument*>(all_arguments_.back());

    return arg;
}

bool ArgParser::GetFlag(const std::string& long_name) const{
    for (const auto & object : all_arguments_) {
        auto* cur_argument = reinterpret_cast<FlagArgument*>(object);
        if (cur_argument->GetLongName() == long_name) {
            return cur_argument->GetValue();
        }
    }

    return false;
}

bool ArgParser::GetFlag(char short_name) const{
    for (const auto & object : all_arguments_) {
        auto* cur_argument = reinterpret_cast<FlagArgument*>(object);
        if (cur_argument->GetShortName() == short_name) {
            return cur_argument->GetValue();
        }
    }

    return false;
}

bool ArgParser::GetFlag(char short_name, int index) const{
    for (const auto & object : all_arguments_) {
        auto* cur_argument = reinterpret_cast<FlagArgument*>(object);
        if (cur_argument->GetShortName() == short_name) {
            return cur_argument->GetValueFromValues(index);
        }
    }

    return false;
}

bool ArgParser::GetFlag(const std::string& long_name, int index) const{
    for (const auto & object : all_arguments_) {
        auto* cur_argument = reinterpret_cast<FlagArgument*>(object);
        if (cur_argument->GetLongName() == long_name) {
            return cur_argument->GetValueFromValues(index);
        }
    }

    return false;
}

HelpArgument& ArgParser::AddHelp(char short_name, const std::string& long_name, const std::string& instructions) {
    help_arguments_.emplace_back(short_name, long_name, instructions);

    return help_arguments_[all_arguments_.size() - 1];
}

bool ArgParser::Help(){
    return help_flag_;
}
}