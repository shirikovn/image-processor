#pragma once

#include <string>
#include <vector>

#include "filter_source.h"
#include "grayscale.h"
#include "bitmap.h"

class EdgeDetection : public IFilter {
public:
    explicit EdgeDetection(Grayscale& gs) : grayscale_{gs} {
    }

    inline std::string GetName() const override {
        return name_;
    }

    void Apply(PixelMatix& matrix, const std::vector<std::string>& params) override;

private:
    Grayscale& grayscale_;
    std::string name_ = "edge";
};
