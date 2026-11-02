#include "Guic/Container.hpp"
#include <algorithm>

using namespace guic;
using namespace guic::engine;

namespace guic {

Container::Container() {
    setHit(false);
}

Container::Container(Rect rect) {
    setHit(false);
    setRect(rect);
}

Container::~Container() {
    clear();
}

bool Container::isCycle(const Element* item) const {
    for (const Element* node = this; node != nullptr; node = node->getParent()) {
        if (node == item) return true;
    }
    return false;
}

void Container::add(Element &item) {
    if(&item == this || isCycle(&item)) return;
    if(item.getParent() != nullptr) return;

    for (auto it = items.begin(); it != items.end(); ++it) {
        if (*it == &item) {
            return;
        }
    }

    item.attachTo(this);
    items.push_back(&item);
    version++;
}

void Container::remove(Element &item) {
    if (item.getParent() != this) return;
    item.detach();
    update();
}

void Container::clear() {
    std::vector<Element*> children = items;
    for (Element* item : children) {
        item->detach();
    }

    items.clear();
    version++;
    update();
}

void Container::detachChild(const Element* child) {
    auto it = std::find(items.begin(), items.end(), child);
    if (it != items.end()) {
        items.erase(it);
        version++;
    }
    update();
}

void Container::setRect(Rect _rect) {
    Element::setRect(_rect);
    for (Element* item : items) item->update();
}

void Container::setPosition(Position pos) {
    Element::setPosition(pos);
    for (Element* item : items) item->update();
}

void Container::setSize(Size size) {
    Element::setSize(size);
    for (Element* item : items) item->update();
}

Rect Container::collectDirtyRect() const {
    if(isChanged()) return Element::collectDirtyRect();
    if(!isShow()) return Rect();

    Rect dirtyRect;

    for (Element* item : items) {
        dirtyRect = dirtyRect.getMerged(item->collectDirtyRect());
    }

    if (dirtyRect.isEmpty()) return dirtyRect;

    dirtyRect.x += rect.x;
    dirtyRect.y += rect.y;

    return dirtyRect.getClippedArea(getVisibleRect());
}

void Container::control(const Event* event) {
    if(!isShow()) return;

    for (size_t i = 0; i < items.size(); ++i) {
        Element* current = items[i];
        Uint16 before = version;

        current->control(event);

        if (version != before) {
            auto it = std::find(items.begin(), items.end(), current);
            i = (it != items.end()) ? it - items.begin() : i-1;
        }
    }
}

Element* Container::hit(int x, int y) {
    if (!isShow()) return nullptr;
    if (Element* found = hitItem(x, y)) return found;
    if (isHit() && getGlobalVisibleRect().contains(x, y)) return this;
    return nullptr;
}

Element* Container::hitItem(int x, int y) {
    Element* best = nullptr;
    Uint16 bestLayer = 0;

    for (size_t i = items.size(); i-- > 0;) {
        Element* item = items[i];
        const Uint16 layer = item->getLayer();

        if (best && layer <= bestLayer) continue;
        if (Element* found = item->hit(x, y)) {
            best = found;
            bestLayer = layer;
        }
    }
    return best;
}

void Container::preload(Renderer &renderer) {
    if(!isShow()) return;

    for (size_t i = 0; i < items.size(); ++i) {
        items[i]->preload(renderer);
    }
}

void Container::draw(Renderer &renderer) {
    if(!isShow()) {
        unchange();
        return;
    }

    if(!getGlobalVisibleRect().intersects(renderer.getClippedRect())) return;

    int maxLayer = 0;

    for (Element* item : items) {
        maxLayer = std::max(maxLayer, (int)item->getLayer());
    }

    for(int j=0; j<=maxLayer; j++){
		for(size_t i=0; i<items.size(); i++){
			if(items[i]->getLayer()==j) {
				items[i]->draw(renderer);
			}
		}
	}

	unchange();
}

}
