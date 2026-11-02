#pragma once
#include <Guic/Element.hpp>
#include <Guic/resources/Image.hpp>

namespace guic {

class GUIC_API Sprite : public Element
{

public:
    enum class Mode {
        Color,
        Image,
        Mashup
    };

	Sprite();
	Sprite(Rect rect);
	Sprite(Rect rect, Image &image);
	Sprite(Rect rect, Color color);

	void setImage(Image &image);
    const Image* getImage() const;
    void setImageRect(Rect rect);

    void setColor(Color color);
    Color getColor() const;

    void setRadius(int radius);
    int getRadius() const;

    void setMode(Mode mode);
    Mode getMode() const;

    void preload(engine::Renderer &renderer) override;
    void draw(engine::Renderer &renderer) override;
    Element* hit(int x, int y) override;

protected:
    std::vector<engine::Vertex> geometry;
    void buildGeometry();
    void buildRoundedGeometry();

    Rect imageRect;
    bool calculateImageRect = true;

    static constexpr int cornerSegments = 4;
    static constexpr float arcTolerance = 0.2f;

private:
    Mode mode;
    Color color;
    Image* image;
    int radius = 0;
};

}
