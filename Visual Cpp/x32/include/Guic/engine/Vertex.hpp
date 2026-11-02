#pragma once
#include <Guic/config/Export.hpp>
#include <Guic/common/Color.hpp>

namespace guic { namespace engine {

struct GUIC_API Vertex
{
    float x = 0;
    float y = 0;
    float u = 0;
    float v = 0;
    Color color = Color::Black;
};

}}
