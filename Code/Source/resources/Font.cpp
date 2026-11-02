#include "Guic/resources/Font.hpp"
#include "SDL2/SDL_ttf.h"
#include "Guic/external/maxrects/MaxRectsBinPack.hpp"
#include <cstring>
#include <algorithm>

using namespace guic::engine;

namespace guic {

const Font::Pack Font::Pack::EN =
    Font::Pack::make(
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
    );

const Font::Pack Font::Pack::RU =
    Font::Pack::make(
        "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
        "абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
    );

const Font::Pack Font::Pack::Sign =
    Font::Pack::make(
        "0123456789"
        " .,!?;:-_()[]{}<>"
        "\"'`~@#$%^&*+=/\\|"
        "«»„“”‘’–—…№€£¥©®™"
    );

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

bool Font::Pack::contains(Uint32 codepoint) const
{
    return std::binary_search(
        codepoints.begin(),
        codepoints.end(),
        codepoint
    );
}

Font::Pack Font::Pack::make(const std::string& characters)
{
    Pack pack;

    pack.codepoints = decodeUTF8(characters);

    std::sort(
        pack.codepoints.begin(),
        pack.codepoints.end()
    );

    std::vector<Uint32>::iterator newEnd = std::unique(
        pack.codepoints.begin(),
        pack.codepoints.end()
    );

    pack.codepoints.erase(
        newEnd,
        pack.codepoints.end()
    );

    return pack;
}

Font::Font(const std::string& path, Uint32 font_size) : path(path), font_size(font_size){};


Bitmap* Font::createBitmap()
{
    is_metadata_loaded = false;

    glyphs.clear();
    kerningCodepoints.clear();
    kernings.clear();
    atlas_size = Size();
    ascent = descent = lineHeight = 0;
    missingGlyph = engine::Glyph();

    TTF_Font* font = TTF_OpenFont(
        path.c_str(),
        static_cast<int>(font_size)
    );

    if (font == nullptr)
    {
        return nullptr;
    }

    ascent = TTF_FontAscent(font);
    descent = TTF_FontDescent(font);
    lineHeight = TTF_FontLineSkip(font);

    // Кернинг считаем заранее для всех пар пака, чтобы верстка
    // не зависела от открытого TTF_Font.
    kerningCodepoints = loading_codepoints;
    std::sort(kerningCodepoints.begin(), kerningCodepoints.end());

    const std::size_t kerningCount = kerningCodepoints.size();
    kernings.assign(kerningCount * kerningCount, 0);

    if (TTF_GetFontKerning(font))
    {
        for (std::size_t i = 0; i < kerningCount; ++i)
        {
            for (std::size_t j = 0; j < kerningCount; ++j)
            {
                // Ошибка и кернинг -1 пикселя возвращают одно и то же значение,
                // поэтому различаем их через SDL_GetError().
                SDL_ClearError();

                const int kerning = TTF_GetFontKerningSizeGlyphs32(
                    font,
                    kerningCodepoints[i],
                    kerningCodepoints[j]
                );

                if (kerning == -1 && SDL_GetError()[0] != '\0')
                    continue;

                kernings[i * kerningCount + j] = kerning;
            }
        }
    }

    struct GlyphData
    {
        Uint32 codepoint = 0;

        int minx = 0;
        int maxx = 0;
        int miny = 0;
        int maxy = 0;
        int advance = 0;

        int width = 0;
        int height = 0;

        Rect rect;

        // Глиф, отрисованный один раз на этапе 1; освобождается на этапе 4 или при раннем выходе.
        SDL_Surface* surface = nullptr;
    };

    std::vector<GlyphData> data;
    data.reserve(loading_codepoints.size());

    // 1. Собираем метрики и размеры глифов.
    for (Uint32 codepoint : loading_codepoints)
    {
        GlyphData item;
        item.codepoint = codepoint;

        if (TTF_GlyphMetrics32(
                font,
                codepoint,
                &item.minx,
                &item.maxx,
                &item.miny,
                &item.maxy,
                &item.advance
            ) != 0)
        {
            continue;
        }

        item.surface = TTF_RenderGlyph32_Blended(
            font,
            codepoint,
            SDL_Color{255, 255, 255, 255}
        );

        if (item.surface != nullptr)
        {
            item.width = item.surface->w;
            item.height = item.surface->h;

            // Пустой глиф (например, пробел) на этапе 4 не нужен.
            if (item.width <= 0 || item.height <= 0)
            {
                SDL_FreeSurface(item.surface);
                item.surface = nullptr;
            }
        }

        data.push_back(item);
    }

    GlyphData missing;

    missing.codepoint = MissingGlyphCodepoint;

    missing.width = static_cast<int>(font_size * 0.5f);
    missing.height = static_cast<int>(font_size * 0.9f);

    missing.advance = static_cast<int>(font_size * 0.6f);

    missing.minx = 0;
    missing.maxx = missing.width;
    missing.miny = 0;
    missing.maxy = missing.height;

    data.push_back(missing);

        // 2. Упаковываем изображения через MaxRects.
    // Два дополнительных пикселя защищают соседние глифы
    // от растекания при фильтрации текстуры.
    bool packed = false;
    int binSize = 128;

    while (!packed && binSize <= 4096)
    {
        rbp::MaxRectsBinPack packer;
        packer.Init(binSize, binSize, false);

        packed = true;

        for (GlyphData& item : data)
        {
            if (item.width <= 0 || item.height <= 0)
                continue;

            Rect rect = packer.Insert(
                item.width + 2,
                item.height + 2,
                rbp::MaxRectsBinPack::RectBestAreaFit
            );

            if (rect.width <= 0 || rect.height <= 0)
            {
                packed = false;
                break;
            }

            item.rect = rect;
        }

        if (!packed)
            binSize *= 2;
    }

    if (!packed)
    {
        for (GlyphData& item : data)
            SDL_FreeSurface(item.surface);

        TTF_CloseFont(font);
        return nullptr;
    }

    // 3. Вычисляем фактические размеры атласа.
    int atlasWidth = 1;
    int atlasHeight = 1;

    for (const GlyphData& item : data)
    {
        if (item.rect.width <= 0 || item.rect.height <= 0)
            continue;

        atlasWidth = std::max(
            atlasWidth,
            item.rect.x + item.rect.width
        );

        atlasHeight = std::max(
            atlasHeight,
            item.rect.y + item.rect.height
        );
    }

    Bitmap* bitmap = new Bitmap();

    bitmap->width = static_cast<Uint16>(atlasWidth);
    bitmap->height = static_cast<Uint16>(atlasHeight);

    atlas_size.width = atlasWidth;
    atlas_size.height = atlasHeight;

    bitmap->pixels.assign(
        static_cast<std::size_t>(atlasWidth) *
        static_cast<std::size_t>(atlasHeight) * 4,
        0
    );

    glyphs.reserve(data.size());

    // 4. Создаём GlyphEntry и переносим пиксели в RGBA-атлас.
    for (GlyphData& item : data)
    {
        GlyphEntry entry;
        entry.codepoint = item.codepoint;

        entry.glyph.advance = static_cast<Uint16>(
            std::max(0, std::min(item.advance, 65535))
        );

        entry.glyph.bearing_x = static_cast<Sint16>(item.minx);
        entry.glyph.bearing_y = static_cast<Sint16>(item.maxy);

        // Пустые глифы, например пробелы, тоже сохраняем:
        // у них есть advance, даже если изображения нет.
        if (item.width > 0 && item.height > 0)
        {
            entry.glyph.x = static_cast<Uint16>(item.rect.x + 1);
            entry.glyph.y = static_cast<Uint16>(item.rect.y + 1);

            entry.glyph.width = item.width;
            entry.glyph.height = item.height;


            if(item.codepoint == MissingGlyphCodepoint)
            {
                for(int y = 0; y < item.height; y++)
                {
                    for(int x = 0; x < item.width; x++)
                    {
                        bool border =
                            x == 0 ||
                            y == 0 ||
                            x == item.width - 1 ||
                            y == item.height - 1;


                        Uint8* pixel =
                            bitmap->pixels.data() +
                            ((item.rect.y + 1 + y) * atlasWidth +
                             (item.rect.x + 1 + x)) * 4;


                        pixel[0] = 255;
                        pixel[1] = 255;
                        pixel[2] = 255;
                        pixel[3] = border ? 255 : 0;
                    }
                }
            } else {
                SDL_Surface* surface = item.surface;
                item.surface = nullptr;

                if (surface != nullptr)
                {
                    SDL_Surface* rgba = SDL_ConvertSurfaceFormat(
                        surface,
                        SDL_PIXELFORMAT_RGBA32,
                        0
                    );

                    SDL_FreeSurface(surface);

                    if (rgba != nullptr)
                    {
                        const int x = item.rect.x + 1;
                        const int y = item.rect.y + 1;

                        entry.glyph.x = static_cast<Uint16>(x);
                        entry.glyph.y = static_cast<Uint16>(y);
                        entry.glyph.width =
                            static_cast<Uint16>(rgba->w);
                        entry.glyph.height =
                            static_cast<Uint16>(rgba->h);

                        bool locked = false;

                        if (SDL_MUSTLOCK(rgba))
                        {
                            if (SDL_LockSurface(rgba) == 0)
                                locked = true;
                        }
                        else
                        {
                            locked = true;
                        }

                        if (locked)
                        {
                            for (int row = 0; row < rgba->h; ++row)
                            {
                                const Uint8* source =
                                    static_cast<const Uint8*>(rgba->pixels) +
                                    static_cast<std::size_t>(row) *
                                    rgba->pitch;

                                Uint8* destination =
                                    bitmap->pixels.data() +
                                    (static_cast<std::size_t>(y + row) *
                                     atlasWidth + x) * 4;

                                memcpy(
                                    destination,
                                    source,
                                    static_cast<std::size_t>(rgba->w) * 4
                                );
                            }

                            if (SDL_MUSTLOCK(rgba))
                                SDL_UnlockSurface(rgba);
                        }

                        SDL_FreeSurface(rgba);
                    }
                }
            }
        }

        if(item.codepoint == MissingGlyphCodepoint)
        {
            missingGlyph = entry.glyph;
        }

        glyphs.push_back(entry);
    }

    // getGlyph() использует бинарный поиск — сортировка обязательна.
    std::sort(
        glyphs.begin(),
        glyphs.end(),
        [](const GlyphEntry& a, const GlyphEntry& b)
        {
            return a.codepoint < b.codepoint;
        }
    );

    TTF_CloseFont(font);

    is_metadata_loaded = true;

    return bitmap;
}

void Font::addPack(Pack pack)
{
    for (Uint32 codepoint : pack.codepoints)
    {
        const std::vector<Uint32>::const_iterator it =
            std::find(
                loading_codepoints.begin(),
                loading_codepoints.end(),
                codepoint
            );

        if (it == loading_codepoints.end()) loading_codepoints.push_back(codepoint);
    }

    is_metadata_loaded = false;
    nextRevision();
}

void Font::addPack(const std::string& pack)
{
    addPack(Pack::make(pack));
}

Glyph Font::getGlyph(Uint32 codepoint) const
{
    const std::vector<GlyphEntry>::const_iterator it =
        std::lower_bound(
            glyphs.begin(),
            glyphs.end(),
            codepoint,
            [](const GlyphEntry& entry, Uint32 cp)
            {
                return entry.codepoint < cp;
            }
        );

    if (it != glyphs.end() && it->codepoint == codepoint) return it->glyph;

    return missingGlyph;
}

int Font::getKerning(Uint32 previous, Uint32 current) const
{
    const auto prev = std::lower_bound(
        kerningCodepoints.begin(),
        kerningCodepoints.end(),
        previous
    );

    const auto cur = std::lower_bound(
        kerningCodepoints.begin(),
        kerningCodepoints.end(),
        current
    );

    if (prev == kerningCodepoints.end() || *prev != previous ||
        cur == kerningCodepoints.end() || *cur != current)
        return 0;

    const std::size_t count = kerningCodepoints.size();
    const std::size_t row = static_cast<std::size_t>(prev - kerningCodepoints.begin());
    const std::size_t column = static_cast<std::size_t>(cur - kerningCodepoints.begin());

    return kernings[row * count + column];
}

int Font::getLineHeight() const {
    return lineHeight;
}

int Font::getAscent() const {
    return ascent;
}

int Font::getDescent() const {
    return descent;
}

Uint32 Font::getFontSize() const {
    return font_size;
}

Size Font::getAtlasSize() const {
    return atlas_size;
}

bool Font::copyMetadataFrom(engine::Resource& src)
{
    Font* other = dynamic_cast<Font*>(&src);
    if (other == nullptr) return false;

    path = other->path;
    font_size = other->font_size;

    ascent = other->ascent;
    descent = other->descent;
    lineHeight = other->lineHeight;

    glyphs = std::move(other->glyphs);
    kerningCodepoints = std::move(other->kerningCodepoints);
    kernings = std::move(other->kernings);

    atlas_size = other->atlas_size;
    missingGlyph = other->missingGlyph;
    loading_codepoints = other->loading_codepoints;

    return true;
}

}
