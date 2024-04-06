#pragma once

#include <string>
#include <vector>
#include <stdexcept>

class ParserError : public std::runtime_error {
public:
    explicit ParserError(std::string msg) : runtime_error{msg} {};
};

struct FilterOption {
    std::string filter_name;
    std::vector<std::string> params;
};

struct Config {
    std::string input_path;
    std::string output_path;
    std::vector<FilterOption> filters;
};

class Parser {
public:
    static Config ParseCL(int argc, char** argv);
};
