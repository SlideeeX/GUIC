#include "Guic/common/Position.hpp"

namespace guic {

GUIC_API Position::Position(int x, int y) {
    this->x = x, this->y = y;
}

Position GUIC_API Position::operator+(const Position& other) const {
    return Position{x + other.x, y + other.y};
}

Position GUIC_API Position::operator-(const Position& other) const {
    return Position{x - other.x, y - other.y};
}

bool GUIC_API Position::operator==(const Position& other) const {
    return (x == other.x && y == other.y);
}

bool GUIC_API Position::operator!=(const Position& other) const {
    return !(*this == other);
}

}
