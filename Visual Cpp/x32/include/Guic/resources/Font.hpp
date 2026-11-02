#pragma once
#include <Guic/engine/Resource.hpp>
#include <Guic/engine/Glyph.hpp>
#include <Guic/engine/GlyphEntry.hpp>
#include <Guic/config/Types.hpp>
#include <Guic/common/Size.hpp>
#include <string>
#include <vector>

namespace guic {

class GUIC_API Font : public engine::Resource
{
public:
    struct GUIC_API Pack
    {
        std::vector<Uint32> codepoints;

        bool contains(Uint32 codepoint) const;

        std::size_t size() const
        {
            return codepoints.size();
        }

        static Pack make(const std::string& characters);

        static const Pack EN;
        static const Pack RU;
        static const Pack Sign;
    };

    Font(const std::string& path, Uint32 font_size);

    engine::Bitmap* createBitmap() override;
    void addPack(Pack pack);
    void addPack(const std::string& pack);

    engine::Glyph getGlyph(Uint32 codepoint) const;

    // Кернинг между двумя кодпойнтами в пикселях; 0, если пары нет.
    int getKerning(Uint32 previous, Uint32 current) const;

    int getLineHeight() const;
    int getAscent() const;
    int getDescent() const;

    Uint32 getFontSize() const;

    Size getAtlasSize() const;
protected:
    bool copyMetadataFrom(Resource& src) override;
private:
    int ascent = 0;
    int descent = 0;
    int lineHeight = 0;

    std::vector<engine::GlyphEntry> glyphs;

    // Отсортированные кодпоинты для матрицы кернинга.
    std::vector<Uint32> kerningCodepoints;
    // Матрица kerningCodepoints.size() x kerningCodepoints.size(), строка — previous.
    std::vector<int> kernings;

    std::vector<Uint32> loading_codepoints;

    Size atlas_size;
    engine::Glyph missingGlyph;

    std::string path;
    Uint32 font_size;

    static const std::string PACK_EN;
    static const std::string PACK_RU;
    static const std::string PACK_SIGN;

    static constexpr Uint32 MissingGlyphCodepoint = 0xFFFFFFFF;
};

}
