#include <string>

#include "filter_source.h"
#include "grayscale.h"
#include "negative.h"
#include "sharpening.h"
#include "edge_detection.h"
#include "crop.h"
#include "gaussian_blur.h"
#include "chess_brigthness.h"

FilterSource::FilterSource() {

    // TODO Add new filters here

    Crop* crop = new Crop{};
    catalog_[crop->GetName()] = crop;

    Grayscale* grayscale = new Grayscale{};
    catalog_[grayscale->GetName()] = grayscale;

    Negative* negative = new Negative{};
    catalog_[negative->GetName()] = negative;

    Sharpening* sharpening = new Sharpening{};
    catalog_[sharpening->GetName()] = sharpening;

    EdgeDetection* edge_detection = new EdgeDetection{*grayscale};
    catalog_[edge_detection->GetName()] = edge_detection;

    GaussianBlur* gaus_blur = new GaussianBlur{};
    catalog_[gaus_blur->GetName()] = gaus_blur;

    ChessBrightness* chess_brightness = new ChessBrightness{};
    catalog_[chess_brightness->GetName()] = chess_brightness;
};

FilterSource::~FilterSource() {
    for (auto& [filter_name, ptr] : catalog_) {
        delete ptr;
    }
}

IFilter& FilterSource::GetFilter(std::string filter_name) {
    if (!catalog_.contains(filter_name)) {
        throw FilterNotFound{"Filter " + filter_name + " does not exist."};
    }

    return *catalog_[filter_name];
};
