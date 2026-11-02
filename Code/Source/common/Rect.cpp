#include "Guic/common/Rect.hpp"
#include <algorithm>

namespace guic {

GUIC_API Rect::Rect(){}

GUIC_API Rect::Rect(int x, int y, int w, int h) {
    this->x = x;
    this->y = y;
    this->width = w;
    this->height = h;
}

bool GUIC_API Rect::isEmpty() const {
    return width <= 0 || height <= 0;
}

bool GUIC_API Rect::contains(int x, int y) const {
    if (isEmpty()) return false;

    return x >= this->x && x <= this->x + this->width && y >= this->y && y <= this->y + this->height;
}

bool GUIC_API Rect::contains(int px, int py, int radius) const {
    if (!contains(px, py)) return false;
    if(radius == 0) return true;

    const int r = std::min({radius, width / 2, height / 2});

    const int left = x + r;
    const int right = x + width - r;
    const int top = y + r;
    const int bottom = y + height - r;

    int cx = 0;
    int cy = 0;

    if (px < left && py < top) { cx = left; cy = top; }
    else if (px > right && py < top) { cx = right; cy = top; }
    else if (px < left && py > bottom) { cx = left; cy = bottom; }
    else if (px > right && py > bottom) { cx = right; cy = bottom; }
    else return true;

    const long long dx = px - cx;
    const long long dy = py - cy;
    return dx * dx + dy * dy <= 1LL * r * r;
}

bool GUIC_API Rect::intersects(const Rect& rect) const {
    if (isEmpty() || rect.isEmpty()) return false;

    return !(x + width < rect.x || rect.x + rect.width < x || y + height < rect.y || rect.y + rect.height < y);
}

Rect GUIC_API Rect::getClippedArea(const Rect& rect) const {
    if (isEmpty() || rect.isEmpty()) return Rect();

    const int nx1 = std::max(x, rect.x);
    const int ny1 = std::max(y, rect.y);
    const int nx2 = std::min(x + width, rect.x + rect.width);
    const int ny2 = std::min(y + height, rect.y + rect.height);

    if (nx1 >= nx2 || ny1 >= ny2) return Rect();

    return Rect(nx1, ny1, nx2 - nx1, ny2 - ny1);
}

Rect GUIC_API Rect::getMerged(const Rect& rect) const {
    if (isEmpty()) return rect.isEmpty() ? Rect() : rect;
    if (rect.isEmpty()) return *this;

    const int left = std::min(x, rect.x);
    const int top = std::min(y, rect.y);
    const int right = std::max(x + width, rect.x + rect.width);
    const int bottom = std::max(y + height, rect.y + rect.height);

    return Rect(left, top, right - left, bottom - top);
}

bool GUIC_API Rect::operator==(const Rect& other) const {
    if (isEmpty() || other.isEmpty()) return isEmpty() && other.isEmpty();

    return x == other.x && y == other.y && width == other.width && height == other.height;
}

bool GUIC_API Rect::operator!=(const Rect& other) const {
    return !(*this == other);
}

}
