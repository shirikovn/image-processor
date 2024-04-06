#pragma once

#include <string>
#include <vector>

#include "filter_source.h"
#include "bitmap.h"

class Crop : public IFilter {
public:
    inline std::string GetName() const override {
        return name_;
    }

    void Apply(PixelMatix& matrix, const std::vector<std::string>& params) override;

private:
    std::string name_ = "crop";
};
