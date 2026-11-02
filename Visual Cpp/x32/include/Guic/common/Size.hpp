#pragma once
#include <Guic/config/Export.hpp>

namespace guic {

struct GUIC_API Size
{
    Size() = default;
    Size(int width, int height);

    int width = 0;
    int height = 0;

    Size operator+(const Size& other) const;
    Size operator-(const Size& other) const;
    bool operator==(const Size& other) const;
    bool operator!=(const Size& other) const;
};

}
