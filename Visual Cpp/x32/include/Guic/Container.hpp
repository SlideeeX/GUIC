#pragma once
#include <Guic/Element.hpp>
#include <vector>

namespace guic {

class GUIC_API Container : public Element
{

public:
	Container();
	Container(Rect rect);
	~Container();

    void add(Element &item);
    void remove(Element &item);
    void clear();
    void detachChild(const Element* child) override;

    void setRect(Rect rect) override;
    void setPosition(Position pos) override;
    void setSize(Size size) override;

    Rect collectDirtyRect() const override;

    void control(const Event* event) override;
    void preload(engine::Renderer &renderer) override;
    void draw(engine::Renderer &renderer) override;
    Element* hit(int x, int y) override;
protected:
private:
    // Topmost child hit at (x, y) in top-first order, or nullptr.
    Element* hitItem(int x, int y);
    // True if item is this container or one of its ancestors: adding it would create a cycle.
    bool isCycle(const Element* item) const;

    std::vector<Element*> items;
    Uint16 version = 0;

};

}
