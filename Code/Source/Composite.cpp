#include "Guic/Composite.hpp"

using namespace guic::engine;

namespace guic {

Composite::~Composite() {
    release(*container);
    delete container;
}

Composite::Composite() {
    container = new Container();
    adopt(*container);
    setHit(false);
    update();
}
Composite::Composite(Rect rect) {
    container = new Container(rect);
    adopt(*container);
    setHit(false);
    setRect(rect);
    update();
}

void Composite::setRect(Rect rect) {
    Element::setRect(rect);
    container->setRect(Rect(0, 0, rect.width, rect.height));
}
void Composite::setPosition(Position pos) {
    Element::setPosition(pos);
}
void Composite::setSize(Size size) {
    Element::setSize(size);
}

void Composite::draw(Renderer& renderer) {
    if(!isShow()) {
        unchange();
        return;
    }

    container->draw(renderer);
    unchange();
}
void Composite::control(const Event* event) {
    if(!isShow()) return;

    container->control(event);
}
void Composite::preload(Renderer& renderer) {
    if(!isShow()) return;

    container->preload(renderer);
}

Element* Composite::hit(int x, int y) {
    if (!isShow()) return nullptr;
    if (Element* found = container->hit(x, y)) return found;
    if(isHit() && getGlobalVisibleRect().contains(x, y)) return this;

    return nullptr;
}

Rect Composite::collectDirtyRect() const {
    if(isChanged()) return Element::collectDirtyRect();
    if(!isShow()) return Rect();

    return container->collectDirtyRect();
}

void Composite::add(Element& item) {
    container->add(item);
    update();
}

void Composite::remove(Element& item) {
    container->remove(item);
    update();
}

void Composite::adopt(Element& el) {
    el.attachTo(this);
    update();
}
void Composite::release(Element& el) {
    el.detach();
    update();
}

void Composite::detachChild(const Element* child) {
    container->detachChild(child);
    update();
}

}
