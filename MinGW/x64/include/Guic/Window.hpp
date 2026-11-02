#pragma once
#include <Guic/engine/EngineWindow.hpp>
#include <Guic/engine/Clock.hpp>
#include <Guic/config/Functions.hpp>
#include <Guic/Container.hpp>

namespace guic {

class GUIC_API Window
{
public:
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    Window();
    Window(std::string name, Size size);
    ~Window();

    void tune();
    void display();

    void setFPS(Uint16 fps);
    void redrawNextFrame();

    void open();
    void close();
    void closeEventSkip();

    void show();
    void hide();
    void focus();

    void setSize(Size size);
    void setName(std::string name);

    void load(engine::Resource& resource);
    void unload(engine::Resource& resource);

    void pushEvent(const Event* event);
    void clearEvents();

    void add(Element &item);
    void remove(Element &item);
    void clear();

    bool isOpen() const;
    bool isShow() const;
    bool isFocused() const;

    Uint32 getId() const;

    engine::Renderer* getRenderer() const;

    Size getSize() const;
    std::string getName() const;

    std::vector<const Event*> getEvents() const;
protected:

private:
    Clock clock;
    Uint64 frameTime = 0;

    Container* container = nullptr;
    std::vector<const Event*> events;

    engine::EngineWindow* engineWindow;
    bool redraw = true;
    bool skipCloseEvent = false;

    Element* lastTarget = nullptr;
};

}
