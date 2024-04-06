#pragma once

#include <stdexcept>
#include <unordered_map>
#include <string>

#include "bitmap.h"

class FilterNotFound : public std::runtime_error {
public:
    explicit FilterNotFound(std::string e) : runtime_error{e} {};
};

class FilterParamsError : public std::runtime_error {
public:
    explicit FilterParamsError(std::string e) : runtime_error{e} {};
};

class IFilter {
public:
    virtual std::string GetName() const = 0;
    virtual void Apply(PixelMatix&, const std::vector<std::string>&) = 0;

    virtual ~IFilter() = default;
};

class FilterSource {
public:
    FilterSource();
    IFilter& GetFilter(std::string);

    ~FilterSource();

private:
    std::unordered_map<std::string, IFilter*> catalog_;
};
