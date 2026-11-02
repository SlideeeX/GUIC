#pragma once
#include <Guic/config/Export.hpp>

namespace guic {

struct GUIC_API Position
{
    Position();
    Position(int x, int y);

    int x = 0;
    int y = 0;

    Position operator+(const Position& other) const;
    Position operator-(const Position& other) const;
    bool operator==(const Position& other) const;
    bool operator!=(const Position& other) const;
};

}
