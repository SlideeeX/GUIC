#pragma once
#include <Guic/config/Export.hpp>
#include <Guic/config/Types.hpp>
#include <vector>

namespace guic { namespace engine {

struct GUIC_API Bitmap
{
    Uint16 width = 0;
    Uint16 height = 0;
    std::vector<Uint8> pixels;
};

}}
