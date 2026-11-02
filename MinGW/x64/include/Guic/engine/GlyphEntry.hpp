#pragma once
#include <Guic/config/Export.hpp>
#include <Guic/engine/Glyph.hpp>

namespace guic { namespace engine {

struct GUIC_API GlyphEntry
{
    Uint32 codepoint = 0;
    Glyph glyph;
};

}}
