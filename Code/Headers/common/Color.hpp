#pragma once
#include <Guic/config/Export.hpp>
#include <Guic/config/Types.hpp>
#include <string>

namespace guic {

class GUIC_API Color
{
public:
    static const Color Invisible;
    static const Color Black;
    static const Color White;
    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Yellow;
    static const Color Purple;
    static const Color Aqua;

    Color();
    Color(Uint32 hex);
    Color(std::string hex);
    Color(Uint8 r, Uint8 g, Uint8 b);
    Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    Uint8 getR() const;
    Uint8 getG() const;
    Uint8 getB() const;
    Uint8 getA() const;

    Uint32 getHex() const;

    bool operator==(const Color& other) const;
    bool operator!=(const Color& other) const;
protected:
private:
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
    Uint8 hexDigitToInt (char c);
    Uint8 hexToDec(char high, char low);
};

}
