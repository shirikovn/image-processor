#include "parser.h"
#include <iostream>
#include <cctype>

Config Parser::ParseCL(int argc, char** argv) {

    if (argc < 3) {
        if (argc > 1 && std::string(argv[1]) == "-h") {
            std::string help =
                "Usage example: input_path output_path -filter1 param1\n\n"
                "Available filters:\n"
                "-crop {wigth} {hieght}: crop image to given size\n"
                "-neg: negative image\n"
                "-sharp: make image sharper\n"
                "-gs: convert image to grey shades\n"
                "-edge: {param}: detect edges (pixels that are bigger than param[0-1])\n"
                "-blur: {param}: Gaussian blur with sigma = param\n"
                "-chess-br {koef} {size}: Make chess like "
                "brightning with size of cell = size";

            std::cout << help << std::endl;
            exit(0);
        }

        throw ParserError{"Need minimum 2 args: input path, output path."};
    }

    Config config{};

    config.input_path = argv[1];
    config.output_path = argv[2];

    FilterOption opt;
    std::vector<std::string> arguments;

    for (size_t i = 3; i < argc; ++i) {
        std::string param = argv[i];

        if (param.substr(0, 1) == "-" && isalpha(param[1])) {

            if (i != 3) {
                opt.params = std::move(arguments);
                config.filters.push_back(std::move(opt));
                arguments = std::vector<std::string>{};
                opt = FilterOption{};
            }

            opt.filter_name = param.substr(1, param.size() - 1);
        } else {
            arguments.push_back(argv[i]);
        }
    }

    if (!opt.filter_name.empty()) {
        opt.params = std::move(arguments);
        config.filters.push_back(std::move(opt));
    }

    return config;
};
