#include "Guic/engine/EngineWindow.hpp"
#include <SDL2/SDL.h>

using namespace guic::config;

namespace guic { namespace engine {

    struct EngineWindow::Impl {
        SDL_Window* window = nullptr;
    };

    EngineWindow::EngineWindow() {
        impl = new Impl();
        this->name = "Guic Window";
        this->size = Size(800, 600);
    };

    EngineWindow::EngineWindow(std::string name, Size size) {
        impl = new Impl();
        this->name = name;
        this->size = size;
    };

    EngineWindow::~EngineWindow() {
        delete renderer;

        if(impl->window != nullptr) SDL_DestroyWindow(impl->window);

        delete impl;
    };

    void EngineWindow::createWindow(){
        if(impl->window == nullptr) {
            impl->window = SDL_CreateWindow(
                name.c_str(),
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                size.width,
                size.height,
                (isShow() ? SDL_WINDOW_SHOWN : SDL_WINDOW_HIDDEN) | SDL_WINDOW_RESIZABLE
            );

            if (!impl->window) {
                opened = false;
                shown = false;
            } else {
                opened = true;
            }
        }

        if(isOpen() && renderer == nullptr) {
            renderer = new Renderer(native());
            renderer->setClipRect(Rect(0, 0, size.width, size.height));
        }
    };

    void EngineWindow::open() {
        if(isOpen()) return;

        createWindow();
    };

    void EngineWindow::close() {
        if(!isOpen()) return;

        size = getSize();
        name = getName();

        delete renderer;
        renderer = nullptr;

        SDL_DestroyWindow(impl->window);
        impl->window = nullptr;

        opened = false;
        shown = false;
    };

    void EngineWindow::show() {
        shown = true;

        if(!isOpen()) return;

        SDL_ShowWindow(impl->window);
    };

    void EngineWindow::hide() {
        if(!isShow()) return;

        shown = false;

        if(!isOpen()) return;

        SDL_HideWindow(impl->window);
    };

    void EngineWindow::focus() {
        if(!isOpen() || !isShow()) return;

        SDL_RaiseWindow(impl->window);
    };

    void EngineWindow::setSize(Size size) {
        this->size = size;

        if(!isOpen()) return;

        SDL_SetWindowSize(impl->window, size.width, size.height);
    };

    void EngineWindow::setName(std::string name) {
        this->name = name;

        if(!isOpen()) return;

        SDL_SetWindowTitle(impl->window, name.c_str());
    };

    void EngineWindow::setClipRect(Rect rect) {
        if(!isOpen()) return;

        renderer->setClipRect(rect);
    };

    void EngineWindow::load(Resource& resource) {
        if(!isOpen()) return;

        renderer->load(resource);
    };

    void EngineWindow::unload(Resource& resource) {
        if(!isOpen()) return;

        renderer->unload(resource);
    };

    void EngineWindow::display() {
        if(!isOpen() || !isShow()) return;

        renderer->present();
    };

    bool EngineWindow::isOpen() const {
        return opened;
    };

    bool EngineWindow::isShow() const {
        return shown;
    };

    bool EngineWindow::isFocused() const {
        if (!isOpen()) return false;

        return (SDL_GetWindowFlags(impl->window) & SDL_WINDOW_INPUT_FOCUS) != 0;
    }

    EngineWindowNative EngineWindow::native() const {
        return impl->window;
    };

    Renderer* EngineWindow::getRenderer() const {
        return renderer;
    };

    Size EngineWindow::getSize() const {
        if (!isOpen()) return size;

        int w, h;
        SDL_GetWindowSize(impl->window, &w, &h);
        return Size(w, h);
    }

    std::string EngineWindow::getName() const {
        if (!isOpen()) return name;

        return SDL_GetWindowTitle(impl->window);
    }

    Uint32 EngineWindow::getId() const {
        if(!isOpen()) return 0;

        return SDL_GetWindowID(impl->window);
    };
}}
