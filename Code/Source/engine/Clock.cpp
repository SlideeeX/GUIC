#include <chrono>
#include "Guic/engine/Clock.hpp"

namespace guic {

Clock::Clock(){}

Uint64 Clock::getTime() const
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()
    ).count();
}

void Clock::startTimer()
{
    if (timerRunning) return;

    timerStart = getTime();
    timerRunning = true;
}

void Clock::stopTimer()
{
    if (!timerRunning) return;

    timerElapsed += getTime() - timerStart;
    timerRunning = false;
}

Uint64 Clock::getTimer() const
{
    if (!timerRunning) return timerElapsed;

    return getTime() - timerStart;
}

Uint64 Clock::lapTimer()
{
    Uint64 elapsed = getTimer();

    timerStart = getTime();
    timerElapsed = 0;
    timerRunning = true;

    return elapsed;
}

}
