#pragma once
#include <Guic/Element.hpp>
#include <Guic/resources/Font.hpp>
#include <string>

namespace guic {

class GUIC_API Text : public Element
{

public:
	Text();
	Text(Rect rect);
	Text(Rect rect, const std::string& str);
	Text(Rect rect, const std::string& str, Font &font);

    void setString(const std::string& str);
    void setFont(Font &font);
    void setColor(Color color);

    std::string	getString() const;
    const Font* getFont() const;
    Color getColor() const;

    void preload(engine::Renderer &renderer) override;
    void draw(engine::Renderer &renderer);
protected:
    void buildGeometry();
    std::vector<engine::Vertex> textGeometry;
private:
    Font* font = nullptr;
    std::string str;
    Color color;
};

}
