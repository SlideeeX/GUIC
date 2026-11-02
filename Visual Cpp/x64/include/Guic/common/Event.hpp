#pragma once
#include <Guic/config/Export.hpp>
#include <Guic/config/Types.hpp>
#include <Guic/engine/Keys.hpp>
#include <vector>
#include <string>

namespace guic {

struct GUIC_API Event
{
    virtual ~Event() = default;

    enum class EventType
    {
        None,
        Custom,
        KeyPressed,
        KeyReleased,
        MouseMoved,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseButtonClicked,
        MouseWheelScrolled,
        WindowClosed,
        WindowResized,
        WindowMinimized,
        WindowMaximized,
        WindowRestored,
        WindowMoved,
        WindowFocusGained,
        WindowFocusLost,
        WindowExposed,
        TextEntered,
        FileDropped
    };

    EventType type = EventType::None;

    struct mods {
        bool shift = false;
        bool ctrl = false;
        bool alt = false;
        bool system = false;

        bool rshift = false;
        bool rctrl = false;
        bool ralt = false;
        bool rsystem = false;

        bool capslock = false;
        bool numlock = false;
        bool scrolllock = false;
    } mods;

    Uint32 winId = 0;
    Uint32 customId = 0; // 100000-999999 reserved by Guic // 0-99999 reserved for main development
    std::vector<std::string> filePaths;

    union data {
        data() { key = {}; mouse = {}; click = {}; window = {}; text = {}; file = {}; }
        ~data(){};

        struct key {
            engine::Keys key;
            bool pressed = false;
            bool released = false;
            bool repeat = false;
        } key;

        struct mouse {
            int	x = 0;
            int	y = 0;
            int	dx = 0;
            int	dy = 0;
            engine::Keys key;
            float wheel = 0;
        } mouse;

        struct click {
            int	pressedX = 0;
            int	pressedY = 0;
            int	releasedX = 0;
            int	releasedY = 0;
            engine::Keys key;
        } click;

        struct window {
            int x = 0;
            int y = 0;
            int w = 0;
            int h = 0;
            bool close = false;
        } window;

        struct text {
            char text[32];
        } text;

        struct file {
            int count = 0;
        } file;
    } data;

};

}
