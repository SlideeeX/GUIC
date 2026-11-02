#include "Guic/Text.hpp"
#include <algorithm>

using namespace guic::engine;

namespace guic {

static std::vector<Uint32> decodeUTF8(const std::string& text)
{
    std::vector<Uint32> result;

    for (std::size_t i = 0; i < text.size();)
    {
        const auto c = static_cast<unsigned char>(text[i]);
        Uint32 cp = 0;
        std::size_t length = 0;

        if (c < 0x80)
        {
            cp = c;
            length = 1;
        }
        else if ((c & 0xE0) == 0xC0)
        {
            cp = c & 0x1F;
            length = 2;
        }
        else if ((c & 0xF0) == 0xE0)
        {
            cp = c & 0x0F;
            length = 3;
        }
        else if ((c & 0xF8) == 0xF0)
        {
            cp = c & 0x07;
            length = 4;
        }
        else
        {
            ++i;
            continue;
        }

        if (i + length > text.size())
            break;

        bool valid = true;

        for (std::size_t j = 1; j < length; ++j)
        {
            const auto next =
                static_cast<unsigned char>(text[i + j]);

            if ((next & 0xC0) != 0x80)
            {
                valid = false;
                break;
            }

            cp = (cp << 6) | (next & 0x3F);
        }

        if (!valid)
        {
            ++i;
            continue;
        }

        result.push_back(cp);
        i += length;
    }

    return result;
}

Text::Text() {
    setHit(false);
    setColor(Color::Black);
}

Text::Text(Rect rect) {
    setHit(false);
    setRect(rect);
    setColor(Color::Black);
}

Text::Text(Rect rect, const std::string& str) {
    setHit(false);
    setRect(rect);
    setString(str);
    setColor(Color::Black);
}

Text::Text(Rect rect, const std::string& str, Font& font) {
    setHit(false);
    setRect(rect);
    setString(str);
    setFont(font);
    setColor(Color::Black);
}

void Text::setString(const std::string& str)
{
    this->str = str;
    update();
}

void Text::setFont(Font& font)
{
    this->font = &font;
    update();
}

void Text::setColor(Color color)
{
    this->color = color;
    update();
}

std::string Text::getString() const
{
    return str;
}

const Font* Text::getFont() const
{
    return font;
}

Color Text::getColor() const
{
    return color;
}

void Text::preload(Renderer &renderer) {
    if(!isShow() || font == nullptr) return;
    if(!getGlobalVisibleRect().intersects(renderer.getClippedRect())) return;

    if (!font->isMetadataLoaded() || !renderer.isLoaded(*font)) {
        renderer.load(*font);
        update();
    }
}

void Text::draw(Renderer &renderer) {
    if(!isShow()) {
        unchange();
        return;
    }

    if(font == nullptr) return;
    if(!getGlobalVisibleRect().intersects(renderer.getClippedRect())) return;

    if(isChanged()) buildGeometry();

    renderer.draw(*font, textGeometry);
    unchange();
}

void Text::buildGeometry()
{
    textGeometry.clear();

    if (font == nullptr) return;
    if (!font->isMetadataLoaded()) return;

    Rect visibleRect = getGlobalVisibleRect();
    if (visibleRect.width == 0 || visibleRect.height == 0) return;

    std::vector<Uint32> codepoints = decodeUTF8(str);

    Size atlasSize = font->getAtlasSize();

    float cursorX = 0;
    float cursorY = 0;

    // 0 — нет предыдущего символа; такого кодпойнта в паках нет.
    Uint32 previousCodepoint = 0;

    Rect globalRect = getGlobalRect();

    for (Uint32 codepoint : codepoints)
    {
        if (codepoint == '\n')
        {
            cursorX = 0;
            cursorY += font->getLineHeight();
            previousCodepoint = 0;
            continue;
        }

        cursorX += font->getKerning(previousCodepoint, codepoint);
        previousCodepoint = codepoint;

        Glyph glyph = font->getGlyph(codepoint);

        float x0 = globalRect.x + cursorX;
        float y0 = globalRect.y + cursorY;

        float x1 = x0 + glyph.width;
        float y1 = y0 + glyph.height;


        if (x1 < visibleRect.x ||
            y1 < visibleRect.y ||
            x0 > visibleRect.x + visibleRect.width ||
            y0 > visibleRect.y + visibleRect.height)
        {
            cursorX += glyph.advance;
            continue;
        }


        float left = std::max(x0, static_cast<float>(visibleRect.x));
        float top = std::max(y0, static_cast<float>(visibleRect.y));

        float right = std::min(
            x1,
            static_cast<float>(visibleRect.x + visibleRect.width)
        );

        float bottom = std::min(
            y1,
            static_cast<float>(visibleRect.y + visibleRect.height)
        );


        float glyphWidth = x1 - x0;
        float glyphHeight = y1 - y0;


        float tx0 = float(glyph.x) / atlasSize.width;
        float ty0 = float(glyph.y) / atlasSize.height;

        float tx1 = float(glyph.x + glyph.width) / atlasSize.width;
        float ty1 = float(glyph.y + glyph.height) / atlasSize.height;


        float u0 = 0;
        float v0 = 0;
        float u1 = 0;
        float v1 = 0;

        if(glyphWidth != 0 && glyphHeight != 0){
            u0 = tx0 + (tx1 - tx0) * ((left - x0) / glyphWidth);
            v0 = ty0 + (ty1 - ty0) * ((top - y0) / glyphHeight);
            u1 = tx0 + (tx1 - tx0) * ((right - x0) / glyphWidth);
            v1 = ty0 + (ty1 - ty0) * ((bottom - y0) / glyphHeight);
        }

        textGeometry.push_back({left, top, u0, v0, color});
        textGeometry.push_back({left, bottom, u0, v1, color});
        textGeometry.push_back({right, bottom, u1, v1, color});

        textGeometry.push_back({left, top, u0, v0, color});
        textGeometry.push_back({right, top, u1, v0, color});
        textGeometry.push_back({right, bottom, u1, v1, color});

        cursorX += glyph.advance;
    }
}

}
