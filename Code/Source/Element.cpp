#include "Guic/Element.hpp"
#include <assert.h>

using namespace guic::engine;

namespace guic {

Element::~Element() {
    detach();
}

bool Element::isShow() const {
    return is_show;
}

bool Element::isChanged() const {
    return is_changed;
}

void Element::update() {
    is_changed = true;
}

void Element::show() {
    is_show = true;
    update();
}

void Element::hide() {
    is_show = false;
    update();
}

void Element::setLayer(Uint16 newLayer) {
    layer = newLayer;
    update();
}

Uint16 Element::getLayer() const {
    return layer;
}

void Element::setHit(bool hit) {
    is_hit = hit;
}

bool Element::isHit() const {
    return is_hit;
}

void Element::setPosition(Position pos) {
    setRect(Rect(pos.x, pos.y, rect.width, rect.height));
    update();
}

void Element::setSize(Size size) {
    setRect(Rect(rect.x, rect.y, size.width, size.height));
    update();
}

void Element::setRect(Rect _rect) {
    if(oldRect.isEmpty()) oldRect = rect;
    rect = _rect;
    update();
}

Position Element::getPosition() const {
    return Position(rect.x, rect.y);
}

Size Element::getSize() const {
    return Size(rect.width, rect.height);
}

Rect Element::getRect() const {
    return rect;
}

Rect Element::getGlobalRect() const {
    if(parentElement == nullptr) return rect;

    Rect globalRect = parentElement->getGlobalRect();

    globalRect.x += rect.x;
    globalRect.y += rect.y;
    globalRect.width = rect.width;
    globalRect.height = rect.height;

    return globalRect;
}

Rect Element::getVisibleRect() const {
    if(parentElement == nullptr) return rect;

    const Rect parentRect = parentElement->getRect();
    const Rect parentVisibleRect = parentElement->getVisibleRect();
    const Rect parentLocalVisibleRect(
        parentVisibleRect.x - parentRect.x,
        parentVisibleRect.y - parentRect.y,
        parentVisibleRect.width,
        parentVisibleRect.height
    );

    return parentLocalVisibleRect.getClippedArea(rect);
}

Rect Element::getGlobalVisibleRect() const {
    Rect globalRect = getGlobalRect();

    if(parentElement == nullptr) return globalRect;

    Rect parentGlobalVisibleRect = parentElement->getGlobalVisibleRect();
    return parentGlobalVisibleRect.getClippedArea(globalRect);
}

Rect Element::collectDirtyRect() const {
    if (!isChanged()) return Rect();

    return oldRect.getMerged(getVisibleRect());
}

const Element* Element::getParent() const {
    return parentElement;
}

void Element::attachTo(Element* parent) {
    if(parent == this) return;
    if(parentElement != nullptr) parentElement->detachChild(this);

    parentElement = parent;
    update();
}

void Element::detach() {
    if(parentElement == nullptr) return;

    parentElement->detachChild(this);
    parentElement = nullptr;
    update();
}

void Element::detachChild(const Element* child) {}

Element* Element::hit(int x, int y) {
    if (!isShow() || !isHit() || !getGlobalVisibleRect().contains(x, y)) return nullptr;
    return this;
}

void Element::control(const Event* event) {};

void Element::preload(Renderer &renderer) {};

void Element::draw(Renderer &renderer) {};

void Element::unchange() {
    oldRect = Rect();
    is_changed = false;
}

}
