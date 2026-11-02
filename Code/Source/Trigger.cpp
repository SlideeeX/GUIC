#include "Guic/Trigger.hpp"
#include "Guic/config/Functions.hpp"

using namespace guic::engine;
using namespace guic::engine::key;

namespace guic {

Trigger::Trigger() {}

Trigger::Trigger(Rect rect) {
    setHit(true);
    setRect(rect);
    unchange();
}

void Trigger::on(std::function<bool()> condition) {
    this->condition = [condition](const Event*)
    {
        return condition();
    };
}


void Trigger::on(std::function<bool(const Event*)> condition) {
    this->condition = condition;
}


void Trigger::bind(std::function<void()> callback) {
    this->callback = [callback](const Event*)
    {
        callback();
    };
}


void Trigger::bind(std::function<void(const Event*)> callback) {
    this->callback = callback;
}


void Trigger::onKey(Keys keys, std::function<void(const Event*)> callback) {
    on(
        [keys](const Event* event) -> bool
        {
            if (event->type != Event::EventType::KeyPressed) return false;
            if (event->data.key.repeat) return false;

            Keys mods = getModsMask(event);

            Keys requiredMods =
                keys & (
                    Key::Shift |
                    Key::Ctrl |
                    Key::Alt |
                    Key::GUI |
                    Key::RShift |
                    Key::RCtrl |
                    Key::RAlt |
                    Key::RGUI |
                    Key::CapsLock |
                    Key::NumLock |
                    Key::ScrollLock
                );

            Keys heldMods = mods & ~(Key::CapsLock | Key::NumLock | Key::ScrollLock);
            if (requiredMods.empty() ? heldMods.any() : (mods & requiredMods) != requiredMods) return false;

            Keys mainKey = keys & ~requiredMods;

            return event->data.key.key == mainKey;
        }
    );

    bind(callback);
}

void Trigger::onKeys(Keys keys, std::function<void(const Event*)> callback) {
    on(
        [keys](const Event* event)
        {
            if (event->type != Event::EventType::KeyPressed) return false;
            if (event->data.key.repeat) return false;

            return (event->data.key.key & keys).any();
        }
    );

    bind(callback);
}

void Trigger::onLMB(std::function<void()> callback) {
    on(
        [this](const Event* event)
        {
            return event->type == Event::EventType::MouseButtonReleased && event->data.click.key == Key::LMB;
        }
    );

    bind(callback);
}

void Trigger::onRMB(std::function<void()> callback) {
    on(
        [this](const Event* event)
        {
            return event->type == Event::EventType::MouseButtonReleased && event->data.mouse.key == Key::RMB;
        }
    );

    bind(callback);
}

void Trigger::onHover(std::function<void(bool hovered)> callback) {
    on(
        [this](const Event* event)
        {
            if(event->type != Event::EventType::MouseMoved) return false;

            bool contains = getGlobalVisibleRect().contains(event->data.mouse.x, event->data.mouse.y)
                         && getGlobalRect().contains(event->data.mouse.x, event->data.mouse.y, radius);

            if(contains != this->hovered) {
                this->hovered = contains;
                return true;
            }

            return false;
        }
    );

    bind([callback, this](){
        callback(this->hovered);
    });
}

void Trigger::control(const Event* event) {
    if(!isShow()) {
        this->hovered = false;
        return;
    }

    if (condition && condition(event)) {
        if (callback) {
            callback(event);
        }
    }
}

void Trigger::setRadius(int _radius) {
    radius = _radius < 0 ? 0 : _radius;
    update();
}

int Trigger::getRadius() const {
    return radius;
}

Rect Trigger::collectDirtyRect() const {
    return Rect();
}

Element* Trigger::hit(int x, int y) {
    if(radius<=0) return Element::hit(x, y);
    if (!isShow() || !isHit() || !getGlobalVisibleRect().contains(x, y)) return nullptr;
    if (!getGlobalRect().contains(x, y, radius)) return nullptr;
    return this;
}

Keys Trigger::getModsMask(const Event* event) {
    Keys mods{};

    if (event->mods.shift) mods = mods | Key::Shift;
    if (event->mods.ctrl) mods = mods | Key::Ctrl;
    if (event->mods.alt) mods = mods | Key::Alt;
    if (event->mods.system) mods = mods | Key::GUI;
    if (event->mods.rshift) mods = mods | Key::RShift;
    if (event->mods.rctrl) mods = mods | Key::RCtrl;
    if (event->mods.ralt) mods = mods | Key::RAlt;
    if (event->mods.rsystem) mods = mods | Key::RGUI;
    if (event->mods.capslock) mods = mods | Key::CapsLock;
    if (event->mods.numlock) mods = mods | Key::NumLock;
    if (event->mods.scrolllock) mods = mods | Key::ScrollLock;

    return mods;
}

}
