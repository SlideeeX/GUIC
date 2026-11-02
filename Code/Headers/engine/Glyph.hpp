#pragma once
#include <Guic/config/Export.hpp>
#include <Guic/config/Types.hpp>

namespace guic { namespace engine {

struct GUIC_API Glyph
{
    Uint16 x = 0;
    Uint16 y = 0;
    Uint16 width = 0;
    Uint16 height = 0;

    Sint16 advance = 0;
    Sint16 bearing_x = 0;
    Sint16 bearing_y = 0;
};

}}
