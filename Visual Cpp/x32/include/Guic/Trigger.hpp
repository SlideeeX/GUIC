#pragma once
#include <Guic/config/Export.hpp>
#include <Guic/config/Types.hpp>
#include <Guic/engine/Key.hpp>
#include <Guic/Element.hpp>
#include <functional>

namespace guic {

class GUIC_API Trigger : public Element
{
public:
    Trigger();
    Trigger(Rect rect);

    void on(std::function<bool()> condition);
    void on(std::function<bool(const Event*)> condition);

    void bind(std::function<void()> callback);
    void bind(std::function<void(const Event*)> callback);

    void onKey(engine::Keys keys, std::function<void(const Event*)> callback);
    void onKeys(engine::Keys keys, std::function<void(const Event*)> callback);

    void onLMB(std::function<void()> callback);
    void onRMB(std::function<void()> callback);

    void onHover(std::function<void(bool hovered)> callback);

    void control(const Event* event) override;

    void setRadius(int radius);
    int getRadius() const;

    Rect collectDirtyRect() const override;
    Element* hit(int x, int y) override;

protected:

private:
    std::function<bool(const Event*)> condition = {};
    std::function<void(const Event*)> callback = {};

    static engine::Keys getModsMask(const Event* event);
    int radius = 0;

    bool hovered = false;
};

}
