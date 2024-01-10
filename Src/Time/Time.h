#pragma once

#include "Helper/Timer.h"
#include "Helper/NonConstructible.h"

class Time: public Helper::NonConstructible
{
public:
    static void Init();
    static void Update();
    static double DeltaTimeMilliSecond();
    static double DeltaTimeSecond();
    static double TimeSinceBegin();
    static double GetFrameTimerElapsed();

private:
    static inline Helper::Timer<Helper::TimePrecision::Microseconds> _globalTimer = Helper::Timer<Helper::TimePrecision::Microseconds>();
    static inline Helper::Timer<Helper::TimePrecision::Microseconds> _frameTimer = Helper::Timer<Helper::TimePrecision::Microseconds>();
    static inline double _deltaTime = 0;
    static inline double _timeSinceBegin = 0;
};