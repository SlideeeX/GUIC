#pragma once
#include <Guic/config/Export.hpp>
#include <Guic/config/Types.hpp>

namespace guic {

class GUIC_API Clock
{
public:
    Clock();

    Uint64 getTime() const;

    void startTimer();
    void stopTimer();

    Uint64 getTimer() const;
    Uint64 lapTimer();

private:
    Uint64 timerStart = 0;
    Uint64 timerElapsed = 0;
    bool timerRunning = false;
};

}
