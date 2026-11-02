#pragma once
#include <Guic/engine/Renderer.hpp>
#include <Guic/common/Position.hpp>
#include <Guic/common/Size.hpp>
#include <Guic/common/Event.hpp>

namespace guic {

class GUIC_API Element
{

public:
    Element() = default;
    Element(const Element&) = delete;
    Element& operator=(const Element&) = delete;

    virtual ~Element();

    bool isShow() const;
    bool isChanged() const;

    void show();
    void hide();
    void update();

    void setLayer(Uint16 newLayer);
    Uint16 getLayer() const;

    void setHit(bool hit);
    bool isHit() const;

    virtual void setPosition(Position pos);
    virtual void setSize(Size size);
    virtual void setRect(Rect rect);

    Position getPosition() const;
    Size getSize() const;
    Rect getRect() const;
    Rect getGlobalRect() const;
    Rect getVisibleRect() const;
    Rect getGlobalVisibleRect() const;

    virtual Rect collectDirtyRect() const;

    const Element* getParent() const;

    virtual void control(const Event* event);
    virtual void preload(engine::Renderer &renderer);
    virtual void draw(engine::Renderer &renderer);

    virtual Element* hit(int x, int y);

    void attachTo(Element* parent);
    void detach();

    virtual void detachChild(const Element* child);

protected:
    void unchange();

    Rect rect;
    Rect oldRect;

private:
    Uint16 layer = 0;
    Element* parentElement = nullptr;

    bool is_show = true;
    bool is_changed = true;
    bool is_hit = true;
};

}
