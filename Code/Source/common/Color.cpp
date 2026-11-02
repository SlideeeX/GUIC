#include "Guic/common/Color.hpp"

namespace guic {

const Color GUIC_API Color::Invisible(0x00000000U);
const Color GUIC_API Color::Black(0x000000ffU);
const Color GUIC_API Color::White(0xffffffffU);
const Color GUIC_API Color::Red(0xff0000ffU);
const Color GUIC_API Color::Green(0x00ff00ffU);
const Color GUIC_API Color::Blue(0x0000ffffU);
const Color GUIC_API Color::Yellow(0xffff00ffU);
const Color GUIC_API Color::Purple(0xff00ffffU);
const Color GUIC_API Color::Aqua(0x00ffffffU);

GUIC_API Color::Color()
{
    r = g = b = a = 0;
}

GUIC_API Color::Color(Uint32 hex)
{
    r = (hex >> 24) & 0xFF;
    g = (hex >> 16) & 0xFF;
    b = (hex >> 8) & 0xFF;
    a = hex & 0xFF;
}

GUIC_API Color::Color(std::string hex)
{
    if ((hex.size() != 7 && hex.size() != 9) || hex[0] != '#') {
        r = 0xFF;
        g = 0x00;
        b = 0xFF;
        a = 0xFF;
        return;
    }

    if (hex.size() == 9){
        r = hexToDec(hex[1], hex[2]);
        g = hexToDec(hex[3], hex[4]);
        b = hexToDec(hex[5], hex[6]);
        a = hexToDec(hex[7], hex[8]);
    }
    else if (hex.size() == 7) {
        r = hexToDec(hex[1], hex[2]);
        g = hexToDec(hex[3], hex[4]);
        b = hexToDec(hex[5], hex[6]);
        a = 0xFF;
    }
}

GUIC_API Color::Color(Uint8 r, Uint8 g, Uint8 b)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = 0xFF;
}

GUIC_API Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

Uint8 GUIC_API Color::getR() const
{
    return r;
}

Uint8 GUIC_API Color::getG() const
{
    return g;
}

Uint8 GUIC_API Color::getB() const
{
    return b;
}

Uint8 GUIC_API Color::getA() const
{
    return a;
}

Uint32 GUIC_API Color::getHex() const
{
    return ((Uint32)r << 24) | ((Uint32)g << 16) | ((Uint32)b << 8) | (Uint32)a;
}

bool GUIC_API Color::operator==(const Color& other) const {
    return r == other.r && g == other.g && b == other.b && a == other.a;
}

bool GUIC_API Color::operator!=(const Color& other) const {
    return !(*this == other);
}

Uint8 Color::hexToDec(char high, char low)
{
    return (hexDigitToInt(high) * 16) + hexDigitToInt(low);
}

Uint8 Color::hexDigitToInt(char c)
{
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }
    if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }
    return 0;
}

}
