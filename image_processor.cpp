#include "parser.h"
#include "bitmap.h"
#include "filter_source.h"

#include <iostream>

int main(int argc, char** argv) {
    Config cfg;

    try {
        cfg = Parser::ParseCL(argc, argv);
    } catch (ParserError e) {
        std::cout << "Arguments error: " << e.what() << std::endl;
        exit(1);
    }

    std::cout << "Config has been successfully parsed." << std::endl;

    BMPImage image{cfg.input_path};

    std::cout << "Image has been successfully readed." << std::endl;

    FilterSource filter_source{};

    for (auto const& filter_s : cfg.filters) {
        try {
            IFilter& f = filter_source.GetFilter(filter_s.filter_name);
            f.Apply(image.matrix, filter_s.params);
            std::cout << " - " << f.GetName() << " has been applied" << std::endl;
        } catch (FilterNotFound e) {
            std::cout << e.what() << std::endl;
            std::cout << "check spelling or type -h to see all available filters" << std::endl;
        } catch (FilterParamsError e) {
            std::cout << e.what() << std::endl;
            std::cout << "type -h to see all available parametrs for each filter" << std::endl;
        }
    }

    image.Write(cfg.output_path);

    std::cout << "Image successfully written in " << cfg.output_path << std::endl;

    return 0;
}
