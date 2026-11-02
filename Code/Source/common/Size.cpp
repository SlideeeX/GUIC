#include "Guic/common/Size.hpp"

namespace guic {

GUIC_API Size::Size(int width, int height) {
    this->width = width, this->height = height;
}

Size GUIC_API Size::operator+(const Size& other) const {
    return Size{width + other.width, height + other.height};
}

Size GUIC_API Size::operator-(const Size& other) const {
    return Size{width - other.width, height - other.height};
}

bool GUIC_API Size::operator==(const Size& other) const {
    return (width == other.width && height == other.height);
}

bool GUIC_API Size::operator!=(const Size& other) const {
    return !(*this == other);
}

}
