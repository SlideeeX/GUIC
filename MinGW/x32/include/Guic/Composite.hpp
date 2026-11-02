#pragma once
#include <Guic/Container.hpp>

namespace guic {

class GUIC_API Composite : public Element
{
public:
    ~Composite() override;
    Composite();
    Composite(Rect rect);

    virtual void setRect(Rect rect) override;
    virtual void setPosition(Position pos) override;
    virtual void setSize(Size size) override;

    virtual void draw(engine::Renderer& renderer) override;
    virtual void control(const Event* event) override;
    virtual void preload(engine::Renderer& renderer) override;

    virtual Element* hit(int x, int y) override;
    virtual Rect collectDirtyRect() const override;

protected:
    void add(Element& item);
    void remove(Element& item);

    void adopt(Element& el);
    void release(Element& el);

    virtual void detachChild(const Element* child) override;
private:
    Container* container;
};

}
