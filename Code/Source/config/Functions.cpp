#include "Guic/config/Functions.hpp"
#include "Guic/engine/Key.hpp"
#include "SDL2/SDL_ttf.h"
#include <cstring>
#include <mutex>

using namespace guic::engine;

namespace guic {

    GUIC_API void guic_delay(Uint32 mls) {
        SDL_Delay(mls);
    }

    GUIC_API Position guic_get_mouse_pos() {
        Position pos{0, 0};
        SDL_GetMouseState(&pos.x, &pos.y);
        return pos;
    }

    static std::mutex guic_events_mutex;

    std::vector<Event*> guic_write_events;
    std::vector<Event*> guic_read_events;
    std::size_t guic_read_cursor = 0;

    GUIC_API void guic_send_event(Event*& event) {
        if (event == nullptr) return;

        {
            std::lock_guard<std::mutex> lock(guic_events_mutex);
            guic_write_events.push_back(event);
        }

        event = nullptr;
    }
}

namespace guic { namespace config {
    Keys convertMouseScancode(Uint8 button) {
        if (button < SDL_BUTTON_LEFT || button > SDL_BUTTON_X2) return {};

        return makeKey(static_cast<KeyCode>(button + 360));
    }

    Keys convertKeyScancode(SDL_Scancode scancode) {
        if (scancode <= SDL_SCANCODE_UNKNOWN || scancode >= SDL_NUM_SCANCODES) return {};

        return makeKey(static_cast<KeyCode>(scancode));
    }

    bool guic_inited = false;

    GUIC_API bool guic_init() {
        if(guic_inited) return true;

        SDL_SetHint(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, "1");

        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            return false;
        }

        if (TTF_Init() != 0)
        {
            return false;
        }

        guic_inited = true;
        return true;
    };

    GUIC_API bool guic_quit() {
        if(!guic_inited) return true;

        SDL_Quit();
        TTF_Quit();

        guic_inited = false;
        return true;
    }

    GUIC_API const Event* guic_poll_event() {
        if (guic_read_cursor >= guic_read_events.size()) return nullptr;

        return guic_read_events[guic_read_cursor++];
    }

    bool guic_poll_sdl_event(Event* event) {
        SDL_Event sdl_event;
        SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);

        if(!SDL_PollEvent(&sdl_event)){
            return false;
        }

        const bool isKeyEvent = sdl_event.type == SDL_KEYDOWN || sdl_event.type == SDL_KEYUP;
        const SDL_Keymod mod = isKeyEvent
            ? static_cast<SDL_Keymod>(sdl_event.key.keysym.mod)
            : SDL_GetModState();

        event->mods.shift = (mod & KMOD_SHIFT) != 0;
        event->mods.ctrl = (mod & KMOD_CTRL) != 0;
        event->mods.alt = (mod & KMOD_ALT) != 0;
        event->mods.system = (mod & KMOD_GUI) != 0;

        event->mods.rshift = (mod & KMOD_RSHIFT) != 0;
        event->mods.rctrl = (mod & KMOD_RCTRL) != 0;
        event->mods.ralt = (mod & KMOD_RALT) != 0;
        event->mods.rsystem = (mod & KMOD_RGUI) != 0;

        event->mods.capslock = (mod & KMOD_CAPS) != 0;
        event->mods.numlock = (mod & KMOD_NUM) != 0;
        event->mods.scrolllock = (mod & KMOD_SCROLL) != 0;

        switch (sdl_event.type)
        {
            case SDL_WINDOWEVENT:
                switch (sdl_event.window.event)
                {
                    case SDL_WINDOWEVENT_CLOSE:
                        event->type = Event::EventType::WindowClosed;
                        break;

                    case SDL_WINDOWEVENT_RESIZED:
                    case SDL_WINDOWEVENT_SIZE_CHANGED:
                        event->type = Event::EventType::WindowResized;
                        event->data.window.w = sdl_event.window.data1;
                        event->data.window.h = sdl_event.window.data2;
                        break;

                    case SDL_WINDOWEVENT_MINIMIZED:
                        event->type = Event::EventType::WindowMinimized;
                        break;

                    case SDL_WINDOWEVENT_MAXIMIZED:
                        event->type = Event::EventType::WindowMaximized;
                        break;

                    case SDL_WINDOWEVENT_RESTORED:
                        event->type = Event::EventType::WindowRestored;
                        break;

                    case SDL_WINDOWEVENT_MOVED:
                        event->type = Event::EventType::WindowMoved;
                        event->data.window.x = sdl_event.window.data1;
                        event->data.window.y = sdl_event.window.data2;
                        break;

                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                        event->type = Event::EventType::WindowFocusGained;
                        break;

                    case SDL_WINDOWEVENT_FOCUS_LOST:
                        event->type = Event::EventType::WindowFocusLost;
                        break;

                    case SDL_WINDOWEVENT_EXPOSED:
                        event->type = Event::EventType::WindowExposed;
                        break;

                    default:
                        event->type = Event::EventType::None;
                        break;
                }

                event->winId = sdl_event.window.windowID;
                break;


            case SDL_KEYDOWN:
                event->type = Event::EventType::KeyPressed;
                event->winId = sdl_event.key.windowID;

                event->data.key.key = convertKeyScancode(sdl_event.key.keysym.scancode);
                event->data.key.repeat = sdl_event.key.repeat != 0;
                break;


            case SDL_KEYUP:
                event->type = Event::EventType::KeyReleased;
                event->winId = sdl_event.key.windowID;

                event->data.key.key = convertKeyScancode(sdl_event.key.keysym.scancode);
                break;


            case SDL_MOUSEMOTION:
                event->type = Event::EventType::MouseMoved;
                event->winId = sdl_event.motion.windowID;

                event->data.mouse.x = sdl_event.motion.x;
                event->data.mouse.y = sdl_event.motion.y;
                event->data.mouse.dx = sdl_event.motion.xrel;
                event->data.mouse.dy = sdl_event.motion.yrel;
                break;


            case SDL_MOUSEBUTTONDOWN:
                event->type = Event::EventType::MouseButtonPressed;
                event->winId = sdl_event.button.windowID;

                event->data.mouse.key = convertMouseScancode(sdl_event.button.button);
                event->data.mouse.x = sdl_event.button.x;
                event->data.mouse.y = sdl_event.button.y;
                break;


            case SDL_MOUSEBUTTONUP:
                event->type = Event::EventType::MouseButtonReleased;
                event->winId = sdl_event.button.windowID;

                event->data.mouse.key = convertMouseScancode(sdl_event.button.button);
                event->data.mouse.x = sdl_event.button.x;
                event->data.mouse.y = sdl_event.button.y;
                break;


            case SDL_MOUSEWHEEL:
                event->type = Event::EventType::MouseWheelScrolled;
                event->winId = sdl_event.wheel.windowID;

                event->data.mouse.wheel = sdl_event.wheel.y;

                {
                    Position mousePos = guic_get_mouse_pos();
                    event->data.mouse.x = mousePos.x;
                    event->data.mouse.y = mousePos.y;
                }
                break;


            case SDL_TEXTINPUT:
                event->type = Event::EventType::TextEntered;
                event->winId = sdl_event.text.windowID;

                memcpy(
                    event->data.text.text,
                    sdl_event.text.text,
                    sizeof(event->data.text.text)
                );
                break;


            case SDL_DROPFILE:
                event->type = Event::EventType::FileDropped;
                event->winId = sdl_event.drop.windowID;

                event->filePaths.clear();
                event->filePaths.emplace_back(sdl_event.drop.file);

                SDL_free(sdl_event.drop.file);
                break;

            default:
                event->type = Event::EventType::None;
                break;
        }

        return true;
    };

    static bool pressed = false;
    static Uint32 pressWinId = 0;
    static engine::Keys pressKey{};
    static int pressX = 0, pressY = 0;

    GUIC_API void guic_update_events() {
        for (Event* e : guic_read_events) delete e;
        guic_read_events.clear();
        guic_read_cursor = 0;

        std::vector<Event*> batch;
        Event* e = new Event();
        while(guic_poll_sdl_event(e)){
            if (!pressed && e->type == Event::EventType::MouseButtonPressed) {
                pressed = true;
                pressWinId = e->winId;
                pressKey = e->data.mouse.key;
                pressX = e->data.mouse.x;
                pressY = e->data.mouse.y;
            }

            batch.push_back(e);

            if (e->type == Event::EventType::MouseButtonReleased && e->data.mouse.key == pressKey) {
                if (pressed && e->winId == pressWinId) {
                    Event* click = new Event();
                    click->type = Event::EventType::MouseButtonClicked;
                    click->winId = e->winId;
                    click->data.click.pressedX = pressX;
                    click->data.click.pressedY = pressY;
                    click->data.click.releasedX = e->data.mouse.x;
                    click->data.click.releasedY = e->data.mouse.y;
                    click->data.click.key = e->data.mouse.key;
                    batch.push_back(click);
                }
                pressed = false;
            }

            e = new Event();
        }
        delete e;

        std::lock_guard<std::mutex> lock(guic_events_mutex);
        guic::guic_write_events.insert(guic::guic_write_events.end(), batch.begin(), batch.end());
        std::swap(guic::guic_write_events, guic_read_events);
    }
}}
