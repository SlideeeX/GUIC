#pragma once
#include <Guic/common/Event.hpp>
#include <Guic/common/Position.hpp>

namespace guic {

    GUIC_API void guic_delay(Uint32 mls);

    GUIC_API Position guic_get_mouse_pos();

    GUIC_API void guic_send_event(Event*& event);

}

namespace guic { namespace config {

    GUIC_API bool guic_init();

    GUIC_API bool guic_quit();

    GUIC_API void guic_update_events();

    GUIC_API const Event* guic_poll_event();

}}
