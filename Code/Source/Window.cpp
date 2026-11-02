#include "Guic/Window.hpp"

using namespace guic::engine;
using namespace guic::config;

namespace guic {

namespace {

    bool isMousePointerEvent(const Event* event) {
        switch (event->type) {
            case Event::EventType::MouseMoved:
            case Event::EventType::MouseButtonPressed:
            case Event::EventType::MouseButtonReleased:
            case Event::EventType::MouseWheelScrolled:
                return true;
            default:
                return false;
        }
    }

}

    std::vector<Window*> guic_windows;

    Window::Window() {
        guic_init();
        engineWindow = new EngineWindow();
        container = new Container();
        Size size = engineWindow->getSize();
        container->setRect(Rect(0, 0, size.width, size.height));
        setFPS(60);
    }

    Window::Window(std::string name, Size size) {
        guic_init();
        engineWindow = new EngineWindow(name, size);
        container = new Container();
        container->setRect(Rect(0, 0, size.width, size.height));
        setFPS(60);
    }

    Window::~Window() {
        for (auto it = guic_windows.begin(); it != guic_windows.end(); ++it)
        {
            if (*it == this)
            {
                guic_windows.erase(it);
                break;
            }
        }

        if(container != nullptr) delete container;
        if(engineWindow != nullptr) delete engineWindow;

        if(guic_windows.size() <= 0) guic_quit();
    }

    void guic_windows_tune(Uint32 windowId);

    void Window::tune() {
        if(!isOpen()) return;

        guic_windows_tune(getId());

        std::vector<const Event*> pendingEvents;
        pendingEvents.swap(events);

        for(const Event* event : pendingEvents) {
            if (!isOpen() || event == nullptr) break;

            if(event->type == Event::EventType::WindowResized){
                container->setSize(Size(event->data.window.w, event->data.window.h));
                redrawNextFrame();
            }

            if(event->type == Event::EventType::WindowExposed ||
               event->type == Event::EventType::WindowRestored ||
               event->type == Event::EventType::WindowMaximized){
                redrawNextFrame();
            }

            if(event->type == Event::EventType::MouseMoved) {
                Element* target = container->hit(event->data.mouse.x, event->data.mouse.y);

                if (lastTarget && lastTarget != target) lastTarget->control(event);

                if (target) {
                    lastTarget = target;
                    target->control(event);
                }

                continue;
            } else if (isMousePointerEvent(event)) {
                Element* target = container->hit(event->data.mouse.x, event->data.mouse.y);

                if (target) {
                    target->control(event);
                }

                continue;
            } else if(event->type == Event::EventType::MouseButtonClicked) {
                Element* down = container->hit(event->data.click.pressedX, event->data.click.pressedY);
                Element* up   = container->hit(event->data.click.releasedX, event->data.click.releasedY);
                if (down && down == up) down->control(event);

                continue;
            } else {
                container->control(event);
            }

            if(event->type == Event::EventType::WindowClosed){
                if(!skipCloseEvent){
                    close();
                    skipCloseEvent = false;
                }
            }
        }
    }

    void Window::display() {
        if(!isOpen() || !isShow()) return;

        if (clock.getTimer() < frameTime) return;
        clock.lapTimer();

        Rect dirtyRect;

        if(redraw){
            dirtyRect = Rect(0, 0, getSize().width, getSize().height);
            redraw = false;
        } else {
            dirtyRect = container->collectDirtyRect();
        }

        if(dirtyRect.isEmpty()) return;

        engineWindow->setClipRect(dirtyRect);

        getRenderer()->clearClip();
        container->preload(*getRenderer());
        getRenderer()->flush();
        container->draw(*getRenderer());

        engineWindow->display();
    }

    void Window::setFPS(Uint16 fps) {
        frameTime = fps==0 ? 0 : 1000/fps;
    }

    void Window::redrawNextFrame() {
        redraw = true;
    }

    void Window::open() {
        if(isOpen()) return;

        clock.startTimer();

        engineWindow->open();
        show();

        guic_windows.push_back(this);
    }

    void Window::close() {
        if(!isOpen()) return;

        clock.stopTimer();
        clock.lapTimer();

        for (auto it = guic_windows.begin(); it != guic_windows.end(); ++it)
        {
            if (*it == this)
            {
                guic_windows.erase(it);
                break;
            }
        }

        events.clear();
        engineWindow->close();
    }

    void Window::closeEventSkip() {
        skipCloseEvent = true;
    }

    void Window::show() {
        engineWindow->show();
        redrawNextFrame();
    }

    void Window::hide() {
        engineWindow->hide();
    }

    void Window::focus() {
        engineWindow->focus();
    }

    void Window::setSize(Size size) {
        engineWindow->setSize(size);
        container->setSize(size);
    }

    void Window::setName(std::string name) {
        engineWindow->setName(name);
    }

    void Window::load(Resource& resource) {
        engineWindow->load(resource);
    }

    void Window::unload(Resource& resource) {
        engineWindow->unload(resource);
    }

    void Window::pushEvent(const Event* event) {
        if(!isOpen() || !isShow()) return;

        events.push_back(event);
    }

    void Window::clearEvents() {
        events.clear();
    }

    void Window::add(Element &item) {
        container->add(item);
    }

    void Window::remove(Element &item) {
        container->remove(item);
    }

    void Window::clear() {
        container->clear();
    }

    bool Window::isOpen() const {
        return engineWindow->isOpen();
    }

    bool Window::isShow() const {
        return engineWindow->isShow();
    }

    bool Window::isFocused() const {
        return engineWindow->isFocused();
    }

    Uint32 Window::getId() const {
        return engineWindow->getId();
    }

    Renderer* Window::getRenderer() const {
        return engineWindow->getRenderer();
    }

    Size Window::getSize() const {
         return engineWindow->getSize();
    }

    std::string Window::getName() const {
        return engineWindow->getName();
    }

    std::vector<const Event*> Window::getEvents() const {
        return events;
    }

    static Uint32 guic_windows_router_P = 0;
    static Uint32 guic_windows_router_U = 0;
    static std::vector<Uint32> guic_windows_router_X;

    bool guic_windows_route_get_update(Uint32 windowId) {
        bool update = false;

        if (windowId == guic_windows_router_P) update = true;
        if (windowId == guic_windows_router_U) update = true;
        for(Uint32 winId : guic_windows_router_X){
            if(winId == windowId) {
                update = true;
                break;
            }
        }

        if(update) {
            guic_windows_router_U = windowId;
            guic_windows_router_X.clear();
        } else {
            guic_windows_router_X.push_back(windowId);
        }

        guic_windows_router_P = windowId;

        return update;
    }

    void guic_windows_clear_events() {
        for(Window* window : guic_windows){
            window->clearEvents();
        }
    }

    void guic_windows_tune(Uint32 windowId) {
        if(guic_windows_route_get_update(windowId)) {
            guic_windows_clear_events();
            guic_update_events();
        }

        const Event* event = guic_poll_event();
        while(event) {
            for(Window* window : guic_windows){
                if(event->winId == window->getId()){
                    window->pushEvent(event);
                    break;
                } else if(event->winId == 0){
                    window->pushEvent(event);
                }
            }
            event = guic_poll_event();
        }
    }

}
