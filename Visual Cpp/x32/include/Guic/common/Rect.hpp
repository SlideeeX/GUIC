#pragma once
#include <Guic/config/Export.hpp>

namespace guic {

struct GUIC_API Rect
{
    Rect();
    Rect(int x, int y, int width, int height);

    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;

    bool isEmpty() const;
    bool contains(int x, int y) const;
    bool contains(int x, int y, int radius) const;
    bool intersects(const Rect& rect) const;

    Rect getClippedArea(const Rect& rect) const;
    Rect getMerged(const Rect& rect) const;

    bool operator==(const Rect& other) const;
    bool operator!=(const Rect& other) const;
};

}
